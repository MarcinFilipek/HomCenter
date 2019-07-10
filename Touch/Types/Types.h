/*
 * Types.h
 *
 *  Created on: 30 wrz 2016
 *      Author: Uzume
 */

#ifndef TYPES_TYPES_H_
#define TYPES_TYPES_H_

#include "stdint.h"

struct colortype {
	colortype() :
			color(0) {
	}
	colortype(uint32_t c) {
		color = c;
	}
	inline uint32_t getColor32(){
		return color;
	}

    operator uint32_t() const
    {
        return (uint32_t)color;
    }

	uint32_t color;
};


typedef uint8_t Aligment;
static const Aligment LEFT = 0;
static const Aligment CENTER = 1;
static const Aligment RIGHT = 2;

typedef uint8_t TextDirection;
static const TextDirection TEXT_DIRECTION_LTR = 0;
static const TextDirection TEXT_DIRECTION_RTL = 1;

typedef uint16_t TypedTextId;

#endif /* TYPES_TYPES_H_ */
