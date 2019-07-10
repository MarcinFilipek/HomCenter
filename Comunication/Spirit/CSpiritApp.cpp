/*
 * CSpiritApp.cpp
 *
 *  Created on: 9 lis 2015
 *      Author: marcin
 */

#include "CSpiritApp.h"

CSpiritUtil CSpiritApp::m_spiritDriver;
FlagStatus CSpiritApp::m_rxDoneFlag = RESET;
FlagStatus CSpiritApp::m_txDoneFlag = SET;
FlagStatus CSpiritApp::m_rxTimeout = RESET;
FlagStatus CSpiritApp::m_keyStatus = RESET;
uint8_t CSpiritApp::m_txFrameBuff[] = {0x00};
CSpiritIrq::SpiritIrqs CSpiritApp::m_irqStatus;

CSpiritApp::CSpiritApp(){
	m_gpioIRQ={CSpiritGpio::SPIRIT_GPIO_3, CSpiritGpio::SPIRIT_GPIO_MODE_DIGITAL_OUTPUT_LP, CSpiritGpio::SPIRIT_GPIO_DIG_OUT_IRQ};
	m_radioInitStruct = {
			XTAL_OFFSET_PPM,
			BASE_FREQUENCY,
			CHANNEL_SPACE,
			CHANNEL_NUMBER,
			(CSpiritRadio::ModulationSelect)MODULATION_SELECT,
			DATARATE,
			FREQ_DEVIATION,
			BANDWIDTH
	};
	m_cmdFlag = RESET;
	m_destinationAddress = 0x12;
	xRxFrame = NULL;
	xTxFrame = NULL;
}
void CSpiritApp::init(uint8_t myaddress){
	m_spiritDriver.setMyAddress(myaddress);
	m_spiritDriver.init();
//	initButtonIrq();
	initP2P();
}

void CSpiritApp::initButtonIrq(){
	GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;/*GPIO_MODE_IT_FALLING;*/
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    /* Enable and set Button EXTI Interrupt to the lowest priority */
    NVIC_SetPriority(EXTI15_10_IRQn, 0x03);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void CSpiritApp::initP2P(){
	m_spiritDriver.initGpioIrq(&m_gpioIRQ);
	m_spiritDriver.initRadio(&m_radioInitStruct);
	m_spiritDriver.setPower(POWER_INDEX, POWER_DBM);
	m_spiritDriver.packetConfig();
	m_spiritDriver.enableSQI();
	m_spiritDriver.setRssiTH(RSSI_THRESHOLD);
}

/* SPIRIT1 Data Transfer Routine. */
void CSpiritApp::dataCommOn(/*uint8_t *pTxBuff, uint8_t cTxlen*/) {
	receiveBuff();
	if (m_keyStatus) {
		m_keyStatus = RESET;
		xTxFrame->frame.senderAddress = m_spiritDriver.getMyAddress();
		sendBuff();
		receiveBuff();
	}
	if (m_cmdFlag) {
		m_cmdFlag = RESET;
//		xTxFrame->Cmd = ACK_OK;
//		xTxFrame->CmdLen = 0x01;
//		xTxFrame->CmdTag = xRxFrame->CmdTag;
//		xTxFrame->CmdType = APPLI_CMD;
//		xTxFrame->DataBuff = pTxBuff;
//		xTxFrame->DataLen = 20;
//		sendBuff(xTxFrame, xTxFrame->DataLen);
	}
}

/*
 * This function handles the point-to-point packet transmission
 */
void CSpiritApp::sendBuff(){
	uint8_t trxLength = 0;
	trxLength = 96;
	xTxFrame->frame.senderAddress = m_spiritDriver.getMyAddress();
	/* Spirit IRQs enable */
	m_spiritDriver.disableIrq();
	m_spiritDriver.enableTxIrq();
	/* payload length config */
	m_spiritDriver.setPayloadLength(trxLength);
	/* rx timeout config */
	m_spiritDriver.setRxTimeout(RECEIVE_TIMEOUT);
	/* IRQ registers blanking */
	m_spiritDriver.clearIRQ();
	/* destination address */
	m_spiritDriver.setDestinationAddress(xTxFrame->dest);
	/* send the TX command */
	m_spiritDriver.startTX((uint8_t*)&xTxFrame->frame, trxLength, &m_txDoneFlag);
}


/*
 * This function handles the point-to-point packet reception
 */
void CSpiritApp::receiveBuff(){
	m_cmdFlag = RESET;
	/* Spirit IRQs enable */
	m_spiritDriver.disableIrq();
	m_spiritDriver.enableRxIrq();
	/* payload length config */
	m_spiritDriver.setPayloadLength(PAYLOAD_LEN);
	/* rx timeout config */
	m_spiritDriver.setRxTimeout(RECEIVE_TIMEOUT);
	/* IRQ registers blanking */
	m_spiritDriver.clearIRQ();
	/* RX command */
	m_spiritDriver.startRX();
	/* wait for data received or timeout period occured */
//	while ((RESET == m_rxDoneFlag) && (RESET == m_rxTimeout));
//	if (m_rxTimeout == SET) {
//		m_rxTimeout = RESET;
//	} else if (m_rxDoneFlag) {
//		m_rxDoneFlag = RESET;
		m_spiritDriver.getRxPacket((uint8_t *)&xRxFrame, 0);
#if defined(LPM_ENABLE)
#if defined(RF_STANDBY)/*||defined(RF_SLEEP)*/
			wakeupFlag = RESET;
#endif
			Enter_LP_mode();
#endif
//	}
}


void CSpiritApp::setKeyStatus(FlagStatus status){
	m_keyStatus = status;
}

CSpiritApp::IRQ_STATUS CSpiritApp::interruptHandler() {
	m_spiritDriver.getStatusIrq(&m_irqStatus);
	/* Check the SPIRIT TX_DATA_SENT IRQ flag */
	if (m_irqStatus.IRQ_TX_DATA_SENT || m_irqStatus.IRQ_MAX_RE_TX_REACH) {
		return TX_DONE;
	}
	/* Check the SPIRIT RX_DATA_READY IRQ flag */
	else if (m_irqStatus.IRQ_RX_DATA_READY) {
		return RX_DONE;
	}
	/* Check the SPIRIT RX_DATA_DISC IRQ flag */
	else if (m_irqStatus.IRQ_RX_DATA_DISC) {
		/* RX command - to ensure the device will be ready for the next reception */
		if (m_irqStatus.IRQ_RX_TIMEOUT) {
			m_spiritDriver.flushRXFifo();
			return RX_TIMEOUT;
		}
	}
	return NONE;
}

void CSpiritApp::setDestinationAddress(uint8_t address){
	m_destinationAddress = address;
}

FlagStatus CSpiritApp::getTxDone(void){
	return m_txDoneFlag;
}

void CSpiritApp::setTxFrame(STXFrame* frame){
	xTxFrame = frame;
}

void CSpiritApp::setRxFrame(SFrame* frame){
	xRxFrame = frame;
}
