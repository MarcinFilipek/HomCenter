/*
 * CacheManager.cpp
 *
 *  Created on: 26 paü 2016
 *      Author: Uzume
 */

#include "CacheManager.h"
#include "string.h"

CacheManager::CacheManager() {
	// TODO Auto-generated constructor stub

}

CacheManager::~CacheManager() {
	// TODO Auto-generated destructor stub
}

bool CacheManager::blockCopy(void* __restrict__  dest, const void* __restrict__  src, uint32_t numBytes){
	bool result = false;
	memcpy(dest,src,numBytes);
	return result;
}
