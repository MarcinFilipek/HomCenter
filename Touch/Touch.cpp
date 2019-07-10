/*
 * Touch.cpp
 *
 *  Created on: 15 gru 2016
 *      Author: Uzume
 */

#include "Touch.h"

/*
 * System.cpp
 *
 *  Created on: 18 paŸ 2016
 *      Author: Marcin
 */

#include "Touch.h"
#include "stm32f7xx_hal.h"
#include "../MyClasses/Hardware/Hardware.h"
#include "CacheManger/CacheManager.h"
#include "../Touch/Bitmap/Bitmap.h"
#include "FontManager/FontManager.h"

#include "../App/FrontendHeap/FrontendHeap.h"
#include "../ResourcesOut/Images/BitmapDatabase.h"
#include "../ResourcesOut/Texts/TextKeysAndLanguages.h"

CFmcSdram Touch::m_ram;
CQSPIDriver Touch::m_qspi;
TouchController Touch::m_touch;
DMA Touch::m_dma;
Lcd Touch::m_lcd;

osThreadId Touch::LED_BlueThreadId;
osThreadId Touch::DMA_ThreadId;
osThreadId Touch::APP_ThreadId;
osThreadId Touch::TOUCH_ThreadId;
osThreadId Touch::LCD_ThreadId;

osMailQId Touch::m_mailLcdToDmaId;
osMailQId Touch::m_mailInvalidatedArea;

osSemaphoreId Touch::osSemaphoreDmaStopWork;
osSemaphoreId Touch::osSemaphoreVsync;
osSemaphoreId Touch::osSemaphoreTouch;

uint32_t Touch::counterSwitchBuffer = 0;
uint32_t Touch::counterRender = 0;

bool Touch::m_systemReady = false;
const bool Touch::USE_VSYNC = true;
ApplicationFontProvider Touch::fontProvider;

void Touch::init(void){
	hardware();
	rtos();
	Bitmap::registerBitmapsDatabase(BitmapDatabase::getInstance(), BitmapDatabase::getInstanceSize(), (uint8_t*)CacheManager::BITMAP_CACHE, 2611200);
	Texts::setLanguage(PL);
	FontManager::setFontProvider(&fontProvider);

	FrontendHeap& heap = FrontendHeap::getInstance();
	(void)heap;
}
void Touch::hardware(void){
	Hardware::systemClockConfig();
//	itConfig();

	m_ram.init();
	m_qspi.init();
	m_qspi.memoryMappedMode();
	HAL_Delay(500);
	Hardware::mpuConfig();
	m_lcd.initialize(480, 272);
	m_touch.init(480, 272);
	m_dma.initialize();
	m_dma.setAllowed(true);
	FrontendHeap::getInstance().app.initialize();
}

void Touch::rtos(void){
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	osSemaphoreDef(DMA_WORK);
	osSemaphoreDmaStopWork = osSemaphoreCreate(osSemaphore(DMA_WORK), 1);

	osSemaphoreDef(TOUCH);
	osSemaphoreTouch = osSemaphoreCreate(osSemaphore(TOUCH), 1);

	osSemaphoreDef(VSYNC);
	osSemaphoreVsync = osSemaphoreCreate(osSemaphore(VSYNC), 1);

	osMailQDef(DMAQ, 16, DmaOperation::OpStruct);
	m_mailLcdToDmaId = osMailCreate(osMailQ(DMAQ), NULL);

	osMailQDef(INVAREAQ, 15, Rect);
	m_mailInvalidatedArea = osMailCreate(osMailQ(INVAREAQ), NULL);

	osThreadDef(DMA2D, threadDma, osPriorityRealtime, 0, configMINIMAL_STACK_SIZE);
	DMA_ThreadId = osThreadCreate(osThread(DMA2D), NULL);

	osThreadDef(APP, threadApplication, osPriorityBelowNormal, 0, /*configMINIMAL_STACK_SIZE*/ 1024);
	APP_ThreadId = osThreadCreate(osThread(APP), NULL);

	osThreadDef(TOUCH_SCREEN, threadTouch, osPriorityAboveNormal, 0, /*configMINIMAL_STACK_SIZE*/256);
	TOUCH_ThreadId = osThreadCreate(osThread(TOUCH_SCREEN), NULL);

	osThreadDef(LCD_RENDERING, threadLcdBufforRend, osPriorityHigh, 0, configMINIMAL_STACK_SIZE);
	LCD_ThreadId = osThreadCreate(osThread(LCD_RENDERING), NULL);

	m_systemReady = true;
}

void Touch::start(void){
	osKernelStart();
}

void Touch::threadDma(void const* args){
	(void)args;
	for(;;){
		m_dma.update();
	}
}

void Touch::threadApplication(void const* args) {
	(void) args;
	FrontendHeap::getInstance().app.handlePendingScreenTransition();
	for (;;) {
		osEvent event;
		bool zmiana = false;
		event = osMailGet(Touch::m_mailInvalidatedArea, 0);
		if(event.status == osEventMail){
			osSignalSet(Touch::LCD_ThreadId, Touch::SWITCH_BUFFOR);
			zmiana = true;
		} else {
			FrontendHeap::getInstance().app.handlePendingScreenTransition();
		}
		while(event.status == osEventMail){
			Rect invalidateArea = *(Rect*)event.value.p;
			FrontendHeap::getInstance().app.draw(invalidateArea);
			osMailFree(Touch::m_mailInvalidatedArea, event.value.p);
			event = osMailGet(Touch::m_mailInvalidatedArea, 3);
		}
		if(zmiana){
			if(USE_VSYNC){
				osSemaphoreWait(Touch::osSemaphoreVsync, osWaitForever);
			}
			osSignalSet(Touch::LCD_ThreadId, Touch::SHOW_RENDER);
		}
	}
}

