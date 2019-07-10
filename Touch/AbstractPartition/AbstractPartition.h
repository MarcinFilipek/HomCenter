/*
 * AbstractPartition.h
 *
 *  Created on: 28 kwi 2017
 *      Author: Uzume
 */

#ifndef ABSTRACTPARTITION_ABSTRACTPARTITION_H_
#define ABSTRACTPARTITION_ABSTRACTPARTITION_H_

#include "stdint.h"

class AbstractPartition {
public:
	virtual ~AbstractPartition();
	void* allocate(uint16_t size);
	virtual uint16_t capacity() const = 0;

	template<typename T>
	void* allocate() {
		return allocate(static_cast<uint16_t>(sizeof(T)));
	}

	template<typename T>
	T& at(const uint16_t index){
		return *static_cast< T* >(element(index));
	}

	template<typename T>
	const T& at(const uint16_t index) const{
		return *static_cast< const T* >(element(index));
	}
protected:
	AbstractPartition();
	virtual void* element(uint16_t index) = 0;
	virtual const void* element(uint16_t index) const = 0;
};

#endif /* ABSTRACTPARTITION_ABSTRACTPARTITION_H_ */
