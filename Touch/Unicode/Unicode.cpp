/*
 * Unicode.cpp
 *
 *  Created on: 3 paŸ 2016
 *      Author: Uzume
 */

#include "Unicode.h"

uint16_t Unicode::strncpy(UnicodeChar* __restrict__ dst, const char* __restrict__ src, uint16_t maxchars){
	while(maxchars > 0){
		*dst = *src;
		dst++;
		src++;
		maxchars--;
	}
	return 0;
}
