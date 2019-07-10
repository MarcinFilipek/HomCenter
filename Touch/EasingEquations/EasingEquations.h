/*
 * EasingEquations.h
 *
 *  Created on: 5 wrz 2017
 *      Author: Marcin
 */

#ifndef TOUCH_EASINGEQUATIONS_EASINGEQUATIONS_H_
#define TOUCH_EASINGEQUATIONS_EASINGEQUATIONS_H_

#include "stdint.h"

class EasingEquations {
public:
	static int16_t linear(uint16_t t, int16_t b, int16_t c, uint16_t d);
	static int16_t backEaseOut(uint16_t t, int16_t b, int16_t c, uint16_t d);
	static int16_t cubicEaseOut(uint16_t t, int16_t b, int16_t c, uint16_t d);
private:
	static const float pi = 3.14;
	static inline int16_t roundRespectSign(float resultFloating) {
		return static_cast<int16_t>((resultFloating > 0.0f) ? (resultFloating + 0.5f) : (resultFloating - 0.5f));
	}
};

#endif /* TOUCH_EASINGEQUATIONS_EASINGEQUATIONS_H_ */
