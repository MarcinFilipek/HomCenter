/*
 * Screen.cpp
 *
 *  Created on: 31 sie 2016
 *      Author: Uzume
 */

#include "Screen.h"


Screen::Screen() {
	container.setPosition(0, 0, 480, 272);
	focus = 0;
}

Screen::~Screen() {
}

void Screen::add(Drawable* child) {
	container.add(child);
}

void Screen::draw(Rect& rect){
	container.draw(rect);
}

void Screen::setupScreen(void) {
}

void Screen::handleClickEvent(const ClickEvent& event) {
	Drawable* child = 0;
	if(!focus){
		container.getLastChild(event.getX(), event.getY(), &child);
		if(child){
			focus = child;
			if(event.getClickEventType() == ClickEvent::PRESSED){
				focus->handleClickEvent(event);
			}
		}
	} else {
		focus->handleClickEvent(event);
		if(event.getClickEventType() == ClickEvent::RELEASED){
			focus = 0;
		}
	}
}

void Screen::handleDragEvent(const DragEvent& event){
	Drawable* child = 0;
	container.getLastChild(event.getNewX(), event.getNewY(), &child);
	if(child){
		child->handleDragEvent(event);
	}
}

void Screen::handleGestureEvent(const GestureEvent& event){
	Drawable* child = 0;
	container.getLastChild(event.getX(), event.getY(), &child);
	if(child){
		child->handleGestureEvent(event);
	}
}

void Screen::handleTickEvent(){
	void (Drawable::*func)() = &Drawable::handleTickEvent;
	container.forEachChild(func);
}

void Screen::tearDownScreen(void) {
}

Container& Screen::getRootContainer(){
	return container;
}
