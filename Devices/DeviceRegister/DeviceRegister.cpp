/*
 * DeviceRegister.cpp
 *
 *  Created on: 19 wrz 2018
 *      Author: Uzume
 */

#include "DeviceRegister.h"
#include <new>
#include "string.h"

DeviceRegister::DeviceRegister():
addressForAssignment(0x01)
{
	memset(tabDeviceSlots, 0, MAX_NUM_OF_ZONE * MAX_NUM_OF_DEVICE);
}

void DeviceRegister::registerDevice(uint8_t* addresBack) {
	uint8_t index = getIndexFirstFreeSlot();
	Device* newDevice = new(&devices.at<Device>(index)) Device;
	tabDeviceSlots[index] = true;
	*addresBack = addressForAssignment;
	newDevice->registration(addressForAssignment);
	timeoutRegistration.start(60);
}

void DeviceRegister::switchDeviceToDeviceOtherType(IDevice::DevType typ, uint8_t address){
	int8_t index = getIndexDeviceByAddress(address);
	switch (typ) {
	case IDevice::DEVICE_SWITCH:
		new (&devices.at<Switch>(index)) Switch;
		((Switch*)(getDeviceByIndex(index)))->setAdress(addressForAssignment);
		incrementAddress();
		break;
	default:
		break;
	}
}

IDevice* DeviceRegister::getDeviceByAddress(uint8_t address) {
	uint8_t numOfDevices = getNumDevices();
	for (uint8_t i = 0; i < numOfDevices; i++) {
		if (devices.at<IDevice>(i).getAdress() == address) {
			return &devices.at<IDevice>(i);
		}
	}
	return NULL;
}

IDevice* DeviceRegister::getDeviceByIndex(uint8_t index){
	uint8_t numOfDevices = getNumDevices();
	if(numOfDevices > 0){
		return &devices.at<IDevice>(index);
	} else {
		return NULL;
	}
}

uint8_t DeviceRegister::getIndexDeviceByAddress(uint8_t address){
	for(uint8_t i = 0; i < MAX_NUM_OF_ZONE * MAX_NUM_OF_DEVICE; i++){
		if(tabDeviceSlots[i] == true){
			if(getDeviceByIndex(i)->getAdress() == address){
				return i;
			}
		}
	}
}

uint8_t DeviceRegister::getNumDevices(){
	uint8_t sum = 0;
	for(uint8_t i = 0; i < MAX_NUM_OF_ZONE * MAX_NUM_OF_DEVICE; i++){
		if(tabDeviceSlots[i] == true){
			sum++;
		}
	}
	return sum;
}

void DeviceRegister::deleteUnregisterDevices(){
	for(uint8_t i = 0; i < MAX_NUM_OF_ZONE * MAX_NUM_OF_DEVICE; i++){
		if(tabDeviceSlots[i] && getDeviceByIndex(i)->getType() == IDevice::DEVICE){
			tabDeviceSlots[i] = false;
		}
	}
}

uint8_t DeviceRegister::getIndexFirstFreeSlot(){
	for(uint8_t i = 0; i < MAX_NUM_OF_ZONE * MAX_NUM_OF_DEVICE; i++){
		if(!tabDeviceSlots[i]){
			return i;
		}
	}
	while(1);
}

void DeviceRegister::incrementAddress(){
	addressForAssignment++;
}
