/*
 * Hardware.cpp
 *
 *  Created on: 9 wrz 2016
 *      Author: Uzume
 */

#include "Hardware.h"
#include "../Touch/Touch.h"
#include <cmsis_os.h>
#include "stm32f7xx_hal.h"
#include "../../Comunication/Spirit/CSpiritApp.h"
#include "../../Comunication/Communication.h"

volatile uint32_t Hardware::m_timeMiliseconds;
TIM_HandleTypeDef TimHandle;

void Hardware::systemClockConfig(void){
	HAL_Init();
	cpuCacheEneble();

	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;
	HAL_StatusTypeDef ret = HAL_OK;

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 432;	//432
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 8;

	ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
	if (ret != HAL_OK) {
		while (1);
	}

	/* Activate the OverDrive to reach the 216 MHz Frequency */
	ret = HAL_PWREx_EnableOverDrive();
	if (ret != HAL_OK) {
		while (1);
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);
	if (ret != HAL_OK) {
		while (1);
	}

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();
	__HAL_RCC_GPIOJ_CLK_ENABLE();
	__HAL_RCC_GPIOK_CLK_ENABLE();
}

void Hardware::mpuConfig(void){
    /* Configure unused area of QSPI region as strongly ordered.
     * This is *important* to avoid unintentional fetches from illegal
     * addresses due to cache/speculation which would halt the MCU.
     */
    HAL_MPU_Disable();
    MPU_Region_InitTypeDef MPU_InitStruct;
    MPU_InitStruct.Enable = MPU_REGION_ENABLE;
    MPU_InitStruct.BaseAddress = 0x90000000;
    MPU_InitStruct.Size = MPU_REGION_SIZE_256MB;
    MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
    MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
    MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
    MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
    MPU_InitStruct.Number = MPU_REGION_NUMBER2;
    MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
    MPU_InitStruct.SubRegionDisable = 0x00;
    MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

    HAL_MPU_ConfigRegion(&MPU_InitStruct);

    /* Configure the MPU attributes as WT for QSPI (used 16Mbytes) */
    MPU_InitStruct.Enable = MPU_REGION_ENABLE;
    MPU_InitStruct.BaseAddress = 0x90000000;
    MPU_InitStruct.Size = MPU_REGION_SIZE_16MB; /* NOTE! Change this if you change QSPI flash size! */
    MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
    MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
    MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
    MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
    MPU_InitStruct.Number = MPU_REGION_NUMBER3;
    MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
    MPU_InitStruct.SubRegionDisable = 0x00;
    MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

    HAL_MPU_ConfigRegion(&MPU_InitStruct);
    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

    //Deactivate speculative/cache access to first FMC Bank to save FMC bandwidth
    FMC_Bank1->BTCR[0] = 0x000030D2;
}
void Hardware::cpuCacheEneble(void){
	  /* Enable I-Cache */

	  SCB_EnableICache();
	  /* Enable D-Cache */
	  SCB_EnableDCache();
}

uint32_t Hardware::getTimeMiliseconds()
{
    return m_timeMiliseconds;
}

//=====================INTERUPS=====================================================
void EXTI15_10_IRQHandler(void) {
	/* EXTI line 15 interrupt detected */
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_15) != RESET) {
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_15);
		CSpiritApp::IRQ_STATUS result = CSpiritApp::interruptHandler();
		if(result == CSpiritApp::TX_DONE){
			osSemaphoreRelease(Communication::osSemaphore_TxSent_Or_MaxRe);
		}
		if(result == CSpiritApp::RX_TIMEOUT || result == CSpiritApp::RX_DONE){
			osSemaphoreRelease(Communication::osSemaphore_Rx_Data_Ready);
		}
	}
	/* EXTI line 13 interrupt detected */
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_13) != RESET)
	{
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);   /* Touch screen interrupt */
		osSemaphoreRelease(Touch::osSemaphoreTouch);
	}
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_11) != RESET) {
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
	}

}

void QUADSPI_IRQHandler(void) {
	HAL_QSPI_IRQHandler(Touch::m_qspi.getQspiHandle());
}

void DMA2D_IRQHandler(void) {
	HAL_DMA2D_IRQHandler(Touch::m_dma.getDMA2DHandle());
	osSemaphoreRelease(Touch::osSemaphoreDmaStopWork);
}

void SysTick_Handler(void) {
	Hardware::m_timeMiliseconds++;
	Touch::tick();
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
	osSystickHandler();
}

void LTDC_IRQHandler(void){
	HAL_LTDC_IRQHandler(Touch::m_lcd.getLtdcHandle());
}

void LTDC_ER_IRQHandler(void){
	HAL_LTDC_IRQHandler(Touch::m_lcd.getLtdcHandle());
}

void HAL_LTDC_LineEvenCallback(LTDC_HandleTypeDef *hltdc){
	if(Touch::m_systemReady){
		if(Touch::USE_VSYNC){
			osSemaphoreRelease(Touch::osSemaphoreVsync);
		}
	}
	HAL_LTDC_ProgramLineEvent(Touch::m_lcd.getLtdcHandle(), Touch::m_lcd.getLtdcHandle()->Init.AccumulatedActiveH + 1);
}
