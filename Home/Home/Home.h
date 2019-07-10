/*
 * Home.h
 *
 *  Created on: 24 sie 2017
 *      Author: Uzume
 */

#ifndef HOME_HOME_HOME_H_
#define HOME_HOME_HOME_H_

#include "../Interfaces/IHome.h"
#include "../Room/Room.h"
#include "../../Devices/DeviceRegister/DeviceRegister.h"

class Home: public IHome {
public:
	static const uint8_t MAX_NUM_OF_ROOM = 6;
	virtual ~Home(){}
	void addRoom();
	static IHome& getInstance();
	Room* getRoom(int8_t index);
	void setDeviceRegister(DeviceRegister* devRegister);
private:
	Home(){}
	Room rooms[MAX_NUM_OF_ROOM];
	DeviceRegister* deviceRegister;
};

#endif /* HOME_HOME_HOME_H_ */
