/*
 * Bitmap.h
 *
 *  Created on: 25 sie 2016
 *      Author: Uzume
 */

#ifndef BITMAP_BITMAP_H_
#define BITMAP_BITMAP_H_

#include "stdint.h"
#include "../Rect/Rect.h"

typedef uint32_t BitmapId;
const BitmapId BITMAP_INVALID = 0xFFFFU;

class Bitmap {
public:
    enum BitmapFormat
    {
    	ARGB8888,	//4bajty
		RGB888,		//3bajty
		RGB565,		//2bajty
    };

    struct BitmapData{
    	uint8_t* data;
    	uint16_t width;
    	uint16_t height;
    	uint8_t format;
    };

    struct CacheTableEntry{
    	uint8_t* data;
    };

	Bitmap(BitmapId BitmapId = BITMAP_INVALID);
	virtual ~Bitmap();
	BitmapId getId(void);

	uint16_t getWidth() const;
	uint16_t getHeight() const;
	BitmapFormat getFormat() const;

	static void registerBitmapsDatabase(const BitmapData* data, const uint16_t n, uint8_t* startCache, uint32_t cacheSize);
	static bool cache(BitmapId id);

	BitmapId bitmapId;

	const uint8_t* getData() const;
private:
	static const BitmapData* bitmaps;
	static CacheTableEntry* cacheTable;
	static BitmapId* allocationTable;
	static uint8_t* nextFreeData;
	static uint16_t numberOfBitmaps;
	static uint32_t memoryRemaining;
	static uint16_t nextAllocationIndex;
};

#endif /* BITMAP_BITMAP_H_ */
