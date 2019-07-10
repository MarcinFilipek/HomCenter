/*
 * Screen.h
 *
 *  Created on: 31 sie 2016
 *      Author: Uzume
 */

#ifndef SCREEN_SCREEN_H_
#define SCREEN_SCREEN_H_

#include "../Container/Container.h"


class Screen {
public:
	Screen();
	virtual ~Screen();
	void draw(Rect& rect);
	virtual void setupScreen(void);
	virtual void handleClickEvent(const ClickEvent& event);
	virtual void handleDragEvent(const DragEvent& event);
	virtual void handleGestureEvent(const GestureEvent& event);
    virtual void handleTickEvent();
	virtual void tearDownScreen(void);
	Container& getRootContainer();
protected:
	void add(Drawable* child);
	Container container;
	Drawable* focus;
};

#endif /* SCREEN_SCREEN_H_ */
