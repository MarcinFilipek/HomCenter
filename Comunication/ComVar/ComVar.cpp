/*
 * ComVar.cpp
 *
 *  Created on: 28 lut 2018
 *      Author: Uzume
 */

#include "ComVar.h"

ComVar::ComVar() :
		m_command(0),
		m_data(0),
		m_modified(false)
{
}

ComVar::~ComVar(){

}
void ComVar::init(int16_t command){
	m_command = command;
}

int16_t ComVar::getCommand(){
	return m_command;
}

int16_t ComVar::getData(){
	m_modified = false;
	return m_data;
}

void ComVar::operator=(int16_t data){
	if(m_data != data){
		m_data = data;
		m_modified = true;
	}
}

ComVar::operator uint16_t(){
	return m_data;
}

void ComVar::setFromComm(int16_t data){
	if(m_data != data){
		m_data = data;
	}
}

bool ComVar::wasModified(){
	return m_modified;
}

