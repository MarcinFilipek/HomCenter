/*
 * MenuSwitchView.h
 *
 *  Created on: 3 paü 2018
 *      Author: Uzume
 */

#ifndef APP_MENUSWITCHVIEW_MENUSWITCHVIEW_H_
#define APP_MENUSWITCHVIEW_MENUSWITCHVIEW_H_

#include "../Touch/View/View.h"
#include "../MenuSwitchPresenter/MenuSwitchPresenter.h"
#include "../Touch/Image/Image.h"
#include "../Touch/Button/Button.h"

class MenuSwitchView : public View<MenuSwitchPresenter>{
public:
	MenuSwitchView();
	virtual ~MenuSwitchView();
	void setupScreen(void) override;
	void tearDownScreen(void) override;
private:
	Image background;
	Button buttonRelay1;
	Button buttonRelay2;
	Button buttonExit;

	Callback<MenuSwitchView, const AbstractButton& > buttonPressedCallback;

	void buttonPressedHandler(const AbstractButton& button);
	void switchBitmap();
};

#endif /* APP_MENUSWITCHVIEW_MENUSWITCHVIEW_H_ */
