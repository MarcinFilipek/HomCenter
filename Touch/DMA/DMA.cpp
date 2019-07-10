/*
 * DMA.cpp
 *
 *  Created on: 30 sie 2016
 *      Author: Uzume
 */

#include "DMA.h"
#include "cmsis_os.h"
#include "../Touch.h"

volatile bool DMA::m_isRunning;
DMA2D_HandleTypeDef DMA::m_dma2dHandle;

DMA::DMA() {
	m_actualOp = NULL;
}
void DMA::initialize() {
	__HAL_RCC_DMA2D_CLK_ENABLE()
	;
	HAL_NVIC_SetPriority(DMA2D_IRQn, 0x05, 0);
	HAL_NVIC_EnableIRQ(DMA2D_IRQn);
}

void DMA::addToQueue(DmaOperation::OpStruct op) {
	m_fifoOperation.addElement(op);
}

bool DMA::isDmaQueueFull(void) {
	if (m_fifoOperation.isFull()) {
		return true;
	} else {
		return false;
	}
}

bool DMA::isDmaQueueEmpty(void) {
	if (m_fifoOperation.isEmpty()) {
		return true;
	} else {
		return false;
	}
}

void DMA::setAllowed(bool set) {
	m_isAllowed = set;
}

bool DMA::getAllowed(void) {
	return m_isAllowed;
}

bool DMA::getDMAIsRunning(void){
	return m_isRunning;
}

void DMA::update(void) {
	osEvent event;
	event = osMailGet(Touch::m_mailLcdToDmaId, osWaitForever);
	if (event.status == osEventMail) {
		m_actualOp = (DmaOperation::OpStruct*)event.value.p;
		if (m_actualOp->operation) {
			execute();
		}
		osMailFree(Touch::m_mailLcdToDmaId, m_actualOp);
	}
}

