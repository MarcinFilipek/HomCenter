/*
 * Model.h
 *
 *  Created on: 21 lut 2018
 *      Author: Uzume
 */

#ifndef APP_MODEL_MODEL_H_
#define APP_MODEL_MODEL_H_

#include "../../Touch/Unicode/Unicode.h"

class ModelListener;

class Model {
public:
	Model();
	virtual ~Model();
	void bind(ModelListener* listener);
	Unicode::UnicodeChar* getBuffor();
	void setBuffer(Unicode::UnicodeChar* buf);
	void clrBuffer(void);
	void setSelectedRoom(uint8_t index);
	uint8_t getSelectedRoom(void);
	void setSelectedDeviceIndex(uint8_t index);
	uint8_t getSelectedDeviceIndex(void);
private:
	static const uint8_t BUFFER_SIZE = 18;
	Unicode::UnicodeChar buffor[BUFFER_SIZE];
	uint8_t selectedRoom;
	uint8_t selectedDeviceIndex;
protected:
	ModelListener* modelListener;
};

#endif /* APP_MODEL_MODEL_H_ */
