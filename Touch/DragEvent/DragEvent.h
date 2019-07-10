/*
 * DragEvent.h
 *
 *  Created on: 4 wrz 2017
 *      Author: Uzume
 */

#ifndef TOUCH_DRAGEVENT_DRAGEVENT_H_
#define TOUCH_DRAGEVENT_DRAGEVENT_H_

#include "../Event/Event.h"

class DragEvent: public Event {
public:
	DragEvent(int16_t oldX, int16_t oldY, int16_t newX, int16_t newY) :
			m_oldX(oldX), m_oldY(oldY), m_newX(newX), m_newY(newY) {

	}
	virtual ~DragEvent(){

	}
	int16_t getOldX() const;
	int16_t getOldY() const;
	int16_t getNewX() const;
	int16_t getNewY() const;
	EventType getEventType();

	int16_t getDeltaX() const;
	int16_t getDeltaY() const;
private:
	int16_t m_oldX;
	int16_t m_oldY;
	int16_t m_newX;
	int16_t m_newY;
};

#endif /* TOUCH_DRAGEVENT_DRAGEVENT_H_ */
