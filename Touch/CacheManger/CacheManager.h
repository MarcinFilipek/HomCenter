/*
 * CacheManager.h
 *
 *  Created on: 26 paü 2016
 *      Author: Uzume
 */

#ifndef CACHEMANGER_CACHEMANAGER_H_
#define CACHEMANGER_CACHEMANAGER_H_

#include "stdint.h"

class CacheManager {
public:
	CacheManager();
	virtual ~CacheManager();
	static const uint32_t START_CACHE = 0xC0000000;

	//buffory do renderingu
	static const uint32_t FRAME_BUFFER_1 = 0xC0000000; 	//size 522240 [byte]
	static const uint32_t FRAME_BUFFER_2 = 0xC007F800; 	//size 522240 [byte]
	static const uint32_t FRAME_BUFFER_3 = 0xC00FF000; 	//size 522240 [byte]

	//bufor dla uzywanych bitmap
	static const uint32_t BITMAP_CACHE = 0xC017E800; 	//size 2611200 [byte]

//	//bufory czcionek
//	static const uint32_t FONT_CACHE = 0xC037C800; 		//size 20660 [byte]
//
//	//bufor napisow
//	static const uint32_t STRING_CACHE = 0xC03818B4;
	static bool blockCopy(void* __restrict__  dest, const void* __restrict__  src, uint32_t numBytes);
};

#endif /* CACHEMANGER_CACHEMANAGER_H_ */
