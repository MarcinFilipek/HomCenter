/*
 * Switch.cpp
 *
 *  Created on: 28 lut 2018
 *      Author: Uzume
 */

#include "Switch.h"
#include "CommandsDeviceSwitch.h"

Switch::Switch() {
	deviceData.relay1.work.init(CommandsDeviceSwitch::CMD_ON_OFF_RELAY_1);
	deviceData.relay2.work.init(CommandsDeviceSwitch::CMD_ON_OFF_RELAY_2);
}

Switch::~Switch() {
}

uint8_t Switch::getType(){
	return (uint8_t)DEVICE_SWITCH;
}

void Switch::setAdress(uint8_t a){
	address = a;
}

ComVar* Switch::getCommTable(){
	return (ComVar*)&deviceData;
}

uint8_t Switch::getLenTable(void){
	return sizeof(DeviceData)/sizeof(ComVar);
}

void Switch::procPacket(int16_t command, int16_t data) {
	(void)command;
	(void)data;
}

void Switch::toggleRelay1(void){
	deviceData.relay1.work = !deviceData.relay1.work;
}

void Switch::toggleRelay2(void){
	deviceData.relay2.work = !deviceData.relay2.work;
}

bool Switch::getStateRelay1(void){
	return deviceData.relay1.work;
}

bool Switch::getStateRelay2(void){
	return deviceData.relay2.work;
}
