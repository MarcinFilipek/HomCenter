/*
 * Event.h
 *
 *  Created on: 21 wrz 2016
 *      Author: Uzume
 */

#ifndef EVENT_EVENT_H_
#define EVENT_EVENT_H_

#include "stdint.h"

class Event {
public:
	typedef enum{
		EVENT_CLICK,
		EVENT_DRAG,
		EVENT_GESTURE
	}EventType;
	Event();
	virtual ~Event();
	virtual EventType getEventType(void) = 0;
};

#endif /* EVENT_EVENT_H_ */
