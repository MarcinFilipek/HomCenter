/*
 * MenuSwitchPresenter.h
 *
 *  Created on: 3 paü 2018
 *      Author: Uzume
 */

#ifndef APP_MENUSWITCHPRESENTER_MENUSWITCHPRESENTER_H_
#define APP_MENUSWITCHPRESENTER_MENUSWITCHPRESENTER_H_

#include "../../Touch/Presenter/Presenter.h"
#include "../FrontendApplication/FrontendApplication.h"
#include "../Model/ModelListener.h"

class MenuSwitchView;

class MenuSwitchPresenter: public Presenter, public ModelListener {
public:
	MenuSwitchPresenter(MenuSwitchView& v);
	virtual ~MenuSwitchPresenter();
	void exit(void);
	void toggleRelay1();
	void toggleRelay2();
	bool getStateRelay1();
	bool getStateRelay2();
private:
	MenuSwitchPresenter();
	MenuSwitchView& view;
};

#endif /* APP_MENUSWITCHPRESENTER_MENUSWITCHPRESENTER_H_ */
