/*
 * FrontendApplication.h
 *
 *  Created on: 28 kwi 2017
 *      Author: Uzume
 */

#ifndef FRONTENDAPPLICATION_FRONTENDAPPLICATION_H_
#define FRONTENDAPPLICATION_FRONTENDAPPLICATION_H_

#include "../Touch/MVPApplication/MVPApplication.h"
#include "../Model/Model.h"

class FrontendHeap;

class FrontendApplication : public MVPApplication{
public:
	FrontendApplication(Model& m, FrontendHeap& heap);
	virtual ~FrontendApplication();

	void gotoMainScreen();
	void gotoKeyboardScreen();
	void gotoMenuHomeScreen();
	void gotoMenuRoomScreen();
	void gotoMenuSwitchScreen();
private:
	Callback<FrontendApplication> transitionCallback;
	FrontendHeap& frontendHeap;
	Model& model;

	void gotoMainScreenImpl();
	void gotoKeyboardScreenImpl();
	void gotoMenuHomeScreenImpl();
	void gotoMenuRoomScreenImpl();
	void gotoMenuSwitchScreenImpl();
};

#endif /* FRONTENDAPPLICATION_FRONTENDAPPLICATION_H_ */
