/*
 * Keyboard.h
 *
 *  Created on: 18 lis 2016
 *      Author: Uzume
 */

#ifndef KEYBOARD_KEYBOARD_H_
#define KEYBOARD_KEYBOARD_H_

#include "../Container/Container.h"
#include "../TextAreaWithWildcard/TextAreaWithWildcard.h"
#include "../Bitmap/Bitmap.h"
#include "../Callback/Callback.h"
#include "../Image/Image.h"

class Keyboard: public Container {
public:
	typedef struct{
		uint8_t 	keyId;
		Rect 		keyArea;
		BitmapId 	highlightBitmapId;
	}Key;

	typedef struct{
		Rect 				keyArea;
		GenericCallback<>* 	callback;
		BitmapId 			highlightBitmapId;
	} CallbackArea;

	typedef struct{
		BitmapId 		bitmap;
		const Key* 		keyArray;
		uint8_t 		numberOfKeys;
		CallbackArea* 	callbackAreaArray;
		uint8_t 		numberOfCallbackAreas;
		Rect 			textAreaPosition;
		TypedText 		textAreaFont;
		colortype 		textAreaFontColor;
		FontId			keyFont;
		colortype 		keyFontColor;
	} Layout;

	typedef struct{
		uint8_t 				keyId;
		Unicode::UnicodeChar 	keyValue;
	} KeyMapping;

	typedef struct{
		const KeyMapping* 	keyMappingArray;
		uint8_t 			numberOfKeys;
	}KeyMappingList;

	Keyboard();
	virtual ~Keyboard(){}
	void setBuffer(Unicode::UnicodeChar* newBuffer, uint16_t newBufferSize);
	Unicode::UnicodeChar* getBuffer(void) const;
	void setBufferPosition(uint16_t newPos);
	uint16_t getBufferPosition(void);
	virtual void draw(const Rect& invalidatedArea) const;
	virtual void handleClickEvent(const ClickEvent& evt);
	void setLayout(const Layout* newLayout);
	const Layout* getLayout() const;
	void setKeymappingList(const KeyMappingList* newKeyMappingList);
    const KeyMappingList* getKeyMappingList() const;
    void setKeyListener(GenericCallback<Unicode::UnicodeChar>& callback);
protected:
    GenericCallback<Unicode::UnicodeChar>* m_keyListener;
	Unicode::UnicodeChar* m_buffer;
	uint16_t m_bufferSize;
	uint16_t m_bufferPosition;
	TextAreaWithOneWildcard m_enteredText;
	const Layout* m_layout;
	const KeyMappingList* m_keyMappingList;
	Image m_image;
	Image m_highlightImage;

	Key getKeyForCoordinates(int16_t x, int16_t y) const;
	Unicode::UnicodeChar getCharForKey(uint8_t keyId) const;
	CallbackArea getCallbackAreaForCoordinates(int16_t x, int16_t y) const;
};

#endif /* KEYBOARD_KEYBOARD_H_ */
