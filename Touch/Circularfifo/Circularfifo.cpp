/*
 * Circularfifo.cpp
 *
 *  Created on: 30 sie 2016
 *      Author: Uzume
 */

#include "Circularfifo.h"

Circularfifo::Circularfifo() {
	m_readPtr = 0;
	m_writePtr = 0;
	m_numberOfElements = 0;
	for(uint8_t c = 0;  c < MAX; c++){
		m_tab[c].operation = DmaOperation::OP_NONE;
	}
}

Circularfifo::~Circularfifo() {
}

uint8_t Circularfifo::getNumberOfElements(void) {
	return m_numberOfElements;
}

bool Circularfifo::isEmpty() {
	return m_numberOfElements == 0;
}

bool Circularfifo::isFull() {
	if (getNumberOfElements() == MAX) {
		return true;
	} else {
		return false;
	}
}

bool Circularfifo::addElement(DmaOperation::OpStruct operation) {
	if (!isFull()) {
		if (m_writePtr >= MAX) {
			m_writePtr = 0;
		}

		m_tab[m_writePtr] = operation;
		m_numberOfElements++;

		if (m_writePtr < MAX) {
			m_writePtr++;
		}
		return true;
	} else {
		return false;
	}
}

DmaOperation::OpStruct Circularfifo::getElement(DmaOperation::OpStruct** pOp) {
	DmaOperation::OpStruct element;
	element.operation = DmaOperation::OP_NONE;
	if (!isEmpty()) {
		if (m_readPtr >= MAX)
			m_readPtr = 0;

		element = m_tab[m_readPtr];
		*pOp = &m_tab[m_readPtr];
		if (m_numberOfElements > 0)
			m_numberOfElements--;

		if (m_readPtr < MAX)
			m_readPtr++;
	}
	return element;
}
