/*
 * DmaOperation.h
 *
 *  Created on: 31 sie 2016
 *      Author: Uzume
 */

#ifndef DMA_OPERATION_DMAOPERATION_H_
#define DMA_OPERATION_DMAOPERATION_H_

#include "stdint.h"

class DmaOperation {
public:
	enum Operations{
		OP_NONE = 0,
		OP_COPY = 1,
		OP_FILL = 2,
		OP_COPY_ARGB8888 = 3,
		OP_COPY_A4 = 4,
		OP_COPY_A8 = 5,
	};
	struct OpStruct{
		Operations operation;
		const uint8_t* pSrc;				//pointer to the source
		uint8_t* pDst;				//pointer to the destination
		uint16_t nSteps;			//the number pixels in the line
		uint16_t nLoop;				//the number of lines
		uint16_t srcLoopStride;		//the number of pixels to stride the source after every loop
		uint16_t dstLoopStride;		//the number of pixels to stride the destination after every loop
		uint32_t color;				//color
		uint8_t alpha;				//alpha
	};
};

#endif /* DMA_OPERATION_DMAOPERATION_H_ */
