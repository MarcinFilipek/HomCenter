/*
 * FrontendApplication.cpp
 *
 *  Created on: 28 kwi 2017
 *      Author: Uzume
 */

#include "FrontendApplication.h"
#include "../MainView/MainView.h"
#include "../TestPresenter/TestPresenter.h"
#include "../KeyboardView/KeyboardView.h"
#include "../KeyboardPresenter/KeyboardPresenter.h"
#include "../FrontendHeap/FrontendHeap.h"
#include "../Touch/MVPApplication/MVPApplication.cpp"

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap) : transitionCallback(), frontendHeap(heap), model(m){

}

FrontendApplication::~FrontendApplication() {
}

void FrontendApplication::gotoMainScreen(){
	transitionCallback = Callback<FrontendApplication>(this, &FrontendApplication::gotoMainScreenImpl);
	pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMainScreenImpl(){
	makeTransition<MainView, TestPresenter, Model>(&currentScreen, &currentPresenter, frontendHeap, &model);
}

void FrontendApplication::gotoKeyboardScreen(){
	transitionCallback = Callback<FrontendApplication>(this, &FrontendApplication::gotoKeyboardScreenImpl);
	pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoKeyboardScreenImpl(){
	makeTransition<KeyboardView, KeyboardPresenter, Model>(&currentScreen, &currentPresenter, frontendHeap, &model);
}

void FrontendApplication::gotoMenuHomeScreen(){
	transitionCallback = Callback<FrontendApplication>(this, &FrontendApplication::gotoMenuHomeScreenImpl);
	pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMenuHomeScreenImpl(){
	makeTransition<MenuHomeView, MenuHomePresenter, Model>(&currentScreen, &currentPresenter, frontendHeap, &model);
}

void FrontendApplication::gotoMenuRoomScreen(){
	transitionCallback = Callback<FrontendApplication>(this, &FrontendApplication::gotoMenuRoomScreenImpl);
	pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMenuRoomScreenImpl(){
	makeTransition<MenuRoomView, MenuRoomPresenter, Model>(&currentScreen, &currentPresenter, frontendHeap, &model);
}

void FrontendApplication::gotoMenuSwitchScreen(){
	transitionCallback = Callback<FrontendApplication>(this, &FrontendApplication::gotoMenuSwitchScreenImpl);
	pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMenuSwitchScreenImpl(){
	makeTransition<MenuSwitchView, MenuSwitchPresenter, Model>(&currentScreen, &currentPresenter, frontendHeap, &model);
}
