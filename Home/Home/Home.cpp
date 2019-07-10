/*
 * Home.cpp
 *
 *  Created on: 24 sie 2017
 *      Author: Uzume
 */

#include "Home.h"

void Home::addRoom(){
	rooms[numOfRoom].setDeviceRegister(deviceRegister);
	numOfRoom++;
}

void Home::setDeviceRegister(DeviceRegister* devRegister){
	deviceRegister = devRegister;
}

IHome& Home::getInstance(){
	static Home instance;
	return instance;
}

Room* Home::getRoom(int8_t index){
	return &rooms[index];
}
