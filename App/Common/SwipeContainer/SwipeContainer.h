/*
 * SwipeContainer.h
 *
 *  Created on: 25 sie 2017
 *      Author: Uzume
 */

#ifndef APP_COMMON_SWIPECONTAINER_SWIPECONTAINER_H_
#define APP_COMMON_SWIPECONTAINER_SWIPECONTAINER_H_

#include "../../../Touch/Container/Container.h"
#include "../../../Touch/ListLayout/ListLayout.h"
#include "../DotIndicator/DotIndicator.h"
#include "../../../Touch/Callback/Callback.h"

class SwipeContainer : public Container {
public:
	SwipeContainer();
	virtual ~SwipeContainer();
	void add(Drawable* screen);
	void setSwipeCutoff(uint16_t cutoff);
	void setEndSwipeElasticWidth(uint16_t width);
	void setDotIndicatorBitmaps(const Bitmap& normalDot, const Bitmap& highlightedDot);
	void setDotIndicatorXY(uint16_t x, uint16_t y);
	void setDotIndicatorXYWithCenteredX(uint16_t x, uint16_t y);
	void setMenuChangeInitiatedCallback(GenericCallback<const SwipeContainer&>& callback);
	void setMenuChangeEndedCallback(GenericCallback<const SwipeContainer&>& callback);
	void setSelectedScreen(uint8_t screenIndex);
	void handleTickEvent();
	void handleClickEvent(const ClickEvent& event);
    void handleDragEvent(const DragEvent& event);
    void handleGestureEvent(const GestureEvent& event);
    uint8_t getNumberOfScreens();
private:
    enum States{
        ANIMATE_SWIPE_CANCELLED_LEFT,
        ANIMATE_SWIPE_CANCELLED_RIGHT,
        ANIMATE_LEFT,
        ANIMATE_RIGHT,
        NO_ANIMATION
    } currentState;
	uint8_t numOfScreens;
	uint8_t animationCounter;
	uint8_t currentScreen;
	uint16_t swipeCutoff;
	int16_t dragX;
	int16_t animateDistance;
	int16_t startX;
	uint16_t endElasticWidth;
	ListLayout screens;
	DotIndicator dotIndicator;

	GenericCallback<const SwipeContainer&>* menuChangeInitiatedAction;
	GenericCallback<const SwipeContainer&>* menuChangeEndedAction;

	void adjustScreens();

    void animateSwipeCancelledLeft();
    void animateSwipeCancelledRight();
    void animateLeft();
    void animateRight();
};

#endif /* APP_COMMON_SWIPECONTAINER_SWIPECONTAINER_H_ */
