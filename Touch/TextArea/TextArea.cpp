/*
 * TextArea.cpp
 *
 *  Created on: 30 wrz 2016
 *      Author: Uzume
 */

#include "TextArea.h"
#include "../Lcd/Lcd.h"
#include "../Texts/Texts.h"

TextArea::TextArea() {
	m_color = colortype(0);
	m_alpha = 255;
	m_linespace = 0;
	m_indentation = 0;
}

TextArea::~TextArea() {
	// TODO Auto-generated destructor stub
}

void TextArea::setColor(colortype c) {
	m_color = c;
}

colortype TextArea::getColor(void) {
	return m_color;
}

void TextArea::setAlpha(uint8_t alpha){
	m_alpha = alpha;
}

uint8_t TextArea::getAlpha(void){
	return m_alpha;
}

void TextArea::draw(const Rect& invalidatedArea) const{
	Lcd::StringVisuals stringVisuals = Lcd::StringVisuals(m_typeText.getFont(),
			m_color, m_alpha, LEFT, m_linespace, TEXT_DIRECTION_LTR, 0);
	Lcd lcd;
	Rect meAbs = getAbsoluteRect();
	Rect dirtyBitmapArea = meAbs & invalidatedArea;
	lcd.drawString(meAbs, dirtyBitmapArea, stringVisuals, m_typeText.getText());
}

void TextArea::setTypedText(TypedText t){
	m_typeText = t;
}

TypedText TextArea::getTypedText(void) const{
	return m_typeText;
}

void TextArea::setLinespace(uint16_t linesspace){
	m_linespace = linesspace;
}

uint16_t TextArea::getLinespace(void) const{
	return m_linespace;
}

void TextArea::setIndentation(uint8_t indent){
	m_indentation = indent;
}

uint8_t TextArea::getIndentation(void){
	return m_indentation;
}

int16_t TextArea::getTextHeight(){
	uint16_t textHeight = 0;
	uint16_t fontHeight = 0;
	const Unicode::UnicodeChar* format = m_typeText.getText();
	fontHeight = getTypedText().getFont()->getGlyph(format[0])->height();
	textHeight += fontHeight;
	while(*format != 0x00){
		if(*format == 0xA){
			textHeight += (fontHeight + getLinespace());
		}
		format++;
	}
	return textHeight;
}
uint16_t TextArea::getTextWidth() const{
	uint16_t maxWidth = 0;
	uint16_t tempWidth = 0;
	const Unicode::UnicodeChar* format = m_typeText.getText();
	while(*format != 0x00){
		if((*format ==0x0A)){
			if(tempWidth > maxWidth){
				maxWidth = tempWidth;
			}
			tempWidth = 0;
		} else {
			tempWidth += getTypedText().getFont()->getGlyph(*format)->width();
			tempWidth += 2; //odleglosci miedzy literami
		}
		format++;
	}

	if(tempWidth > maxWidth){
		maxWidth = tempWidth;
	}

	return maxWidth;
}

void TextArea::resizeToCurrentText(){
	m_rect.m_height = getTextHeight();
	m_rect.m_width = getTextWidth();
}

uint16_t TextArea::getType() const {
	return (uint16_t) TYPE_TEXTAREA;
}
