/*
 * SwipeContainer.cpp
 *
 *  Created on: 25 sie 2017
 *      Author: Uzume
 */

#include "SwipeContainer.h"
#include "../../../Touch/EasingEquations/EasingEquations.h"

SwipeContainer::SwipeContainer() :
		currentState(NO_ANIMATION),
		numOfScreens(0),
		currentScreen(0),
		swipeCutoff(80),
		dragX(0),
		animateDistance(0),
		startX(0),
		endElasticWidth(30),
		menuChangeInitiatedAction(0),
		menuChangeEndedAction(0),
		animationCounter(0){

	Container::add(&screens);
	Container::add(&dotIndicator);
}

SwipeContainer::~SwipeContainer() {
}

void SwipeContainer::add(Drawable* screen){
	screens.add(screen);
	numOfScreens++;
	dotIndicator.setnumberOfDots(numOfScreens);
	setWidth(screen->getWidth());
	setHeight(screen->getHeight());
}

void SwipeContainer::setSwipeCutoff(uint16_t cutoff){
	swipeCutoff = cutoff;
}

void SwipeContainer::setEndSwipeElasticWidth(uint16_t width) {
	endElasticWidth = width;
}

void SwipeContainer::setDotIndicatorBitmaps(const Bitmap& normalDot, const Bitmap& highlightedDot) {
	dotIndicator.setBitmaps(normalDot, highlightedDot);
}

void SwipeContainer::setDotIndicatorXY(uint16_t x, uint16_t y){
	dotIndicator.setXY(x, y);
}

void SwipeContainer::setDotIndicatorXYWithCenteredX(uint16_t x, uint16_t y) {
	dotIndicator.setXY(x - dotIndicator.getWidth() / 2, y);
}

void SwipeContainer::setMenuChangeInitiatedCallback(GenericCallback<const SwipeContainer&>& callback) {
	menuChangeInitiatedAction = &callback;
}

void SwipeContainer::setMenuChangeEndedCallback(GenericCallback<const SwipeContainer&>& callback) {
	menuChangeEndedAction = &callback;
}

uint8_t SwipeContainer::getNumberOfScreens(){
	return numOfScreens;
}

void SwipeContainer::adjustScreens() {
	screens.moveTo(-(currentScreen * getWidth()) + dragX, 0);
}

void SwipeContainer::setSelectedScreen(uint8_t screenIndex)
{
    currentScreen = screenIndex;
    dotIndicator.setHighlightPosition(currentScreen);
    adjustScreens();
}

void SwipeContainer::handleTickEvent(){
	switch(currentState){
	case ANIMATE_SWIPE_CANCELLED_LEFT:
		animateSwipeCancelledLeft();
		break;
	case ANIMATE_SWIPE_CANCELLED_RIGHT:
		animateSwipeCancelledRight();
		break;
	case ANIMATE_LEFT:
		animateLeft();
		break;
	case ANIMATE_RIGHT:
		animateRight();
		break;
	}
}

void SwipeContainer::handleClickEvent(const ClickEvent& event) {
	if(currentState != NO_ANIMATION){
		return;
	}

	if(event.getClickEventType() == ClickEvent::RELEASED){
		animateDistance = dragX;
		startX = screens.getX();
		if(dragX < 0){
			if(currentScreen == getNumberOfScreens() - 1 || dragX > -swipeCutoff){
				currentState = ANIMATE_SWIPE_CANCELLED_LEFT;
			} else {
				currentState = ANIMATE_LEFT;
				if(menuChangeInitiatedAction && menuChangeInitiatedAction->isValid()){
					menuChangeInitiatedAction->execute(*this);
				}
			}
		} else if(dragX > 0) {
			if(currentScreen == 0 || dragX < swipeCutoff){
				currentState = ANIMATE_SWIPE_CANCELLED_RIGHT;
			} else {
				currentState = ANIMATE_RIGHT;
				if(menuChangeInitiatedAction && menuChangeInitiatedAction->isValid()){
					menuChangeInitiatedAction->execute(*this);
				}
			}
		}

	}
}

void SwipeContainer::handleDragEvent(const DragEvent& event){
	if(currentState != NO_ANIMATION){
		return;
	}
	dragX += event.getDeltaX();
	if(currentScreen == 0 && dragX > endElasticWidth){
		dragX = endElasticWidth;
	} else if ( currentScreen == getNumberOfScreens() - 1 && dragX < -endElasticWidth){
		dragX = -endElasticWidth;
	}
	adjustScreens();
}

void SwipeContainer::handleGestureEvent(const GestureEvent& event) {
	if (currentState != NO_ANIMATION) {
		return;
	}
	if (event.getType() == GestureEvent::SWIPE_HORIZONTAL) {
		animateDistance = dragX;
		startX = screens.getX();
		if (event.getVelocity() < 0 && currentScreen < getNumberOfScreens() - 1) {
			currentState = ANIMATE_LEFT;

			if (menuChangeInitiatedAction && menuChangeInitiatedAction->isValid()) {
				menuChangeInitiatedAction->execute(*this);
			}
		} else if (event.getVelocity() > 0 && currentScreen > 0) {
			currentState = ANIMATE_RIGHT;

			if (menuChangeInitiatedAction && menuChangeInitiatedAction->isValid()) {
				menuChangeInitiatedAction->execute(*this);
			}
		}
	}
}

void SwipeContainer::animateSwipeCancelledLeft() {
	uint8_t duration = 14;

	if (animationCounter <= duration) {
		int16_t delta = EasingEquations::linear(animationCounter, 0, -animateDistance, duration);
		dragX = animateDistance + delta;

		adjustScreens();
	} else {
		// Final step: stop the animation
		currentState = NO_ANIMATION;
		animationCounter = 0;
		dragX = 0;
		adjustScreens();
	}
	animationCounter++;
}

void SwipeContainer::animateSwipeCancelledRight() {
	uint8_t duration = 14;

	if (animationCounter <= duration) {
		int16_t delta = EasingEquations::linear(animationCounter, 0, animateDistance, duration);
		dragX = animateDistance - delta;

		adjustScreens();
	} else {
		// Final step: stop the animation
		currentState = NO_ANIMATION;
		animationCounter = 0;
		dragX = 0;
		adjustScreens();
	}
	animationCounter++;
}

void SwipeContainer::animateLeft() {
	uint8_t duration = 10;

	if (animationCounter <= duration) {
		int16_t delta = EasingEquations::linear(animationCounter, 0, getWidth() + animateDistance, duration);
		dragX = animateDistance - delta;

		adjustScreens();
	} else {
		// Final step: stop the animation
		currentState = NO_ANIMATION;

		animationCounter = 0;
		currentScreen++;
		dragX = 0;
		adjustScreens();
		dotIndicator.goRight();

		if (menuChangeEndedAction && menuChangeEndedAction->isValid()) {
			menuChangeEndedAction->execute(*this);
		}
	}
	animationCounter++;
}

void SwipeContainer::animateRight() {
	uint8_t duration = 10;

	if (animationCounter <= duration) {
        int16_t delta = EasingEquations::linear(animationCounter, 0, getWidth() - animateDistance, duration);
		dragX = animateDistance + delta;

		adjustScreens();
	} else {
		// Final step: stop the animation
		currentState = NO_ANIMATION;
		animationCounter = 0;
		currentScreen--;
		dragX = 0;
		adjustScreens();
		dotIndicator.goLeft();

		if (menuChangeEndedAction && menuChangeEndedAction->isValid()) {
			menuChangeEndedAction->execute(*this);
		}
	}
	animationCounter++;
}

