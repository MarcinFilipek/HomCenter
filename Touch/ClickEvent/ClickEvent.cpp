/*
 * ClickEvent.cpp
 *
 *  Created on: 21 wrz 2016
 *      Author: Uzume
 */

#include "ClickEvent.h"

ClickEvent::ClickEvent(ClickEventType type, uint16_t x, uint16_t y){
	m_clickEventType = type;
	m_x = x;
	m_y = y;
}

ClickEvent::~ClickEvent() {}

Event::EventType ClickEvent::getEventType(void){
	return Event::EVENT_CLICK;
}

void ClickEvent::setClickEventType(ClickEventType clickEventType){
	m_clickEventType = clickEventType;
}

ClickEvent::ClickEventType ClickEvent::getClickEventType(void) const {
	return m_clickEventType;
}

uint16_t ClickEvent::getX(void) const {
	return m_x;
}

uint16_t ClickEvent::getY(void) const {
	return m_y;
}

void ClickEvent::setX(uint16_t x){
	m_x = x;
}

void ClickEvent::setY(uint16_t y){
	m_y = y;
}
