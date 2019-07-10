/*
 * AbstractButton.cpp
 *
 *  Created on: 21 wrz 2016
 *      Author: Uzume
 */

#include "AbstractButton.h"

AbstractButton::AbstractButton() {
	setTouchable(true);
	m_pressed = false;
	action = 0;
}

AbstractButton::~AbstractButton() {
	// TODO Auto-generated destructor stub
}

uint16_t AbstractButton::getType() const{
	return (uint16_t)TYPE_ABSTRACTBUTTON;
}

void AbstractButton::handleClickEvent(const ClickEvent& event) {
	if (event.getClickEventType() == ClickEvent::PRESSED) {
		if (getAbsoluteRect().intersect(event.getX(), event.getY()) && !m_pressed) {
			invalidate();
			m_pressed = true;
		}
		if (!getAbsoluteRect().intersect(event.getX(), event.getY()) && m_pressed) {
			invalidate();
			m_pressed = false;
		}
	}
	if(m_pressed && event.getClickEventType() == ClickEvent::RELEASED){
		m_pressed = false;
		if(action && action->isValid()){
			action->execute(*this);
		}
		invalidate();
	}
}

bool AbstractButton::getPressedState(void) {
	return m_pressed;
}

void AbstractButton::setAction(GenericCallback<const AbstractButton&>& callback){
	action = &callback;
}
