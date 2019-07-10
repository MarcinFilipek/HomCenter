/*
 * MenuSwitchPresenter.cpp
 *
 *  Created on: 3 paü 2018
 *      Author: Uzume
 */

#include "MenuSwitchPresenter.h"
#include "../../Home/Home/Home.h"

MenuSwitchPresenter::MenuSwitchPresenter(MenuSwitchView& v) : view(v){

}

MenuSwitchPresenter::~MenuSwitchPresenter() {
}

void MenuSwitchPresenter::exit(void){
	static_cast<FrontendApplication*>(Application::getInstance())->gotoMenuRoomScreen();
}

void MenuSwitchPresenter::toggleRelay1(){
	Switch* dev = (Switch*)(Home::getInstance().getRoom(model->getSelectedRoom())->getDeviceByIndex(model->getSelectedDeviceIndex()));
	dev->toggleRelay1();
}

void MenuSwitchPresenter::toggleRelay2(){
	Switch* dev = (Switch*)(Home::getInstance().getRoom(model->getSelectedRoom())->getDeviceByIndex(model->getSelectedDeviceIndex()));
	dev->toggleRelay2();
}

bool MenuSwitchPresenter::getStateRelay1(){
	Switch* dev = (Switch*)(Home::getInstance().getRoom(model->getSelectedRoom())->getDeviceByIndex(model->getSelectedDeviceIndex()));
	return dev->getStateRelay1();
}

bool MenuSwitchPresenter::getStateRelay2(){
	Switch* dev = (Switch*)(Home::getInstance().getRoom(model->getSelectedRoom())->getDeviceByIndex(model->getSelectedDeviceIndex()));
	return dev->getStateRelay2();
}
