/*
 * Communication.cpp
 *
 *  Created on: 5 mar 2018
 *      Author: Uzume
 */

#include "Communication.h"

osMailQId Communication::mailTx;
osMailQId Communication::mailRx;
osThreadId Communication::txrxCreatorThreadId;
osThreadId Communication::txThreadId;
osThreadId Communication::rxThreadId;
Led Communication::ledBlue;
Led Communication::ledRed;
CSpiritApp Communication::spirit;
DeviceRegister* Communication::deviceRegister;
osSemaphoreId Communication::osSemaphore_TxSent_Or_MaxRe;
osSemaphoreId Communication::osSemaphore_Rx_Data_Ready;
bool Communication::test = true;

void Communication::init(){
	spirit.init(ADRESS_HOME_CENTER);
	ledBlue.init(GPIOG, GPIO_PIN_7);
	ledBlue.setOff();

	ledRed.init(GPIOI, GPIO_PIN_0);
	ledRed.setOff();

	osMailQDef(TXQ, 16, STXFrame);
	mailTx = osMailCreate(osMailQ(TXQ), NULL);

	osMailQDef(RXQ, 16, SFrame);
	mailRx = osMailCreate(osMailQ(RXQ), NULL);

	osSemaphoreDef(TX);
	osSemaphore_TxSent_Or_MaxRe = osSemaphoreCreate(osSemaphore(TX), 1);

	osSemaphoreDef(RX);
	osSemaphore_Rx_Data_Ready = osSemaphoreCreate(osSemaphore(RX), 1);

	osThreadDef(TXRXCREATOR, txrxCreatorThread, osPriorityBelowNormal, 0, 256/*configMINIMAL_STACK_SIZE*/);
	txrxCreatorThreadId = osThreadCreate(osThread(TXRXCREATOR), NULL);

	osThreadDef(TX, txThread, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	txThreadId = osThreadCreate(osThread(TX), NULL);

	osThreadDef(RX, rxThread, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	rxThreadId = osThreadCreate(osThread(RX), NULL);
}

void Communication::initHardware(){
}

void Communication::setDeviceRegiseter(DeviceRegister* devRegister)
{
	deviceRegister = devRegister;
}

void Communication::txrxCreatorThread(void const* args){
	(void)args;
	IDevice* ptrDevice = 0;
	STXFrame* txFrame;
	SFrame* rxFrame;
	for(;;){
		for(uint8_t i = 0; i < deviceRegister->getNumDevices(); i++)
		{
			//	TX
			ptrDevice = deviceRegister->getDeviceByIndex(i);
			txFrame = (STXFrame*)osMailAlloc(mailTx, osWaitForever);
			createFrame(txFrame, ptrDevice->getCommTable(), ptrDevice->getLenTable());
			txFrame->dest = ptrDevice->getAdress();
			osMailPut(mailTx, txFrame);

			osSemaphoreWait(osSemaphore_TxSent_Or_MaxRe, 2500);
//				RX
			spirit.setRxFrame(rxFrame);
			spirit.receiveBuff();
			osSemaphoreWait(osSemaphore_Rx_Data_Ready, 2500);
			rxFrame = (SFrame*)osMailAlloc(mailRx, osWaitForever);
			test ? rxFrame->senderAddress = 0x12 : rxFrame->senderAddress = 0x01;
			test = false;
			osMailPut(mailRx, rxFrame);
		}
	}
}

void Communication::txThread(void const* args){
	(void)args;
	for(;;){
		osEvent event = osMailGet(mailTx, osWaitForever);
		if(event.status == osEventMail){
			STXFrame frame = *(STXFrame*)event.value.p;
			osMailFree(mailTx, event.value.p);
			spirit.setTxFrame(&frame);
			spirit.sendBuff();
			ledBlue.setToggle();
		}
	}
}

void Communication::rxThread(void const* args) {
	(void) args;
	for (;;) {
		IDevice* ptrDevice = 0;
		osEvent event = osMailGet(mailRx, osWaitForever);
		if (event.status == osEventMail) {
			SFrame frame = *(SFrame*)event.value.p;
			osMailFree(mailRx, event.value.p);
			uint8_t add = deviceRegister->getDeviceByIndex(0)->getAdress();
			ptrDevice = deviceRegister->getDeviceByAddress(frame.senderAddress);
			if(ptrDevice){
				if(ptrDevice->getType() == IDevice::DEVICE){
					deviceRegister->switchDeviceToDeviceOtherType(IDevice::DEVICE_SWITCH, frame.senderAddress);
				} else {
					ptrDevice->procPacket(0, 0);
				}
			}
		}
	}
}

void Communication::createFrame(STXFrame* frame, ComVar* deviceCommTable, uint8_t lengthCommTable){
	int32_t data = 0;
	ComVar* ptrData = deviceCommTable;
//	uint8_t count = 0;
//	for(count = 0; count < lengthCommTable; count++){
//		if(deviceCommTable->wasModified()){ 	//SET
//			data = (ptrData->getCommand() << 16) + ptrData->getData();
//		} else {								//GET
//			data = ((ptrData->getCommand() + GET_OFFSET) << 16) + ptrData->getData();
//		}
//		*(frame->frame.buffer + count) = data;
//		ptrData++;
//	}

	for(uint8_t count =0; count < MAX_BUFFER_LENGHT; count++){
		if(count < lengthCommTable){
			if(ptrData->wasModified()){ 	//SET
				data = (ptrData->getCommand() << 16) + ptrData->getData();
			} else {								//GET
				data = ((ptrData->getCommand() + GET_OFFSET) << 16) + ptrData->getData();
			}
		} else {
			data = 0;
		}
		*(frame->frame.buffer + count) = data;
		ptrData++;
	}
}
