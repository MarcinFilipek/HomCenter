/*
 * KeyboardView.cpp
 *
 *  Created on: 28 cze 2017
 *      Author: Marcin
 */

#include "KeyboardView.h"

KeyboardView::KeyboardView() :
		m_keyboard(), buttonClicedCallback(this, &KeyboardView::buttonClicked) {
}

KeyboardView::~KeyboardView() {
}

void KeyboardView::setupScreen(){
	m_keyboard.setPosition(0, 0, 480, 272);
	m_keyboard.setTouchable(true);

	m_buttonExit.setBitmaps(Bitmap(BITMAP_EXIT_ID), Bitmap(BITMAP_EXIT_ID));
	m_buttonExit.setXY(445, 3);
	m_buttonExit.setAction(buttonClicedCallback);


	add(&m_keyboard);
	add(&m_buttonExit);
}

void KeyboardView::tearDownScreen(void){

}

Unicode::UnicodeChar* KeyboardView::getBuffer(){
	return m_keyboard.getBuffer();
}

void KeyboardView::buttonClicked(const AbstractButton& source) {
	if (&source == &m_buttonExit) {
		presenter->exit();
	}
}
