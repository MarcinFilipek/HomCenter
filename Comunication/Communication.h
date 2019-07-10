/*
 * Communication.h
 *
 *  Created on: 5 mar 2018
 *      Author: Uzume
 */

#ifndef COMUNICATION_COMMUNICATION_H_
#define COMUNICATION_COMMUNICATION_H_

#include "FramePacket.h"
#include "../MyClasses/CLed/CLed.h"
#include "cmsis_os.h"
#include "Spirit/CSpiritApp.h"
#include "../Devices/DeviceRegister/DeviceRegister.h"

class Communication {
public:
	Communication(){}
	virtual ~Communication(){}
	static const int16_t GET_OFFSET = 16383;
	static const uint8_t ADRESS_HOME_CENTER = 0xFF;
	static void txrxCreatorThread(void const*);
	static void txThread(void const*);
	static void rxThread(void const*);
	static void init();
	static void setDeviceRegiseter(DeviceRegister* devRegister);

	static osSemaphoreId osSemaphore_TxSent_Or_MaxRe;
	static osSemaphoreId osSemaphore_Rx_Data_Ready;
private:
	static osMailQId mailTx;
	static osMailQId mailRx;
	static osThreadId txrxCreatorThreadId;
	static osThreadId txThreadId;
	static osThreadId rxThreadId;
	static Led ledBlue;
	static Led ledRed;
	static CSpiritApp spirit;
	static DeviceRegister* deviceRegister;
	static bool test;

	static void initHardware();
	static void createFrame(STXFrame* frame, ComVar* deviceCommTable, uint8_t lengthCommTable);
};

#endif /* COMUNICATION_COMMUNICATION_H_ */
