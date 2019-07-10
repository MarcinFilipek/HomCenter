/*
 * Switch.h
 *
 *  Created on: 28 lut 2018
 *      Author: Uzume
 */

#ifndef DEVICES_SWITCH_SWITCH_H_
#define DEVICES_SWITCH_SWITCH_H_

#include "../Interfaces/IDevice.h"

class Switch: public IDevice {
public:
	typedef struct{
		struct{
			ComVar work;
		}relay1;
		struct{
			ComVar work;
		}relay2;
	}DeviceData;

	Switch();
	virtual ~Switch();
	uint8_t getType() override;
	void setAdress(uint8_t a);
	ComVar* getCommTable();
	uint8_t getLenTable(void);
	void procPacket(int16_t command, int16_t data);
	void toggleRelay1(void);
	void toggleRelay2(void);
	bool getStateRelay1(void);
	bool getStateRelay2(void);
private:
	DeviceData deviceData;
};

#endif /* DEVICES_SWITCH_SWITCH_H_ */
