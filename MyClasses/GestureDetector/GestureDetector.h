/*
 * GestureDetector.h
 *
 *  Created on: 7 wrz 2017
 *      Author: Uzume
 */

#ifndef MYCLASSES_GESTUREDETECTOR_GESTUREDETECTOR_H_
#define MYCLASSES_GESTUREDETECTOR_GESTUREDETECTOR_H_

#include "../TouchState/TouchState.h"

class GestureDetector {
public:
	typedef enum
	{
	  GEST_ID_NO_GESTURE 		= 0x00, /*!< Gesture not defined / recognized */
	  GEST_ID_MOVE_UP    		= 0x01, /*!< Gesture Move Up */
	  GEST_ID_MOVE_RIGHT 		= 0x02, /*!< Gesture Move Right */
	  GEST_ID_MOVE_DOWN  		= 0x03, /*!< Gesture Move Down */
	  GEST_ID_MOVE_LEFT  		= 0x04, /*!< Gesture Move Left */
	  GEST_ID_ZOOM_IN    		= 0x05, /*!< Gesture Zoom In */
	  GEST_ID_ZOOM_OUT   		= 0x06, /*!< Gesture Zoom Out */
	  GEST_ID_NB_MAX    		= 0x07  /*!< max number of gesture id */
	} GestureId;

	GestureDetector();
	virtual ~GestureDetector(){}
	void setMinDistanceMovingLeftRight(int8_t d);
	void setMinDistanceMovingUpDawn(int8_t d);
	void setActualTouchState(TouchState::State* s);
	void saveOldCord(int16_t x, int16_t y);
private:
	int8_t m_minDistanceMovingLR;
	int8_t m_minDistanceMovingUD;
	int16_t m_dragX;
	int16_t m_dragY;

	int16_t m_oldX;
	int16_t m_oldY;
};

#endif /* MYCLASSES_GESTUREDETECTOR_GESTUREDETECTOR_H_ */