void Touch::threadTouch(void const* args) {
	(void) args;
	bool prevtouch = false;
	uint16_t oldX;
	uint16_t oldY;
	for (;;) {
		if (osSemaphoreWait(osSemaphoreTouch, 5) == osOK) {
			m_touch.getState();
			if(!m_touch.isNoTouch() && !prevtouch){
				oldX = m_touch.getTouchScreenState()->touchX[0];
				oldY = m_touch.getTouchScreenState()->touchY[0];
				m_touch.getGestureDetector()->saveOldCord(oldX, oldY);
			}

			if(!m_touch.isNoTouch() && prevtouch){
				m_touch.getGestureDetector()->saveOldCord(oldX, oldY);
				DragEvent eventDrag = DragEvent(oldX, oldY,
						m_touch.getTouchScreenState()->touchX[0],
						m_touch.getTouchScreenState()->touchY[0]);

				if(abs(eventDrag.getDeltaX()) > 10 || abs(eventDrag.getDeltaY()) > 10){
					oldX = m_touch.getTouchScreenState()->touchX[0];
					oldY = m_touch.getTouchScreenState()->touchY[0];
					FrontendHeap::getInstance().app.handleDragEvent(eventDrag);
				} else {
					ClickEvent eventClick = ClickEvent(ClickEvent::PRESSED,
							m_touch.getTouchScreenState()->touchX[0],
							m_touch.getTouchScreenState()->touchY[0]);
					FrontendHeap::getInstance().app.handleClickEvent(eventClick);
				}
			}

			if(m_touch.isNoTouch() && prevtouch){
				ClickEvent eventClick = ClickEvent(ClickEvent::RELEASED,
						m_touch.getTouchScreenState()->touchX[0],
						m_touch.getTouchScreenState()->touchY[0]);
				FrontendHeap::getInstance().app.handleClickEvent(eventClick);

				if(m_touch.getTouchScreenState()->gestureId){
					if(m_touch.getTouchScreenState()->gestureId == 2){
						GestureEvent eventGest = GestureEvent(
								GestureEvent::SWIPE_HORIZONTAL, 10,
								m_touch.getTouchScreenState()->touchX[0],
								m_touch.getTouchScreenState()->touchY[0]);
						FrontendHeap::getInstance().app.handleGestureEvent(eventGest);
					}
					if(m_touch.getTouchScreenState()->gestureId == 4){
						GestureEvent eventGest = GestureEvent(
								GestureEvent::SWIPE_HORIZONTAL, -10,
								m_touch.getTouchScreenState()->touchX[0],
								m_touch.getTouchScreenState()->touchY[0]);
						FrontendHeap::getInstance().app.handleGestureEvent(eventGest);
					}
				}
				m_touch.getGestureDetector()->setActualTouchState(m_touch.getTouchScreenState());
			}
		}
		prevtouch = !m_touch.isNoTouch();
	}
}

void Touch::threadLcdBufforRend(void const* args) {
	(void) args;
	osEvent event;
	uint32_t currentBuffor = CacheManager::FRAME_BUFFER_1;
	uint32_t buffor1 = CacheManager::FRAME_BUFFER_1;
	uint32_t buffor2 = CacheManager::FRAME_BUFFER_2;
	for (;;) {
		event = osSignalWait(SWITCH_BUFFOR, osWaitForever);
		if(event.value.signals == SWITCH_BUFFOR){
			counterSwitchBuffer++;
			if(currentBuffor == buffor1){
				currentBuffor = buffor2;
			} else {
				currentBuffor = buffor1;
			}
			m_lcd.setLayerAddress(0, currentBuffor);
		}
		event = osSignalWait(SHOW_RENDER, osWaitForever);
		if(event.value.signals == SHOW_RENDER){
			m_lcd.switchFrame();
			counterRender++;
			if(currentBuffor == buffor1){
//				CacheManager::blockCopy((void*)buffor2, (void*)buffor1, 480 * 272 * 4);
				m_lcd.copyFrameBufferRegionToMemory((uint8_t*)buffor1, (uint8_t*)buffor2);
			} else {
//				CacheManager::blockCopy((void*)buffor1, (void*)buffor2, 480 * 272 * 4);
				m_lcd.copyFrameBufferRegionToMemory((uint8_t*)buffor2, (uint8_t*)buffor1);
			}
		}
	}
}

void Touch::itConfig(){
	GPIO_InitTypeDef gpioInit;
	gpioInit.Pin = GPIO_PIN_11;
	gpioInit.Pull = GPIO_NOPULL;
	gpioInit.Speed	= GPIO_SPEED_FAST;
	gpioInit.Mode = GPIO_MODE_IT_RISING;
	HAL_GPIO_Init(GPIOI, &gpioInit);

	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0x0F, 0x00);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void Touch::tick(void){
	if(m_systemReady){
		Application::getInstance()->handleTickEvent();
	}
}
