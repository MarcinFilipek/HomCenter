/*
 * MainDriver.cpp
 *
 *  Created on: 24 sie 2017
 *      Author: Uzume
 */

#include "MainDriver.h"
#include "Home/Home/Home.h"
#include "MyClasses/CTimer/timer.h"
#include "MyClasses/Hardware/Hardware.h"

MainDriver::MainDriver() {
}

MainDriver::~MainDriver() {
}

void MainDriver::init(void){
	touch.init();
	CTimer::classInit1000(Hardware::getTimeMiliseconds);
	communication.init();
	communication.setDeviceRegiseter(&deviceRegister);
	((Home*)(&Home::getInstance()))->setDeviceRegister(&deviceRegister);
}

void MainDriver::start(void){
	osKernelStart();
}
