/*
 * IRoom.h
 *
 *  Created on: 24 sie 2017
 *      Author: Uzume
 */

#ifndef HOME_INTERFACES_IROOM_H_
#define HOME_INTERFACES_IROOM_H_

#include <stdint.h>
#include "../../Devices/Interfaces/IDevice.h"

class IRoom{
public:
	IRoom(): numOfDevices(0){
	}
	virtual ~IRoom(){}
	virtual bool addDevice() = 0;
	uint8_t getNumOfDevice(){
		return numOfDevices;
	}
	virtual IDevice* getDeviceByIndex(uint8_t index) = 0;
protected:
	uint8_t numOfDevices;
};



#endif /* HOME_INTERFACES_IROOM_H_ */
