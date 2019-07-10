/*
 * Model.cpp
 *
 *  Created on: 21 lut 2018
 *      Author: Uzume
 */

#include "Model.h"
#include "string.h"

Model::Model() : modelListener(0) {
	clrBuffer();
	selectedRoom = 0;
}

Model::~Model() {
}

void Model::bind(ModelListener* listener){
	modelListener = listener;
}

Unicode::UnicodeChar* Model::getBuffor(){
	return buffor;
}

void Model::setBuffer(Unicode::UnicodeChar* buf){
	Unicode::UnicodeChar* temp = buf;
	uint8_t i = 0;
	while(*temp != 0){
		buffor[i] = *temp;
		temp++;
		i++;
	}
}

void Model::clrBuffer(void){
	memset(buffor, 0, sizeof(buffor));
}

void Model::setSelectedRoom(uint8_t index){
	selectedRoom = index;
}

uint8_t Model::getSelectedRoom(void){
	return selectedRoom;
}

void Model::setSelectedDeviceIndex(uint8_t index){
	selectedDeviceIndex = index;
}

uint8_t Model::getSelectedDeviceIndex(void){
	return selectedDeviceIndex;
}
