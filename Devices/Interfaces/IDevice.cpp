/*
 * IDevice.cpp
 *
 *  Created on: 23 lut 2018
 *      Author: Uzume
 */

#include "IDevice.h"

uint8_t IDevice::getAdress(){
	return address;
}

uint8_t IDevice::getType(){
	return (uint8_t)IDEVICE;
}
