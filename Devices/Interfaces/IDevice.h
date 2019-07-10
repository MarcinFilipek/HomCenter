/*
 * IDevice.h
 *
 *  Created on: 23 lut 2018
 *      Author: Uzume
 */

#ifndef DEVICES_INTERFACES_IDEVICE_H_
#define DEVICES_INTERFACES_IDEVICE_H_

#include <stdint.h>
#include  "../../Comunication/ComVar/ComVar.h"

class IDevice {
public:
	enum DevType{
		IDEVICE,
		DEVICE,
		DEVICE_SWITCH
	};
	IDevice(): address(0){}
	virtual ~IDevice(){}
	virtual uint8_t getAdress();
	virtual uint8_t getType();
	virtual ComVar* getCommTable()=0;
	virtual uint8_t getLenTable(void)=0;
	virtual void procPacket(int16_t command, int16_t data)=0;
protected:
	uint8_t address;
};

#endif /* DEVICES_INTERFACES_IDEVICE_H_ */
