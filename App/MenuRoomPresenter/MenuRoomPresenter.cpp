/*
 * MenuRoomPresenter.cpp
 *
 *  Created on: 22 lut 2018
 *      Author: Uzume
 */

#include "MenuRoomPresenter.h"
#include "../MenuRoomView/MenuRoomView.h"
#include "../FrontendApplication/FrontendApplication.h"
#include "../../Home/Home/Home.h"
#include "../../ResourcesOut/Images/BitmapDatabase.h"

MenuRoomPresenter::MenuRoomPresenter(MenuRoomView& v) :
		view(v) {
}

MenuRoomPresenter::~MenuRoomPresenter() {
}

void MenuRoomPresenter::activate(void){

}

void MenuRoomPresenter::deactivate(void){

}

void MenuRoomPresenter::exit(void){
	static_cast<FrontendApplication*>(Application::getInstance())->gotoMenuHomeScreen();
}

uint8_t MenuRoomPresenter::getNumOfDevices(){
	return Home::getInstance().getRoom(model->getSelectedRoom())->getNumOfDevice();
}

void MenuRoomPresenter::addDevice(){
	Home::getInstance().getRoom(model->getSelectedRoom())->addDevice();
}

uint16_t MenuRoomPresenter::getBitmapIdForDevice(uint8_t index){
	IDevice* dev = Home::getInstance().getRoom(model->getSelectedRoom())->getDeviceByIndex(index);
	if(dev){
		IDevice::DevType typ = (IDevice::DevType)(dev->getType());
		switch(typ){
		case IDevice::DEVICE_SWITCH:
			return BITMAP_SWITCHOFFOFF_ID;
		case IDevice::IDEVICE:
		case IDevice::DEVICE:
		default:
			return BITMAP_CUBE_ID;
		}
	}
	return BITMAP_CUBE_ID;
}

void MenuRoomPresenter::goToDevice(uint8_t index){
	model->setSelectedDeviceIndex(index);
	static_cast<FrontendApplication*>(Application::getInstance())->gotoMenuSwitchScreen();
}
