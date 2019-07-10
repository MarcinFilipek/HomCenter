/*
 * Widget.h
 *
 *  Created on: 10 sie 2017
 *      Author: Uzume
 */

#ifndef TOUCH_WIDGET_WIDGET_H_
#define TOUCH_WIDGET_WIDGET_H_

#include "../Drawable/Drawable.h"

class Widget : public Drawable{
public:
	Widget();
	virtual ~Widget();
	virtual void getLastChild(int16_t x, int16_t y, Drawable** last);
};

#endif /* TOUCH_WIDGET_WIDGET_H_ */
