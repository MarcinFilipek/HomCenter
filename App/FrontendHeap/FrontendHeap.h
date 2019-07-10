/*
 * FrontendHeap.h
 *
 *  Created on: 27 kwi 2017
 *      Author: Uzume
 */

#ifndef FRONTENDHEAP_FRONTENDHEAP_H_
#define FRONTENDHEAP_FRONTENDHEAP_H_

#include "../Touch/MVPHeap/MVPHeap.h"
#include "../FrontendApplication/FrontendApplication.h"
#include "../Touch/Meta/Meta.h"
#include "../Touch/Partition/Partition.h"

#include "../MainView/MainView.h"
#include "../TestPresenter/TestPresenter.h"
#include "../KeyboardView/KeyboardView.h"
#include "../KeyboardPresenter/KeyboardPresenter.h"
#include "../MenuHomeView/MenuHomeView.h"
#include "../MenuHomePresenter/MenuHomePresenter.h"
#include "../MenuRoomView/MenuRoomView.h"
#include "../MenuRoomPresenter/MenuRoomPresenter.h"
#include "../MenuSwitchView/MenuSwitchView.h"
#include "../MenuSwitchPresenter/MenuSwitchPresenter.h"
#include "../Model/Model.h"

class FrontendHeap : public MVPHeap{
public:
	typedef TypeList<MainView, TypeList<KeyboardView, TypeList<MenuHomeView, TypeList<MenuRoomView, TypeList<MenuSwitchView, Nil> > > > > ViewTypes;
	typedef select_type_maxsize<ViewTypes>::type MaxViewType;

	typedef TypeList<TestPresenter, TypeList<KeyboardPresenter, TypeList<MenuHomePresenter, TypeList<MenuRoomPresenter, TypeList<MenuRoomPresenter, Nil> > > > > PresenterTypes;
	typedef select_type_maxsize<PresenterTypes>::type MaxPresenterType;

	static FrontendHeap& getInstance(void){
		static FrontendHeap instance;
		return instance;
	}
	Partition<PresenterTypes, 1> presenters;
	Partition<ViewTypes, 1> views;
	FrontendApplication app;
	Model model;
private:
	FrontendHeap() : MVPHeap(presenters, views, app), presenters(), views(), app(model, *this){
//		app.gotoMainScreen();
//		app.gotoKeyboardScreen();
		app.gotoMenuHomeScreen();
	}
};



#endif /* FRONTENDHEAP_FRONTENDHEAP_H_ */
