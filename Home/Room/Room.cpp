/*
 * Room.cpp
 *
 *  Created on: 23 lut 2018
 *      Author: Uzume
 */

#include "Room.h"
#include <new>

void Room::setDeviceRegister(DeviceRegister* devRegister) {
	deviceRegister = devRegister;
}

bool Room::addDevice(){
	uint8_t address = 0;
	deviceRegister->registerDevice(&address);
	tabAddressDevice[numOfDevices] = address;
	numOfDevices++;
}

IDevice* Room::getDeviceByIndex(uint8_t index){
	return deviceRegister->getDeviceByAddress(tabAddressDevice[index]);
}
