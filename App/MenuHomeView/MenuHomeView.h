/*
 * MenuHomeView.h
 *
 *  Created on: 22 sie 2017
 *      Author: Uzume
 */

#ifndef APP_MENUHOMEVIEW_MENUHOMEVIEW_H_
#define APP_MENUHOMEVIEW_MENUHOMEVIEW_H_

#include "../Touch/View/View.h"
#include "../MenuHomePresenter/MenuHomePresenter.h"
#include "../Touch/Image/Image.h"
#include "../Touch/TextArea/TextArea.h"
#include "../Touch/Button/Button.h"
#include "../Common/SwipeContainer/SwipeContainer.h"
#include "../Touch/TextAreaWithWildcard/TextAreaWithWildcard.h"

class MenuHomeView: public View<MenuHomePresenter> {
public:
	MenuHomeView();
	virtual ~MenuHomeView();

	void setupScreen(void) override;
	void tearDownScreen(void) override;
	void setSelectedMenuIndex(uint8_t index);
private:
	struct MainButtonCord{
		int16_t x;
		int16_t y;
	};
	static const uint8_t NUM_OF_ROW_MAIN_BUTTON = 2;
	static const uint8_t NUM_OF_COL_MAIN_BUTTON = 3;
	MainButtonCord cordMainButton[NUM_OF_ROW_MAIN_BUTTON][NUM_OF_COL_MAIN_BUTTON];
protected:
	static const uint8_t NUMBER_OF_SCREENS = 3;

	Image backgroundLeft;
	Image backgroundRight;

	Container containerScreen[NUMBER_OF_SCREENS];
	Image backgroundScreen[NUMBER_OF_SCREENS];

	TextArea textHeader;
	TextArea textAddRoom;
	Button buttonAddRoom;

	Button buttonRoom[NUM_OF_COL_MAIN_BUTTON * NUM_OF_ROW_MAIN_BUTTON];

	TextAreaWithOneWildcard textNameOfRoom;

	SwipeContainer menuContainer;

	Callback<MenuHomeView, const AbstractButton& > buttonPressedCallback;
	Callback<MenuHomeView, const AbstractButton& > buttonRoomPressedCallback;
	Callback<MenuHomeView, const SwipeContainer&> menuStateChangeInitiatedCallback;
	Callback<MenuHomeView, const SwipeContainer&> menuStateChangeEndedCallback;

	void menuStateChangeInitiatedHandler(const SwipeContainer& sc);
	void menuStateChangeEndedHandler(const SwipeContainer& sc);
	void buttonPressedHandler(const AbstractButton& button);
	void buttonRoomPressedHandler(const AbstractButton& button);
};

#endif /* APP_MENUHOMEVIEW_MENUHOMEVIEW_H_ */
