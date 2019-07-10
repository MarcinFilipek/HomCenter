/*
 * main.cpp
 *
 *  Created on: 18 paü 2016
 *      Author: Marcin
 */


#include "MainDriver.h"
#include "../MyClasses/StackChecker/StackChecker.h"

int main(void)
{
	static MainDriver mainDriver;
	mainDriver.init();
	uint32_t s = StackChecker::getMaxStackUsage();
	mainDriver.start();
	for(;;);
}
