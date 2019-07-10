/*
 * CustomKeyboard.h
 *
 *  Created on: 18 lis 2016
 *      Author: Uzume
 */

#ifndef CUSTOMKEYBOARD_CUSTOMKEYBOARD_H_
#define CUSTOMKEYBOARD_CUSTOMKEYBOARD_H_

#include "../Touch/Keyboard/Keyboard.h"
#include "KeyboardKeyMapping.h"
#include "KeyboardLayout.h"

class CustomKeyboard: public Container {
public:
	CustomKeyboard();
	virtual ~CustomKeyboard(){}
	void setTouchable(bool touch);
	static const uint8_t BUFFER_SIZE = 18;
	Unicode::UnicodeChar* getBuffer();
private:
	Keyboard m_keyboard;
	Unicode::UnicodeChar m_buffer[BUFFER_SIZE];
	TextArea m_modeBtnTextArea;
	Callback<CustomKeyboard> m_capslockPressed;
	Callback<CustomKeyboard> m_backspacePressed;
	Callback<CustomKeyboard> m_modePressed;
	Callback<CustomKeyboard> m_okPressed;
	Callback<CustomKeyboard, Unicode::UnicodeChar> m_keyPressed;
	bool m_alphaKeys;
	bool m_uppercaseKeys;
	bool m_firstCharacterEntry;

	void setKeyMappingList();
	void backspacePressedHandler();
	void capslockPressedHandler();
	void modePressedHandler();
	void okPressedHandler();
	void keyPressedHandler(Unicode::UnicodeChar keyChar);
};

#endif /* CUSTOMKEYBOARD_CUSTOMKEYBOARD_H_ */
