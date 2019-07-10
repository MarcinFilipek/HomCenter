/*
 * GestureDetector.cpp
 *
 *  Created on: 7 wrz 2017
 *      Author: Uzume
 */

#include "GestureDetector.h"

GestureDetector::GestureDetector(){
	m_minDistanceMovingLR = 50;
	m_minDistanceMovingUD = 50;
	m_dragX = 0;
	m_dragY = 0;
	m_oldX = 0;
	m_oldY = 0;
}

void GestureDetector::setMinDistanceMovingLeftRight(int8_t d){
	m_minDistanceMovingLR = d;
}

void GestureDetector::setMinDistanceMovingUpDawn(int8_t d){
	m_minDistanceMovingUD = d;
}

void GestureDetector::setActualTouchState(TouchState::State* s){
	if(s->touchDetected == 1){
		m_dragX += (s->touchX[0] - m_oldX);
		m_dragY += (s->touchY[0] - m_oldY);
		//obliczenie wiekszego przyrostu miedzy x a y
		if((m_dragX * m_dragX) > (m_dragY * m_dragY)){
			if(m_dragX < 0 && m_dragX < -m_minDistanceMovingLR){
				s->gestureId = GEST_ID_MOVE_LEFT;
			} else if(m_dragX > 0 && m_dragX > m_minDistanceMovingLR){
				s->gestureId = GEST_ID_MOVE_RIGHT;
			} else {
				s->gestureId = GEST_ID_NO_GESTURE;
			}
		} else {
			if(m_dragY < 0 && m_dragY < -m_minDistanceMovingUD){
				s->gestureId = GEST_ID_MOVE_UP;
			} else if(m_dragY > 0 && m_dragY > m_minDistanceMovingUD){
				s->gestureId = GEST_ID_MOVE_DOWN;
			}
		}
	} else {
		m_dragX = 0;
		m_dragY = 0;
		m_oldX = 0;
		m_oldY = 0;
		s->gestureId = GEST_ID_NO_GESTURE;
	}
}

void GestureDetector::saveOldCord(int16_t x, int16_t y){
	m_oldX = x;
	m_oldY = y;
}
