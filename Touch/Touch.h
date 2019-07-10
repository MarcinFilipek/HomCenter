/*
 * Touch.h
 *
 *  Created on: 15 gru 2016
 *      Author: Uzume
 */

#ifndef TOUCH_H_
#define TOUCH_H_

#include "../MyClasses/CLed/CLed.h"
#include "cmsis_os.h"
#include "DMA/DMA.h"
#include "Lcd/Lcd.h"
#include "../MyClasses/FmcSdram/CFmcSdram.h"
#include "../MyClasses/QSPI/CQSPIDriver.h"
#include "../MyClasses/TouchController/TouchController.h"
#include "../ResourcesOut/Fonts/ApplicationFontProvider.h"

class Touch {
public:
	Touch(){};
	virtual ~Touch(){};
	static void init(void);
	static void hardware(void);
	static void rtos(void);
	static void start(void);
	static void threadDma(void const*);
	static void threadApplication(void const*);
	static void threadTouch(void const*);
	static void threadLcdBufforRend(void const*);
	static void tick(void);

	static osMailQId m_mailLcdToDmaId;
	static osMailQId m_mailInvalidatedArea;
	static osSemaphoreId osSemaphoreDmaStopWork;
	static osSemaphoreId osSemaphoreVsync;
	static osSemaphoreId osSemaphoreTouch;
	static const uint32_t SIZE_DMA_QUEUE = 20;
	static osThreadId LED_BlueThreadId;
	static osThreadId DMA_ThreadId;
	static osThreadId APP_ThreadId;
	static osThreadId TOUCH_ThreadId;
	static osThreadId LCD_ThreadId;

	static DMA m_dma;
	static Lcd m_lcd;
	static CFmcSdram m_ram;
	static CQSPIDriver m_qspi;
	static TouchController m_touch;
	static ApplicationFontProvider fontProvider;
	static void itConfig();
	static bool m_systemReady;
	static const bool USE_VSYNC;

	static const int32_t SWITCH_BUFFOR = 1;
	static const int32_t SHOW_RENDER = 2;
	static uint32_t counterSwitchBuffer;
	static uint32_t counterRender;
};

#endif /* TOUCH_H_ */
