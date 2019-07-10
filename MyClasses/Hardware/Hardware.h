/*
 * Hardware.h
 *
 *  Created on: 9 wrz 2016
 *      Author: Uzume
 */

#ifndef HARDWARE_HARDWARE_H_
#define HARDWARE_HARDWARE_H_

#include "stdint.h"

class Hardware {
public:
	Hardware(){};
	virtual ~Hardware(){};
	static void systemClockConfig(void);
	static void mpuConfig(void);
	static void cpuCacheEneble(void);
	static uint32_t getTimeMiliseconds(void);

	static volatile uint32_t m_timeMiliseconds;
};

//=====================INTERUPS======================
extern "C" void EXTI15_10_IRQHandler(void);
extern "C" void QUADSPI_IRQHandler(void);
extern "C" void DMA2D_IRQHandler(void);
extern "C" void SysTick_Handler(void);
extern "C" void LTDC_IRQHandler(void);
extern "C" void LTDC_ER_IRQHandler(void);
#endif /* HARDWARE_HARDWARE_H_ */
