/*
 * ComVar.h
 *
 *  Created on: 28 lut 2018
 *      Author: Uzume
 */

#ifndef COMUNICATION_COMVAR_COMVAR_H_
#define COMUNICATION_COMVAR_COMVAR_H_

#include "stdint.h"

class ComVar {
public:
	ComVar();
	virtual ~ComVar();
	void init(int16_t command);
	void operator=(int16_t data);
	operator uint16_t();
	void setFromComm(int16_t data);
	int16_t getCommand(void);
	int16_t getData(void);
	bool wasModified();
private:
	int16_t m_command;
	int16_t m_data;
	bool m_modified;
protected:
};

#endif /* COMUNICATION_COMVAR_COMVAR_H_ */
