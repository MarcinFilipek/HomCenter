/*
 * Device.h
 *
 *  Created on: 28 lut 2018
 *      Author: Uzume
 */

#ifndef DEVICES_DEVICE_DEVICE_H_
#define DEVICES_DEVICE_DEVICE_H_

#include "../Interfaces/IDevice.h"

class Device: public IDevice{
public:
	typedef struct{
		ComVar rejestruj;
		ComVar whoUAre1_1;
		ComVar whoUAre1_2;
		ComVar whoUAre2_1;
		ComVar whoUAre2_2;
		ComVar whoUAre3_1;
		ComVar whoUAre3_2;
		ComVar softVersion;
		ComVar address;
		ComVar typUrzadzenia;
	}DeviceData;
	static const uint8_t ADRESS_UNREGISTERED = 0x12;
	Device();
	virtual ~Device();
	virtual uint8_t getType() override;
	void registration(uint8_t adr);
	ComVar* getCommTable();
	uint8_t getLenTable(void);
	void procPacket(int16_t command, int16_t data);
private:
	DeviceData deviceData;
};

#endif /* DEVICES_DEVICE_DEVICE_H_ */
