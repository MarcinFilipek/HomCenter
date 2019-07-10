/*
 * Button.cpp
 *
 *  Created on: 26 sie 2016
 *      Author: Uzume
 */

#include "Button.h"
#include "../Lcd/Lcd.h"

Button::Button() : AbstractButton(), m_up(), m_down() {
	m_alpha = 0xFF;
}

Button::~Button() {}

uint16_t Button::getType() const{
	return (uint16_t)TYPE_BUTTON;
}
void Button::setBitmaps(Bitmap up, Bitmap down){
	m_up = up;
	m_down = down;
	setWidth(m_up.getWidth());
	setHeight(m_up.getHeight());
}

void Button::draw(const Rect& invalidatedArea) const{
	Lcd lcd;
	Rect meAbs = getAbsoluteRect();
	Rect dirtyBitmapArea = meAbs & invalidatedArea;
	getVisibleRect(dirtyBitmapArea);
	lcd.drawPartialBitmap(getCurrentlyDisplayedBitmap(), meAbs.m_x, meAbs.m_y, dirtyBitmapArea);
}

uint8_t Button::getAlpha(void){
	return m_alpha;
}

void Button::setAlpha(uint8_t alpha){
	m_alpha = alpha;
}

Bitmap Button::getCurrentlyDisplayedBitmap(void) const{
	return m_pressed ? m_down : m_up;
}
