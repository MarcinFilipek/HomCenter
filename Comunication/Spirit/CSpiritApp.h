/*
 * CSpiritApp.h
 *
 *  Created on: 9 lis 2015
 *      Author: marcin
 */

#ifndef CSPIRITAPP_H_
#define CSPIRITAPP_H_

#include "Util/CSpiritUtil.h"
#include "RadioConfParam.h"
#include "../FramePacket.h"

class CSpiritApp {
public:
	typedef enum{
		NONE,
		TX_DONE,
		RX_DONE,
		RX_TIMEOUT
	}IRQ_STATUS;
	CSpiritApp(void);
	void init(uint8_t myaddress);
	void initButtonIrq(void);
	void initP2P(void);
	void dataCommOn(/*uint8_t *pTxBuff, uint8_t cTxlen*/);
	static IRQ_STATUS interruptHandler(void);
	static void setKeyStatus(FlagStatus status);
	void setDestinationAddress(uint8_t address);
	void sendBuff(void);
	static FlagStatus getTxDone(void);
	void setTxFrame(STXFrame* frame);
	void setRxFrame(SFrame* frame);
	void receiveBuff(void);
private:
	uint8_t m_destinationAddress;
	static CSpiritUtil m_spiritDriver;
	CSpiritGpio::SGpioInit m_gpioIRQ;
	CSpiritRadio::SRadioInit m_radioInitStruct;
	FlagStatus m_cmdFlag;
	static FlagStatus m_rxDoneFlag;
	static FlagStatus m_txDoneFlag;
	static FlagStatus m_rxTimeout;
	static FlagStatus m_keyStatus;
	STXFrame* xTxFrame;
	SFrame* xRxFrame;
	static CSpiritIrq::SpiritIrqs m_irqStatus;
	static uint8_t m_txFrameBuff[MAX_BUFFER_LEN];
protected:
};

#endif /* CSPIRITAPP_H_ */
