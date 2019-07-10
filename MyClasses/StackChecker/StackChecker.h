/*
 * StackChecker.h
 *
 *  Created on: 23 cze 2016
 *      Author: Sebastian
 */

#ifndef L5UI_STACKCHECKER_H_
#define L5UI_STACKCHECKER_H_

#include <stdint.h>
/**
 * Aby Funckja dzialala należy w projekcie zdefiniowac makro INITIALIZE_STACK
 */
class StackChecker
{
public:
	/**
	 *
	 * @return maksimum zużycia stosu od momentu rozpoczecia dzialania programu
	 */
	static int32_t getMaxStackUsage();
};

#endif /* L5UI_STACKCHECKER_H_ */
