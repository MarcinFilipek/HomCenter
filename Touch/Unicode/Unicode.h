/*
 * Unicode.h
 *
 *  Created on: 3 paü 2016
 *      Author: Uzume
 */

#ifndef UNICODE_UNICODE_H_
#define UNICODE_UNICODE_H_

#include "../Types/Types.h"

class Unicode {
public:
	typedef uint16_t UnicodeChar;
	static uint16_t strncpy(UnicodeChar* __restrict__ dst, const char* __restrict__ src, uint16_t maxchars);
};

#endif /* UNICODE_UNICODE_H_ */
