/*
 * GestureEvent.h
 *
 *  Created on: 4 wrz 2017
 *      Author: Uzume
 */

#ifndef TOUCH_GESTUREEVENT_GESTUREEVENT_H_
#define TOUCH_GESTUREEVENT_GESTUREEVENT_H_

#include "../Event/Event.h"

class GestureEvent: public Event {
public:
	typedef enum {
		SWIPE_HORIZONTAL, SWIPE_VERTICAL
	} GestureType;

	GestureEvent(GestureType t, int16_t v, int16_t x_coord, int16_t y_coord) :
			type(t), velocity(v), x(x_coord), y(y_coord) {

	}
	virtual ~GestureEvent() {
	}
	int16_t getVelocity() const;
	GestureType getType() const;
	int16_t getX() const;
	int16_t getY() const;
	Event::EventType getEventType();
private:
	GestureEvent() {}
	GestureType type;
	int16_t velocity;
	int16_t x;
	int16_t y;
};

#endif /* TOUCH_GESTUREEVENT_GESTUREEVENT_H_ */
