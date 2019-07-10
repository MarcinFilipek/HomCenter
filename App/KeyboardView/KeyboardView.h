/*
 * KeyboardView.h
 *
 *  Created on: 28 cze 2017
 *      Author: Marcin
 */

#ifndef KEYBOARDVIEW_KEYBOARDVIEW_H_
#define KEYBOARDVIEW_KEYBOARDVIEW_H_

#include "../Touch/View/View.h"
#include "../KeyboardPresenter/KeyboardPresenter.h"
#include "../CustomKeyboard/CustomKeyboard.h"
#include "../Touch/Button/Button.h"

class KeyboardView: public View<KeyboardPresenter> {
public:
	KeyboardView();
	virtual ~KeyboardView();
	void setupScreen(void);
	void tearDownScreen(void);
	Unicode::UnicodeChar* getBuffer();
	void buttonClicked(const AbstractButton& source);
private:
	CustomKeyboard m_keyboard;
	Button m_buttonExit;
	Callback<KeyboardView, const AbstractButton&> buttonClicedCallback;

};

#endif /* KEYBOARDVIEW_KEYBOARDVIEW_H_ */
