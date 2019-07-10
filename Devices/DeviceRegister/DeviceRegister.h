/*
 * DeviceRegister.h
 *
 *  Created on: 19 wrz 2018
 *      Author: Uzume
 */

#ifndef DEVICES_DEVICEREGISTER_DEVICEREGISTER_H_
#define DEVICES_DEVICEREGISTER_DEVICEREGISTER_H_

#include "../../Devices/Device/Device.h"
#include "../../Devices/Switch/Switch.h"
#include "../../Touch/Meta/Meta.h"
#include "../../Touch/Partition/Partition.h"
#include "../../MyClasses/CTimer/timer.h"

class DeviceRegister {
public:
	static const uint8_t MAX_NUM_OF_ZONE = 6;
	static const uint8_t MAX_NUM_OF_DEVICE = 6;
	typedef TypeList<Device, TypeList<Switch, Nil> > DeviceTypes;
	DeviceRegister();
	virtual ~DeviceRegister(){}
	void registerDevice(uint8_t* addresBack);
	void switchDeviceToDeviceOtherType(IDevice::DevType typ, uint8_t address);
	IDevice* getDeviceByAddress(uint8_t address);
	IDevice* getDeviceByIndex(uint8_t index);
	uint8_t getIndexDeviceByAddress(uint8_t address);
	uint8_t getNumDevices();
private:
	Partition<DeviceTypes,  MAX_NUM_OF_ZONE * MAX_NUM_OF_DEVICE> devices;
	bool tabDeviceSlots[MAX_NUM_OF_ZONE * MAX_NUM_OF_DEVICE];
	CTimer timeoutRegistration;
	uint8_t  addressForAssignment;

	uint8_t getIndexFirstFreeSlot();
	void deleteUnregisterDevices();
	void incrementAddress();
};

#endif /* DEVICES_DEVICEREGISTER_DEVICEREGISTER_H_ */
