/*
 * IHome.h
 *
 *  Created on: 24 sie 2017
 *      Author: Uzume
 */

#ifndef HOME_INTERFACES_IHOME_H_
#define HOME_INTERFACES_IHOME_H_

#include "stdint.h"
#include "IRoom.h"

class IHome {
public:
	IHome();
	virtual ~IHome();
	virtual void addRoom(void) = 0;
	uint8_t getNumOfRoom(){
		return numOfRoom;
	}
	static IHome& getInstance();
	virtual IRoom* getRoom(int8_t index)=0;
protected:
	uint8_t numOfRoom;
};

#endif /* HOME_INTERFACES_IHOME_H_ */
