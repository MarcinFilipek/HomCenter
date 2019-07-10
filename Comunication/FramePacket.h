/*
 * FramePacket.h
 *
 *  Created on: 5 mar 2018
 *      Author: Uzume
 */

#ifndef COMUNICATION_FRAMEPACKET_H_
#define COMUNICATION_FRAMEPACKET_H_

#include "stdint.h"

static const uint8_t MAX_BUFFER_LENGHT = 24 - 1;

typedef struct {
	int32_t senderAddress;
	int32_t buffer[MAX_BUFFER_LENGHT];
} SFrame;

typedef struct {
	int16_t command;
	int16_t data;
} SPacket;

typedef struct{
	uint8_t dest;
	SFrame frame;
}STXFrame;



#endif /* COMUNICATION_FRAMEPACKET_H_ */
