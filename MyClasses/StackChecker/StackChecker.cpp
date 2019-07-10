/*
 * StackChecker.cpp
 *
 *  Created on: 23 cze 2016
 *      Author: Sebastian
 */

#include "StackChecker.h"


	extern const unsigned char __stack_start__[];
	extern const unsigned char __stack_end__[];

int32_t StackChecker::getMaxStackUsage()
{
	uint32_t stackStart = (uint32_t) __stack_start__;
	uint32_t stackEnd = ((uint32_t) __stack_end__);
	uint32_t stacksize = stackEnd - stackStart;

	int32_t stackUsage = stacksize;
	uint8_t * lastStackByte =  (uint8_t*)stackStart;

	while(*lastStackByte == 0xCC)
	{
		stackUsage--;
		lastStackByte++;
	}
	return stackUsage;
}
