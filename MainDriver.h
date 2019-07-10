/*
 * MainDriver.h
 *
 *  Created on: 24 sie 2017
 *      Author: Uzume
 */

#ifndef MAINDRIVER_H_
#define MAINDRIVER_H_

#include "Touch/Touch.h"
#include "Comunication/Communication.h"
#include "Devices/DeviceRegister/DeviceRegister.h"

class MainDriver {
public:
	MainDriver();
	virtual ~MainDriver();
	void init(void);
	void start(void);
private:
	DeviceRegister deviceRegister;
	Touch touch;
	Communication communication;
};

#endif /* MAINDRIVER_H_ */
