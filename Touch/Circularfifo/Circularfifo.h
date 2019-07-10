/*
 * Circularfifo.h
 *
 *  Created on: 30 sie 2016
 *      Author: Uzume
 */

#ifndef CIRCULARFIFO_CIRCULARFIFO_H_
#define CIRCULARFIFO_CIRCULARFIFO_H_

#include "../DMA_Operation/DmaOperation.h"

class Circularfifo {
public:
	enum{
		MAX = 20
	};

	Circularfifo();
	virtual ~Circularfifo();
	bool isEmpty(void);
	bool isFull(void);

	bool addElement(DmaOperation::OpStruct operation);
	DmaOperation::OpStruct getElement(DmaOperation::OpStruct** pOp);
private:
	DmaOperation::OpStruct m_tab[MAX];
	uint8_t m_readPtr;
	uint8_t m_writePtr;
	uint8_t m_numberOfElements;

	uint8_t getNumberOfElements(void);
};

#endif /* CIRCULARFIFO_CIRCULARFIFO_H_ */
