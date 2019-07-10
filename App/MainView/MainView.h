/*
 * MainView.h
 *
 *  Created on: 5 maj 2017
 *      Author: Uzume
 */

#ifndef MAINVIEW_MAINVIEW_H_
#define MAINVIEW_MAINVIEW_H_

#include "../Touch/View/View.h"
#include "../TestPresenter/TestPresenter.h"
#include "../Touch/Image/Image.h"
#include "../Touch/Button/Button.h"
#include "../Touch/TextArea/TextArea.h"
#include "../Touch/TextAreaWithWildcard/TextAreaWithWildcard.h"

class MainView: public View<TestPresenter> {
public:
	MainView() :
			buttonClicedCallback(this, &MainView::buttonClicked) {
	}
	virtual ~MainView() {

	}
	void setupScreen(void);
	void tearDownScreen(void);
	void buttonClicked(const AbstractButton& source);
private:
	Image m_imageBackground;
	Image m_imageExit;
	Image m_imageKafelek;
	Image m_imageKreska;
	Image m_imageKreska2;
	Button m_buttonPower;
	Button m_buttonPower2;
	TextArea m_textCzesc;
	TextArea m_textDlugi;
	TextArea m_textDlugiLF;
	Unicode::UnicodeChar m_buffer[10];
	TextAreaWithOneWildcard m_textWildcard;
	Container m_kontener;
	Callback<MainView, const AbstractButton&> buttonClicedCallback;
};

#endif /* MAINVIEW_MAINVIEW_H_ */
