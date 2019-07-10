/*
 * TouchState.h
 *
 *  Created on: 7 wrz 2017
 *      Author: Uzume
 */

#ifndef MYCLASSES_TOUCHSTATE_TOUCHSTATE_H_
#define MYCLASSES_TOUCHSTATE_TOUCHSTATE_H_

#include "stdint.h"
#include "../FT5336/FT5336.h"

class TouchState {
public:
	typedef enum
	{
	  TOUCH_EVENT_NO_EVT        = 0x00, /*!< Touch Event : undetermined */
	  TOUCH_EVENT_PRESS_DOWN    = 0x01, /*!< Touch Event Press Down */
	  TOUCH_EVENT_LIFT_UP       = 0x02, /*!< Touch Event Lift Up */
	  TOUCH_EVENT_CONTACT       = 0x03, /*!< Touch Event Contact */
	  TOUCH_EVENT_NB_MAX        = 0x04  /*!< max number of touch events kind */
	} TouchEvent;

	typedef struct {
		uint8_t touchDetected; 											/*!< Total number of active touches detected at last scan */
		uint16_t touchX[FT5336::m_maxDetectableTouch]; 					/*!< Touch X[0], X[1] coordinates on 12 bits */
		uint16_t touchY[FT5336::m_maxDetectableTouch]; 					/*!< Touch Y[0], Y[1] coordinates on 12 bits */
		uint8_t touchWeight[FT5336::m_maxDetectableTouch]; 				/*!< Touch_Weight[0], Touch_Weight[1] : weight property of touches */
		TouchEvent touchEventId[FT5336::m_maxDetectableTouch]; 		/*!< Touch_EventId[0], Touch_EventId[1] : take value of type @ref TS_TouchEventTypeDef */
		uint8_t touchArea[FT5336::m_maxDetectableTouch]; 				/*!< Touch_Area[0], Touch_Area[1] : touch area of each touch */
		uint8_t gestureId; 										/*!< type of gesture detected : take value of type @ref TS_GestureIdTypeDef */
	} State;

	TouchState(){}
	virtual ~TouchState(){}
};

#endif /* MYCLASSES_TOUCHSTATE_TOUCHSTATE_H_ */
