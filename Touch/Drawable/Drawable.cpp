/*
 * Drawable.cpp
 *
 *  Created on: 1 wrz 2016
 *      Author: Uzume
 */

#include "Drawable.h"
#include "../Touch.h"
#include "cmsis_os.h"
#include "stddef.h"

Drawable::Drawable() : m_visible(true), m_touchable(false){
	m_nextSibling = NULL;
	m_parent = NULL;

	m_rect.m_x = 0;
	m_rect.m_y = 0;
	m_rect.m_width = 0;
	m_rect.m_height = 0;
}

Drawable::~Drawable() {
	// TODO Auto-generated destructor stub
}

Drawable* Drawable::getNextSibling(void){
	return m_nextSibling;
}

void Drawable::setNextSibling(Drawable* d){
	m_nextSibling = d;
}

void Drawable::setX(int16_t x){
	if(m_rect.m_x != x){
		m_rect.m_x = x;
	}
}

int16_t Drawable::getX(void){
	return m_rect.m_x;
}

void Drawable::setY(int16_t y){
	if(m_rect.m_y != y){
		m_rect.m_y = y;
	}
}

int16_t Drawable::getY(void){
	return m_rect.m_y;
}

void Drawable::setXY(int16_t x, int16_t y){
	setX(x);
	setY(y);
}

void Drawable::setWidth(int16_t width){
	if(m_rect.m_width != width){
		m_rect.m_width = width;
	}
}

int16_t Drawable::getWidth(void){
	return m_rect.m_width;
}

void Drawable::setHeight(int16_t height){
	if(m_rect.m_height != height){
		m_rect.m_height = height;
	}
}

int16_t Drawable::getHeight(void){
	return m_rect.m_height;
}

void Drawable::setPosition(int16_t x, int16_t y, int16_t width, int16_t height){
	setXY(x, y);
	setWidth(width);
	setHeight(height);
}

uint16_t Drawable::getType() const{
	return (uint16_t)TYPE_DRAWABLE;
}

void Drawable::setVisible(bool vis){
	if(m_visible != vis){
		m_visible = vis;
	}
}

void Drawable::setTouchable(bool touch){
	m_touchable = touch;
}

bool Drawable::isVisible(void) const{
	return m_visible;
}

bool Drawable::isTouchable(void) const{
	return m_touchable;
}

void Drawable::setParent(Drawable* parent){
	m_parent = parent;
}

Drawable* Drawable::getParent(void){
	return m_parent;
}

void Drawable::translateRectToAbsolute(Rect& r) const{
	Rect t = getAbsoluteRect();
	r = t;

}
void Drawable::childGeometryChanged(void){
	if(m_parent != NULL)
		m_parent->childGeometryChanged();
}

const Rect& Drawable::getRect(void) const{
	return m_rect;
}

void Drawable::getVisibleRect(Rect& rect) const{
	if(m_parent){
		rect &= m_parent->getAbsoluteRect();
	} else {
		rect = m_rect;
	}
}
Rect Drawable::getAbsoluteRect() const {
	Rect result = Rect(0, 0, 0, 0);
	if (!m_parent) {
		result = Rect(m_rect.m_x, m_rect.m_y, m_rect.m_width, m_rect.m_height);
	} else {
		Rect parentAbsolRect = m_parent->getAbsoluteRect();
		result = Rect(parentAbsolRect.m_x + m_rect.m_x,
				parentAbsolRect.m_y + m_rect.m_y,
				m_rect.m_width,
				m_rect.m_height);
	}
	return result;
}

void Drawable::moveRelative(int16_t x, int16_t y){
	m_rect.m_x += x;
	m_rect.m_y += y;
	invalidate();
}
void Drawable::moveTo(int16_t x, int16_t y) {
	moveRelative(x - m_rect.m_x, y - m_rect.m_y);
}

void Drawable::invalidate(){
	Rect* areaToDraw;
	Rect absCord = getAbsoluteRect();
	int16_t newX = MIN(absCord.m_x, m_oldRect.m_x);
	int16_t newY = MIN(absCord.m_y, m_oldRect.m_y);
	int16_t width = MAX(absCord.right(), m_oldRect.right()) - newX;
	int16_t height = MAX(absCord.bottom(), m_oldRect.bottom()) - newY;

	m_oldRect = absCord;
	areaToDraw = (Rect*)osMailAlloc(Touch::m_mailInvalidatedArea, osWaitForever);
	areaToDraw->m_x = newX;
	areaToDraw->m_y = newY;
	areaToDraw->m_width = width;
	areaToDraw->m_height = height;
	getVisibleRect(*areaToDraw);
	osMailPut(Touch::m_mailInvalidatedArea, areaToDraw);
}
