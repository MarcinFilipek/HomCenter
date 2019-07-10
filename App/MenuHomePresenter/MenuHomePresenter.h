/*
 * MenuHomePresenter.h
 *
 *  Created on: 22 sie 2017
 *      Author: Uzume
 */

#ifndef APP_MENUHOMEPRESENTER_MENUHOMEPRESENTER_H_
#define APP_MENUHOMEPRESENTER_MENUHOMEPRESENTER_H_

#include "../../Touch/Presenter/Presenter.h"
#include "../FrontendApplication/FrontendApplication.h"
#include "../Model/ModelListener.h"

class MenuHomeView;

class MenuHomePresenter: public Presenter, public ModelListener {
public:
	MenuHomePresenter(MenuHomeView& v);
	virtual ~MenuHomePresenter();
	void activate(void) override;
	void deactivate(void) override;
	void addRoom(void);
	void goToRoom(uint8_t indexOfRoom);
	uint8_t getNumOfRoom();
	Unicode::UnicodeChar* getBuffor();
private:
	MenuHomePresenter();
	MenuHomeView& view;
};

#endif /* APP_MENUHOMEPRESENTER_MENUHOMEPRESENTER_H_ */
