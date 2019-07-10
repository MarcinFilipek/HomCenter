/*
 * GestureEvent.cpp
 *
 *  Created on: 4 wrz 2017
 *      Author: Uzume
 */

#include "GestureEvent.h"

int16_t GestureEvent::getVelocity() const {
	return velocity;
}

GestureEvent::GestureType GestureEvent::getType() const {
	return type;
}

int16_t GestureEvent::getX() const {
	return x;
}

int16_t GestureEvent::getY() const {
	return y;
}

Event::EventType GestureEvent::getEventType() {
	return Event::EVENT_GESTURE;
}
