/*
 * CustomKeyboard.cpp
 *
 *  Created on: 18 lis 2016
 *      Author: Uzume
 */

#include "CustomKeyboard.h"
#include "../Touch/Color/Color.h"
#include "string.h"

CustomKeyboard::CustomKeyboard() :
		m_keyboard(),
		m_modeBtnTextArea(),
		m_capslockPressed(this, &CustomKeyboard::capslockPressedHandler),
		m_backspacePressed(this, &CustomKeyboard::backspacePressedHandler),
		m_modePressed(this, &CustomKeyboard::modePressedHandler),
		m_okPressed(this, &CustomKeyboard::okPressedHandler),
		m_keyPressed(this, &CustomKeyboard::keyPressedHandler),
		m_alphaKeys(true),
		m_uppercaseKeys(false),
		m_firstCharacterEntry(false) {

	layout.callbackAreaArray[0].callback = &m_capslockPressed;
	layout.callbackAreaArray[1].callback = &m_backspacePressed;
	layout.callbackAreaArray[2].callback = &m_modePressed;
	layout.callbackAreaArray[3].callback = &m_okPressed;
	m_keyboard.setLayout(&layout);
	m_keyboard.setKeyListener(m_keyPressed);
	m_keyboard.setPosition(0, 0, 480, 272);

	memset(m_buffer, 0, sizeof(m_buffer));
	m_keyboard.setBuffer(m_buffer, BUFFER_SIZE);
    m_uppercaseKeys = true;
    m_firstCharacterEntry = true;

    m_modeBtnTextArea.setPosition(0, 236, 100, 15);
    m_modeBtnTextArea.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));

    setKeyMappingList();

    add(&m_keyboard);
    add(&m_modeBtnTextArea);
}

void CustomKeyboard::setKeyMappingList(){
	if(m_alphaKeys){
		m_modeBtnTextArea.setTypedText(T_ALPHAMODE);
		if(m_uppercaseKeys){
			m_keyboard.setKeymappingList(&keyMappingListAlphaUpper);
		} else {
			m_keyboard.setKeymappingList(&keyMappingListAlphaLower);
		}
	} else {
		m_modeBtnTextArea.setTypedText(T_NUMMODE);
		if (m_uppercaseKeys) {
			m_keyboard.setKeymappingList(&keyMappingListNumUpper);
		} else {
			m_keyboard.setKeymappingList(&keyMappingListNumLower);
		}
	}
}

void CustomKeyboard::backspacePressedHandler(){
	uint16_t pos = m_keyboard.getBufferPosition();
	if(pos>0){
		m_buffer[pos - 1] = 0;
		m_keyboard.setBufferPosition(pos - 1);
		if(1 == pos){
			m_firstCharacterEntry = true;
			m_uppercaseKeys = true;
			setKeyMappingList();
		}
	}
}

void CustomKeyboard::capslockPressedHandler(){
	m_uppercaseKeys = !m_uppercaseKeys;
	setKeyMappingList();
}

void CustomKeyboard::modePressedHandler(){
	m_alphaKeys = !m_alphaKeys;
	if(m_firstCharacterEntry && m_alphaKeys){
		m_uppercaseKeys = true;
	} else {
		m_uppercaseKeys = false;
	}
	setKeyMappingList();
}

void CustomKeyboard::keyPressedHandler(Unicode::UnicodeChar keyChar){
    if (m_firstCharacterEntry && keyChar != 0)
    {
        m_firstCharacterEntry = false;
        m_uppercaseKeys = false;
        setKeyMappingList();
    }
}

void CustomKeyboard::okPressedHandler(){

}

void CustomKeyboard::setTouchable(bool touch) {
	Container::setTouchable(touch);
	m_keyboard.setTouchable(touch);
}

Unicode::UnicodeChar* CustomKeyboard::getBuffer(){
	return m_buffer;
}
