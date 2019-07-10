/*
 * Device.cpp
 *
 *  Created on: 28 lut 2018
 *      Author: Uzume
 */

#include "Device.h"
#include "CommandsDevice.h"

Device::Device() {
	address = ADRESS_UNREGISTERED;
	deviceData.rejestruj.init(CommandsDevice::CMD_REGISTER);
	deviceData.whoUAre1_1.init(CommandsDevice::CMD_WHO_U_ARE1_1);
	deviceData.whoUAre1_2.init(CommandsDevice::CMD_WHO_U_ARE1_2);
	deviceData.whoUAre2_1.init(CommandsDevice::CMD_WHO_U_ARE2_1);
	deviceData.whoUAre2_2.init(CommandsDevice::CMD_WHO_U_ARE2_2);
	deviceData.whoUAre3_1.init(CommandsDevice::CMD_WHO_U_ARE3_1);
	deviceData.whoUAre3_2.init(CommandsDevice::CMD_WHO_U_ARE3_2);
	deviceData.address.init(CommandsDevice::CMD_ADDRESS);
	deviceData.softVersion.init(CommandsDevice::CMD_SOFT_VERSION);
	deviceData.typUrzadzenia.init(CommandsDevice::CMD_TYPE);
}

Device::~Device() {
}

uint8_t Device::getType(){
	return (uint8_t)DEVICE;
}

void Device::registration(uint8_t adr){
	deviceData.rejestruj = true;
	deviceData.address = adr;
}

ComVar* Device::getCommTable(){
	return (ComVar*)&deviceData;
}

uint8_t Device::getLenTable(void){
	return sizeof(DeviceData)/sizeof(ComVar);
}

void Device::procPacket(int16_t command, int16_t data) {
	(void)command;
	(void)data;
}
