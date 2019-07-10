/*
 * Room.h
 *
 *  Created on: 23 lut 2018
 *      Author: Uzume
 */

#ifndef HOME_ROOM_ROOM_H_
#define HOME_ROOM_ROOM_H_

#include "../Interfaces/IRoom.h"
#include "../../Devices/DeviceRegister/DeviceRegister.h"

class Room : public IRoom {
public:
	Room(){}
	virtual ~Room(){}
	void setDeviceRegister(DeviceRegister* devRegister);
	bool addDevice();
	IDevice* getDeviceByIndex(uint8_t index);
private:
	uint8_t tabAddressDevice[DeviceRegister::MAX_NUM_OF_DEVICE];
	DeviceRegister* deviceRegister;
};

#endif /* HOME_ROOM_ROOM_H_ */
