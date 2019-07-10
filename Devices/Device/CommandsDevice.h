/*
 * CommandsDevice.h
 *
 *  Created on: 28 lut 2018
 *      Author: Uzume
 */

#ifndef DEVICES_DEVICE_COMMANDSDEVICE_H_
#define DEVICES_DEVICE_COMMANDSDEVICE_H_

class CommandsDevice{
public:
	enum Commands{
		CMD_WHO_U_ARE1_1 = 1,	//ID_CPU_1 najstarsze 16 bitow
		CMD_WHO_U_ARE1_2 = 2,	//ID_CPU_1 najmlodsze 16 bitow
		CMD_WHO_U_ARE2_1 = 3,	//ID_CPU_2 najstarsze 16 bitow
		CMD_WHO_U_ARE2_2 = 4,	//ID_CPU_2 najmlodsze 16 bitow
		CMD_WHO_U_ARE3_1 = 5,	//ID_CPU_3 najstarsze 16 bitow
		CMD_WHO_U_ARE3_2 = 6,	//ID_CPU_3 najmlodsze 16 bitow
		CMD_REGISTER = 7,
		CMD_SOFT_VERSION = 8,
		CMD_ADDRESS = 9,
		CMD_TYPE = 10,
	};
};



#endif /* DEVICES_DEVICE_COMMANDSDEVICE_H_ */
