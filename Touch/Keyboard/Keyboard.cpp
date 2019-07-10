/*
 * Keyboard.cpp
 *
 *  Created on: 18 lis 2016
 *      Author: Uzume
 */

#include "Keyboard.h"
#include "../Touch/Lcd/Lcd.h"
#include "../FontManager/FontManager.h"
#include "../ResourcesOut/Texts/TextKeysAndLanguages.h"

Keyboard::Keyboard() {
	m_buffer = 0;
	m_bufferSize = 0;
	m_bufferPosition = 0;
	m_keyMappingList = NULL;
	m_keyListener = NULL;
	m_layout = NULL;
	m_highlightImage.setVisible(false);
}

void Keyboard::setBuffer(Unicode::UnicodeChar* newBuffer, uint16_t newBufferSize){
	m_buffer = newBuffer;
	m_bufferSize = newBufferSize;
	m_enteredText.setWildcard(m_buffer);
}

Unicode::UnicodeChar* Keyboard::getBuffer(void) const{
	return m_buffer;
}

void Keyboard::setBufferPosition(uint16_t newPos){
	m_bufferPosition = newPos;
}

uint16_t Keyboard::getBufferPosition(void){
	return m_bufferPosition;
}

void Keyboard::draw(const Rect& invalidatedArea) const{
	if(m_firstChild != NULL){
		Drawable* tempChild = m_firstChild;
		do{
			if(tempChild->isVisible()){
				tempChild->draw(invalidatedArea);
			}
			tempChild = tempChild->getNextSibling();
		} while(tempChild != NULL);
	}

	Lcd::StringVisuals stringVisuals = Lcd::StringVisuals(FontManager::getFont(m_layout->keyFont), m_layout->keyFontColor);
	Rect dirtyBitmapArea = m_rect & invalidatedArea;
	Lcd lcd;
	Unicode::UnicodeChar temp[2] = {0x00, 0x00};
	for(uint8_t c = 0; c< m_keyMappingList->numberOfKeys; c++){
		temp[0] = getCharForKey(c + 1);
		lcd.drawString(m_layout->keyArray[c].keyArea, dirtyBitmapArea, stringVisuals, temp);
	}
}

void Keyboard::handleClickEvent(const ClickEvent& evt){
	Keyboard::CallbackArea callbackArea = getCallbackAreaForCoordinates(evt.getX(), evt.getY());
	Keyboard::Key key = getKeyForCoordinates(evt.getX(), evt.getY());
	Unicode::UnicodeChar ch = getCharForKey(key.keyId);

	if(evt.getClickEventType() == ClickEvent::PRESSED){
		if(callbackArea.callback){
			m_highlightImage.setBitmap(Bitmap(callbackArea.highlightBitmapId));
			m_highlightImage.setPosition(
					callbackArea.keyArea.m_x,
					callbackArea.keyArea.m_y,
					callbackArea.keyArea.m_width,
					callbackArea.keyArea.m_height);
			m_highlightImage.setVisible(true);
			invalidate();
		}
		if(key.keyId){
			m_highlightImage.setBitmap(Bitmap(key.highlightBitmapId));
			m_highlightImage.setPosition(
					key.keyArea.m_x,
					key.keyArea.m_y,
					key.keyArea.m_width,
					key.keyArea.m_height);
			m_highlightImage.setVisible(true);
			invalidate();
		}
	}
	if(evt.getClickEventType() == ClickEvent::RELEASED){
		if(callbackArea.callback && callbackArea.callback->isValid()){
			callbackArea.callback->execute();
			invalidate();
		}
		if(ch && (getBufferPosition() < m_bufferSize - 1)){
			if(m_keyListener->isValid()){
				m_keyListener->execute(ch);
			}
			*(getBuffer() + getBufferPosition())  = ch;
			setBufferPosition(getBufferPosition() + 1);
			invalidate();
		}
		m_highlightImage.setVisible(false);
		invalidate();
	}
}

void Keyboard::setLayout(const Layout* newLayout){
	m_layout = newLayout;

	m_image.setBitmap(m_layout->bitmap);
	m_image.setXY(getX(), getY());
	add(&m_image);
	add(&m_highlightImage);

	m_enteredText.setTypedText(TypedText(T_ENTEREDTEXT));
	m_enteredText.setPosition(
			m_layout->textAreaPosition.m_x,
			m_layout->textAreaPosition.m_y,
			m_layout->textAreaPosition.m_width,
			m_layout->textAreaPosition.m_height);
	m_enteredText.setColor(m_layout->textAreaFontColor);
	add(&m_enteredText);
}

const Keyboard::Layout* Keyboard::getLayout() const{
	return m_layout;
}

void Keyboard::setKeymappingList(const KeyMappingList* newKeyMappingList){
	m_keyMappingList = newKeyMappingList;
}

const Keyboard::KeyMappingList* Keyboard::getKeyMappingList() const
{
    return m_keyMappingList;
}

void Keyboard::setKeyListener(GenericCallback<Unicode::UnicodeChar>& callback)
{
    m_keyListener = &callback;
}

Keyboard::Key Keyboard::getKeyForCoordinates(int16_t x, int16_t y) const{
	Key result;
	result.keyId = 0;
	const Key* pKey = m_layout->keyArray;
	for(uint8_t c = 0; c < m_keyMappingList->numberOfKeys; c++){
		if(pKey->keyArea.intersect(x, y)){
			result = *pKey;
		}
		pKey++;
	}
	return result;
}

Unicode::UnicodeChar Keyboard::getCharForKey(uint8_t keyId) const{
	Unicode::UnicodeChar result = 0x00;
	const KeyMapping* pKeyMapping = m_keyMappingList->keyMappingArray;
	for(uint8_t c = 0; c< m_keyMappingList->numberOfKeys; c++){
		if(pKeyMapping->keyId == keyId){
			result = pKeyMapping->keyValue;
		}
		pKeyMapping++;
	}
	return result;
}

Keyboard::CallbackArea Keyboard::getCallbackAreaForCoordinates(int16_t x, int16_t y) const{
	Keyboard::CallbackArea result;
	result.callback = 0;
	const Keyboard::CallbackArea* pCallbackArea = m_layout->callbackAreaArray;
	for(uint8_t c = 0; c < m_layout->numberOfCallbackAreas; c++){
		if(pCallbackArea->keyArea.intersect(x, y)){
			result = *pCallbackArea;
		}
		pCallbackArea++;
	}
	return result;
}
