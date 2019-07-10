/*
 * Bitmap.cpp
 *
 *  Created on: 25 sie 2016
 *      Author: Uzume
 */

#include "Bitmap.h"
#include "../Touch.h"
#include "cmsis_os.h"

const Bitmap::BitmapData* Bitmap::bitmaps = 0;
Bitmap::CacheTableEntry* Bitmap::cacheTable = 0;
BitmapId* Bitmap::allocationTable = 0;
uint8_t* Bitmap::nextFreeData = 0;
uint16_t Bitmap::numberOfBitmaps = 0;
uint32_t Bitmap::memoryRemaining = 0;
uint16_t Bitmap::nextAllocationIndex = 0;

Bitmap::Bitmap(BitmapId BitmapId) {
	bitmapId = BitmapId;
	cache(bitmapId);
}

Bitmap::~Bitmap() {
}

void Bitmap::registerBitmapsDatabase(const BitmapData* data, const uint16_t n, uint8_t* startCache, uint32_t cacheSize){
	bitmaps = data;
	numberOfBitmaps = n;
	nextFreeData = startCache;
	memoryRemaining = cacheSize;
	cacheTable = new CacheTableEntry[n];
	allocationTable = new BitmapId[n];
	for(int i = 0; i < n; i++)
		allocationTable[i] = BITMAP_INVALID;
}

bool Bitmap::cache(BitmapId id){
	if( id == BITMAP_INVALID){
		return false;
	}
	bool found = false;
	DmaOperation::OpStruct* op;
	for(uint16_t c = 0; c < numberOfBitmaps; c++){
		if(allocationTable[c] == id){
			found = true;
		}
	}
	if(!found){
		uint32_t size = 0;
		switch(bitmaps[id].format){
		case ARGB8888:
			size = bitmaps[id].height * bitmaps[id].width * 4;
			break;
		case RGB888:
			size = bitmaps[id].height * bitmaps[id].width * 3;
			break;
		case RGB565:
			size = bitmaps[id].height * bitmaps[id].width * 2;
			break;
		}

		if(size> memoryRemaining){
			return false;
		} else {
			op = (DmaOperation::OpStruct*) osMailAlloc(Touch::m_mailLcdToDmaId, osWaitForever);
			op->operation = DmaOperation::OP_COPY;
			op->pDst = nextFreeData;
			op->pSrc = bitmaps[id].data;
			//TODO: Trzeba zrobic obsluge dla RGB888, funkcja COPY przenosi 565,
			if(bitmaps[id].format == RGB565){
				op->nSteps = bitmaps[id].width;
				op->nLoop = bitmaps[id].height;
			} else {
				op->nSteps = bitmaps[id].width * 2;
				op->nLoop = bitmaps[id].height * 2;
			}
			op->srcLoopStride = 0;
			op->dstLoopStride = 0;
			op->color = 0;
			op->alpha = 0xFF;
			osSemaphoreWait(Touch::osSemaphoreDmaStopWork, osWaitForever);
			osMailPut(Touch::m_mailLcdToDmaId, op);
			allocationTable[nextAllocationIndex] = id;
			cacheTable[nextAllocationIndex].data = nextFreeData;
			nextFreeData += size;
			nextAllocationIndex++;
		}
	}

	return true;
}

BitmapId Bitmap::getId(void){
	return bitmapId;
}

const uint8_t* Bitmap::getData() const{
	uint8_t* data = 0;
	uint16_t index = 0;
	BitmapData dataOfBitmap;
	for(uint16_t i = 0; i < numberOfBitmaps; i++){
		if(allocationTable[i] == bitmapId){
			index = i;
		}
	}
	data = cacheTable[index].data;
	return data;
}

uint16_t Bitmap::getWidth() const{
	return bitmaps[bitmapId].width;
}

uint16_t Bitmap::getHeight() const{
	return bitmaps[bitmapId].height;
}

Bitmap::BitmapFormat Bitmap::getFormat() const{
	return (Bitmap::BitmapFormat)bitmaps[bitmapId].format;
}