void DMA::execute() {
	m_isRunning = true;
	m_dma2dHandle.Instance = DMA2D;

	switch (m_actualOp->operation) {
	case DmaOperation::OP_COPY:
		/*Dest*/
		m_dma2dHandle.Init.Mode = DMA2D_M2M;
		m_dma2dHandle.Init.ColorMode = DMA2D_RGB565;
		m_dma2dHandle.Init.OutputOffset = m_actualOp->dstLoopStride;

		m_dma2dHandle.XferCpltCallback  = transferComplete;
		m_dma2dHandle.XferErrorCallback = transferError;

		m_dma2dHandle.LayerCfg[0/*layerIndex*/].AlphaMode = DMA2D_NO_MODIF_ALPHA;
		m_dma2dHandle.LayerCfg[0/*layerIndex*/].InputAlpha = 0xFF;
		m_dma2dHandle.LayerCfg[0/*layerIndex*/].InputColorMode = DMA2D_RGB565;
		m_dma2dHandle.LayerCfg[0/*layerIndex*/].InputOffset = m_actualOp->dstLoopStride;

		m_dma2dHandle.LayerCfg[1/*layerIndex*/].AlphaMode = DMA2D_NO_MODIF_ALPHA;
		m_dma2dHandle.LayerCfg[1/*layerIndex*/].InputAlpha = 0xFF;
		m_dma2dHandle.LayerCfg[1/*layerIndex*/].InputColorMode = DMA2D_RGB565;
		m_dma2dHandle.LayerCfg[1/*layerIndex*/].InputOffset = m_actualOp->srcLoopStride;

		HAL_DMA2D_Init(&m_dma2dHandle);
		HAL_DMA2D_ConfigLayer(&m_dma2dHandle, 0);
		HAL_DMA2D_ConfigLayer(&m_dma2dHandle, 1);
		HAL_DMA2D_Start_IT(&m_dma2dHandle, (uint32_t) m_actualOp->pSrc,
				(uint32_t) m_actualOp->pDst, m_actualOp->nSteps,
				m_actualOp->nLoop);
		break;
	case DmaOperation::OP_FILL:
		m_dma2dHandle.Init.Mode = DMA2D_R2M;
		m_dma2dHandle.Init.ColorMode = DMA2D_ARGB8888;
		m_dma2dHandle.Init.OutputOffset = m_actualOp->dstLoopStride;

		m_dma2dHandle.XferCpltCallback  = transferComplete;
		m_dma2dHandle.XferErrorCallback = transferError;

		m_dma2dHandle.LayerCfg[0/*layerIndex*/].AlphaMode = DMA2D_COMBINE_ALPHA;
		m_dma2dHandle.LayerCfg[0/*layerIndex*/].InputAlpha = m_actualOp->alpha;
		m_dma2dHandle.LayerCfg[0/*layerIndex*/].InputColorMode = DMA2D_ARGB8888;
		m_dma2dHandle.LayerCfg[0/*layerIndex*/].InputOffset = 0;
		HAL_DMA2D_Init(&m_dma2dHandle);
		HAL_DMA2D_ConfigLayer(&m_dma2dHandle, 0);
		HAL_DMA2D_Start_IT(&m_dma2dHandle, m_actualOp->color,
				(uint32_t) m_actualOp->pDst, m_actualOp->nSteps,
				m_actualOp->nLoop);
		break;
	case DmaOperation::OP_COPY_ARGB8888:
		/*Dest*/
		m_dma2dHandle.Init.Mode = DMA2D_M2M_BLEND;
		m_dma2dHandle.Init.ColorMode = DMA2D_RGB565;
		m_dma2dHandle.Init.OutputOffset = m_actualOp->dstLoopStride;
		m_dma2dHandle.XferCpltCallback  = transferComplete;
		m_dma2dHandle.XferErrorCallback = transferError;

		/* Background layer Configuration */
		m_dma2dHandle.LayerCfg[0].InputOffset = m_actualOp->dstLoopStride;
		m_dma2dHandle.LayerCfg[0].InputColorMode = CM_RGB565;
		m_dma2dHandle.LayerCfg[0].AlphaMode = DMA2D_NO_MODIF_ALPHA;
		m_dma2dHandle.LayerCfg[0].InputAlpha = 0xFF;

		/* Foreground layer Configuration : layer 1 */
		m_dma2dHandle.LayerCfg[1].InputOffset = m_actualOp->srcLoopStride;
		m_dma2dHandle.LayerCfg[1].InputColorMode = CM_ARGB8888;
		m_dma2dHandle.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
		m_dma2dHandle.LayerCfg[1].InputAlpha = 0xFF;

		HAL_DMA2D_Init(&m_dma2dHandle);
		HAL_DMA2D_ConfigLayer(&m_dma2dHandle, 0);
		HAL_DMA2D_ConfigLayer(&m_dma2dHandle, 1);
		HAL_DMA2D_BlendingStart_IT(&m_dma2dHandle, (uint32_t) m_actualOp->pSrc,
				(uint32_t) m_actualOp->pDst, (uint32_t) m_actualOp->pDst,
				m_actualOp->nSteps, m_actualOp->nLoop);
		break;
	case DmaOperation::OP_COPY_A8:
		/*Dest*/
		m_dma2dHandle.Init.Mode = DMA2D_M2M_BLEND;
		m_dma2dHandle.Init.ColorMode = (Lcd::getBitDepth() == 32) ? DMA2D_ARGB8888 : (Lcd::getBitDepth() == 24) ? DMA2D_RGB888 : DMA2D_RGB565;
		m_dma2dHandle.Init.OutputOffset = m_actualOp->dstLoopStride;
		m_dma2dHandle.XferCpltCallback  = transferComplete;
		m_dma2dHandle.XferErrorCallback = transferError;

		/* Background layer Configuration */
		m_dma2dHandle.LayerCfg[0].InputOffset = m_actualOp->dstLoopStride;
		m_dma2dHandle.LayerCfg[0].InputColorMode = (Lcd::getBitDepth() == 32) ? CM_ARGB8888 : (Lcd::getBitDepth() == 24) ? CM_RGB888 : CM_RGB565;;
		m_dma2dHandle.LayerCfg[0].AlphaMode = DMA2D_NO_MODIF_ALPHA;
		m_dma2dHandle.LayerCfg[0].InputAlpha = 0xFF;

		/* Foreground layer Configuration : layer 1 */
		m_dma2dHandle.LayerCfg[1].InputOffset = m_actualOp->srcLoopStride;
		m_dma2dHandle.LayerCfg[1].InputColorMode = CM_A8;
		m_dma2dHandle.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
		m_dma2dHandle.LayerCfg[1].InputAlpha = m_actualOp->color;

		HAL_DMA2D_Init(&m_dma2dHandle);
		HAL_DMA2D_ConfigLayer(&m_dma2dHandle, 0);
		HAL_DMA2D_ConfigLayer(&m_dma2dHandle, 1);
		HAL_DMA2D_BlendingStart_IT(&m_dma2dHandle, (uint32_t) m_actualOp->pSrc,
				(uint32_t) m_actualOp->pDst, (uint32_t) m_actualOp->pDst,
				m_actualOp->nSteps, m_actualOp->nLoop);
		break;
	case DmaOperation::OP_COPY_A4:
		/*Dest*/
		m_dma2dHandle.Init.Mode = DMA2D_M2M_BLEND;
		m_dma2dHandle.Init.ColorMode = (Lcd::getBitDepth() == 32) ? DMA2D_ARGB8888 : (Lcd::getBitDepth() == 24) ? DMA2D_RGB888 : DMA2D_RGB565;
		m_dma2dHandle.Init.OutputOffset = m_actualOp->dstLoopStride;
		m_dma2dHandle.XferCpltCallback  = transferComplete;
		m_dma2dHandle.XferErrorCallback = transferError;

		/* Background layer Configuration */
		m_dma2dHandle.LayerCfg[0].InputOffset = m_actualOp->dstLoopStride;
		m_dma2dHandle.LayerCfg[0].InputColorMode = (Lcd::getBitDepth() == 32) ? CM_ARGB8888 : (Lcd::getBitDepth() == 24) ? CM_RGB888 : CM_RGB565;;
		m_dma2dHandle.LayerCfg[0].AlphaMode = DMA2D_NO_MODIF_ALPHA;
		m_dma2dHandle.LayerCfg[0].InputAlpha = 0xFF;

		/* Foreground layer Configuration : layer 1 */
		m_dma2dHandle.LayerCfg[1].InputOffset = m_actualOp->srcLoopStride;
		m_dma2dHandle.LayerCfg[1].InputColorMode = CM_A4;
		m_dma2dHandle.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
		m_dma2dHandle.LayerCfg[1].InputAlpha = m_actualOp->color;

		HAL_DMA2D_Init(&m_dma2dHandle);
		HAL_DMA2D_ConfigLayer(&m_dma2dHandle, 0);
		HAL_DMA2D_ConfigLayer(&m_dma2dHandle, 1);
		HAL_DMA2D_BlendingStart_IT(&m_dma2dHandle, (uint32_t) m_actualOp->pSrc,
				(uint32_t) m_actualOp->pDst, (uint32_t) m_actualOp->pDst,
				m_actualOp->nSteps, m_actualOp->nLoop);
		break;
	default:
		break;
	}
}

void DMA::transferComplete(DMA2D_HandleTypeDef *hdma2d){
	m_isRunning = false;
}

void DMA::transferError(DMA2D_HandleTypeDef *hdma2d)
{
	while(1);
}

DMA2D_HandleTypeDef* DMA::getDMA2DHandle(void){
	return &m_dma2dHandle;
}

