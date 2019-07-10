/*
 * KeyboardPresenter.cpp
 *
 *  Created on: 28 cze 2017
 *      Author: Marcin
 */

#include "KeyboardPresenter.h"
#include "../KeyboardView/KeyboardView.h"
#include "../FrontendApplication/FrontendApplication.h"

KeyboardPresenter::KeyboardPresenter(KeyboardView& v) :
		view(v) {

}

KeyboardPresenter::~KeyboardPresenter() {
	// TODO Auto-generated destructor stub
}

void KeyboardPresenter::activate(void){
}

void KeyboardPresenter::deactivate(void){
	model->setBuffer(view.getBuffer());
}

void KeyboardPresenter::exit(void){
	static_cast<FrontendApplication*>(Application::getInstance())->gotoMenuHomeScreen();
}
