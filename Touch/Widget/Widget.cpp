/*
 * Widget.cpp
 *
 *  Created on: 10 sie 2017
 *      Author: Uzume
 */

#include "Widget.h"

Widget::Widget() {
}

Widget::~Widget() {
}

void Widget::getLastChild(int16_t x, int16_t y, Drawable** last){
	if(isVisible() && isTouchable()){
		*last = this;
	}
}
