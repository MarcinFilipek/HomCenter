/*
 * MenuRoomView.h
 *
 *  Created on: 22 lut 2018
 *      Author: Uzume
 */

#ifndef APP_MENUROOMVIEW_MENUROOMVIEW_H_
#define APP_MENUROOMVIEW_MENUROOMVIEW_H_

#include "../Touch/View/View.h"
#include "../Touch/Image/Image.h"
#include "../Touch/Button/Button.h"
#include "../Touch/TextArea/TextArea.h"
#include "../MenuRoomPresenter/MenuRoomPresenter.h"

class MenuRoomView: public View<MenuRoomPresenter> {
public:
	MenuRoomView();
	virtual ~MenuRoomView(){}
	void setupScreen(void);
private:
	struct MainButtonCord{
		int16_t x;
		int16_t y;
	};
	static const uint8_t NUM_OF_ROW_MAIN_BUTTON = 2;
	static const uint8_t NUM_OF_COL_MAIN_BUTTON = 3;
	MainButtonCord cordMainButton[NUM_OF_ROW_MAIN_BUTTON][NUM_OF_COL_MAIN_BUTTON];

	Image background;
	Button buttonExit;
	Button buttonAddDevice;
	TextArea textAddDevice;
	Button buttonDevice[NUM_OF_COL_MAIN_BUTTON * NUM_OF_ROW_MAIN_BUTTON];
protected:
	Callback<MenuRoomView, const AbstractButton& > buttonPressedCallback;
	Callback<MenuRoomView, const AbstractButton& > buttonDevicePressedCallback;

	void buttonPressedHandler(const AbstractButton& button);
	void buttonDevicePressedHandler(const AbstractButton& button);
};

#endif /* APP_MENUROOMVIEW_MENUROOMVIEW_H_ */
