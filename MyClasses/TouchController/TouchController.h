/*
 * TouchController.h
 *
 *  Created on: 20 wrz 2016
 *      Author: Uzume
 */

#ifndef TOUCHCONTROLLER_TOUCHCONTROLLER_H_
#define TOUCHCONTROLLER_TOUCHCONTROLLER_H_

#include "../GestureDetector/GestureDetector.h"

class TouchController {
public:
	typedef enum {
		TS_SWAP_NONE = 1,
		TS_SWAP_X = 2,
		TS_SWAP_Y = 4,
		TS_SWAP_XY = 8
	}TOrientation;

	FT5336 m_ft5336Driver;
	void init(uint16_t sizeX, uint16_t sizeY);
	void itConfig(void);
	void getState(void);
	TouchState::State* getTouchScreenState(void){ return &m_tsState; }
	void getGestureId(void);
	void resetTouchData(void);
	bool isNoTouch(void);
	GestureDetector* getGestureDetector();
private:
	static const uint16_t TS_I2C_ADDRESS = 0x70;
	uint16_t m_sizeX;
	uint16_t m_sizeY;
	TOrientation m_orientation;
	TouchState::State m_tsState;
	GestureDetector m_gestureDetector;
};

#endif /* TOUCHCONTROLLER_TOUCHCONTROLLER_H_ */
