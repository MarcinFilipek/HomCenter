/*
 * EasingEquations.cpp
 *
 *  Created on: 5 wrz 2017
 *      Author: Marcin
 */

#include "EasingEquations.h"

int16_t EasingEquations::linear(uint16_t t, int16_t b, int16_t c, uint16_t d){
	float result = c*t/d + b;
	int16_t r = roundRespectSign(result);
	return r;
}
int16_t EasingEquations::backEaseOut(uint16_t t, int16_t b, int16_t c, uint16_t d) {
	float result = c * ((t = t / d - 1) * t * ((1.70158 + 1) * t + 1.70158) + 1) + b;
	int16_t r = roundRespectSign(result);
	return r;
}

int16_t EasingEquations::cubicEaseOut(uint16_t t, int16_t b, int16_t c, uint16_t d){
	t /= d;
	t--;
	int16_t result = c * (t * t * t + 1) + b;
	return result;
}
