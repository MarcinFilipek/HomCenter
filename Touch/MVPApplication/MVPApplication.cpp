/*
 * MVPApplication.cpp
 *
 *  Created on: 28 kwi 2017
 *      Author: Uzume
 */

#include "MVPApplication.h"
#include "../Touch/Presenter/Presenter.h"

static inline void prepareTransition(Screen** currentScreen, Presenter** currentPresenter){
	if(*currentScreen){
		(*currentScreen)->tearDownScreen();
	}
	if(*currentPresenter){
		(*currentPresenter)->deactivate();
	}
	if(*currentScreen){
		(*currentScreen)->~Screen();
	}
	if(*currentPresenter){
		(*currentPresenter)->~Presenter();
	}
}

static inline void finalizeTransition(Screen* newScreen, Presenter* newPresenter){
	newScreen->setupScreen();
	newPresenter->activate();
	Application::getInstance()->draw();
}

template < class ScreenType, class PresenterType, class ModelType >
PresenterType* makeTransition(Screen** currnetScreen, Presenter** currentPresenter, MVPHeap& heap, ModelType* model){
	prepareTransition(currnetScreen, currentPresenter);

	ScreenType* newScreen = new(&heap.screenStorage.at< ScreenType >(0)) ScreenType;
	PresenterType* newPresenter = new(&heap.presenterStorage.at<PresenterType>(0)) PresenterType(*newScreen);
	*currentPresenter = newPresenter;
	*currnetScreen = newScreen;
	model->bind(newPresenter);
	newPresenter->bind(model);
	newScreen->bind(*newPresenter);

	finalizeTransition((Screen*) newScreen, (Presenter*) newPresenter);

	return newPresenter;
}
