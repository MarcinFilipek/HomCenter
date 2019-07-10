/*
 * DragEvent.cpp
 *
 *  Created on: 4 wrz 2017
 *      Author: Uzume
 */

#include "DragEvent.h"

int16_t DragEvent::getOldX() const{
	return m_oldX;
}

int16_t DragEvent::getOldY() const{
	return m_oldY;
}

int16_t DragEvent::getNewX() const{
	return m_newX;
}

int16_t DragEvent::getNewY() const{
	return m_newY;
}

Event::EventType DragEvent::getEventType(){
	return Event::EVENT_DRAG;
}

int16_t DragEvent::getDeltaX() const{
	return m_newX - m_oldX;
}

int16_t DragEvent::getDeltaY() const{
	return m_newX - m_oldX;
}
