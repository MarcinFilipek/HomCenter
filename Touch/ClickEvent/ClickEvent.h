/*
 * ClickEvent.h
 *
 *  Created on: 21 wrz 2016
 *      Author: Uzume
 */

#ifndef CLICKEVENT_CLICKEVENT_H_
#define CLICKEVENT_CLICKEVENT_H_

#include "../Event/Event.h"

class ClickEvent : public Event {
public:
    typedef enum
    {
        PRESSED,  ///< An enum constant representing the pressed option
        RELEASED, ///< An enum constant representing the released option
        CANCEL    ///< An enum constant representing the cancel option
    } ClickEventType;

	ClickEvent(ClickEventType type, uint16_t x, uint16_t y);
	virtual ~ClickEvent();
	uint16_t getX(void) const;
	uint16_t getY(void) const;
	void setX(uint16_t x);
	void setY(uint16_t y);
	EventType getEventType(void);
	void setClickEventType(ClickEventType clickEventType);
	ClickEventType getClickEventType(void) const;
private:
	ClickEventType m_clickEventType;
	uint16_t m_x;
	uint16_t m_y;
};

#endif /* CLICKEVENT_CLICKEVENT_H_ */
