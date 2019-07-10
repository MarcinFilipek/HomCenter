/*
 * DMA.h
 *
 *  Created on: 30 sie 2016
 *      Author: Uzume
 */

#ifndef DMA_DMA_H_
#define DMA_DMA_H_

#include "../Circularfifo/Circularfifo.h"
#include "stm32f7xx_hal.h"

class DMA {
public:
	DMA();
	virtual ~DMA(){};
	void initialize(void);
	void addToQueue(DmaOperation::OpStruct op);
	bool isDmaQueueFull(void);
	bool isDmaQueueEmpty(void);

	void setAllowed(bool set);
	bool  getAllowed(void);
	bool getDMAIsRunning(void);
	void update(void);


	static void transferComplete(DMA2D_HandleTypeDef *hdma2d);
	static void transferError(DMA2D_HandleTypeDef *hdma2d);
	static DMA2D_HandleTypeDef* getDMA2DHandle(void);
private:
	Circularfifo m_fifoOperation;
	DmaOperation::OpStruct* m_actualOp;
	static DMA2D_HandleTypeDef m_dma2dHandle;
	static volatile bool m_isRunning;
	volatile bool m_isAllowed;

	void execute(void);

protected:
};

#endif /* DMA_DMA_H_ */
