/*
 * Partition.h
 *
 *  Created on: 27 kwi 2017
 *      Author: Uzume
 */

#ifndef PARTITION_PARTITION_H_
#define PARTITION_PARTITION_H_

#include "../Meta/Meta.h"
#include "../AbstractPartition/AbstractPartition.h"

template<typename ListOfTypes, uint16_t NUMBER_OF_ELEMENTS>
class Partition : public AbstractPartition{
public:
	typedef ListOfTypes SupportedTypeList;
	enum {
		INTS_PR_ELEMENT = (sizeof(typename select_type_maxsize<SupportedTypeList>::type) + sizeof(int32_t) - 1) / sizeof(int32_t),
		SIZE_OF_ELEMENT = INTS_PR_ELEMENT * sizeof(int32_t)
	};
	Partition() : AbstractPartition(){
	}
	virtual ~Partition(){
	}
	uint16_t capacity() const{
		return NUMBER_OF_ELEMENTS;
	}
	uint32_t element_size(){
		return sizeof(stBlocks[0]);
	}
protected:
	void* element(uint16_t index){
		return &stBlocks[index];
	}
	const void* element(uint16_t index) const{
		return &stBlocks[index];
	}
private:
	struct Block{
		int32_t filler[INTS_PR_ELEMENT];
	};
	Block stBlocks[NUMBER_OF_ELEMENTS];
};

#endif /* PARTITION_PARTITION_H_ */
