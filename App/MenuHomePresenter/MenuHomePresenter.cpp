/*
 * MenuHomePresenter.cpp
 *
 *  Created on: 22 sie 2017
 *      Author: Uzume
 */

#include "MenuHomePresenter.h"
#include "../MenuHomeView/MenuHomeView.h"
#include "../../Home/Home/Home.h"

MenuHomePresenter::MenuHomePresenter(MenuHomeView& v) : view(v){

}

MenuHomePresenter::~MenuHomePresenter() {

}

void MenuHomePresenter::activate(void){
	view.setSelectedMenuIndex(0);
}

void MenuHomePresenter::deactivate(void){

}

void MenuHomePresenter::addRoom(void){
	Home::getInstance().addRoom();
	static_cast<FrontendApplication*>(Application::getInstance())->gotoKeyboardScreen();
}

uint8_t MenuHomePresenter::getNumOfRoom(){
	return Home::getInstance().getNumOfRoom();
}

Unicode::UnicodeChar* MenuHomePresenter::getBuffor(){
	return model->getBuffor();
}

void MenuHomePresenter::goToRoom(uint8_t indexOfRoom){
	model->setSelectedRoom(indexOfRoom);
	static_cast<FrontendApplication*>(Application::getInstance())->gotoMenuRoomScreen();
}
