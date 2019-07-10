/*
 * TextAreaWithWildcard.cpp
 *
 *  Created on: 14 lis 2016
 *      Author: Uzume
 */

#include "TextAreaWithWildcard.h"
#include "../Lcd/Lcd.h"
#include <cstdarg>

int16_t TextAreaWildcardBase::calculateTextHeight(const Unicode::UnicodeChar* format, ...) const{
	uint16_t textHeight = 0;
	uint16_t fontHeight = m_typeText.getFont()->getFontHeight();
	textHeight+= fontHeight;
	while(*format != 0x00){
		if(*format == 0x02){
			Unicode::UnicodeChar* wildcard = 0;
			va_list ap;
			va_start(ap, format);
			wildcard = va_arg(ap, Unicode::UnicodeChar*);
			while(*wildcard != 0x00){
				if(*wildcard == 0x0A){
					textHeight += (fontHeight + getLinespace());
				}
				wildcard++;
			}
		}
		if(*format == 0x0A){
			textHeight += (fontHeight + getLinespace());
		}
		format++;
	}

	return textHeight;
}

int16_t TextAreaWithOneWildcard::getTextHeight(){
	return m_typeText.hasValidId() ? calculateTextHeight(m_typeText.getText(), m_wildcard) : 0;
}

void TextAreaWithOneWildcard::draw(const Rect& invalidatedArea) const{
	if(m_typeText.hasValidId()){
		const Font* fontToDraw = m_typeText.getFont();
		if(fontToDraw != 0){
			Lcd::StringVisuals stringVisuals(fontToDraw, m_color, m_alpha, LEFT, m_linespace, TEXT_DIRECTION_LTR, 0);
			Lcd lcd;
			Rect dirtyBitmapArea = m_rect & invalidatedArea;
			lcd.drawString(m_rect, dirtyBitmapArea, stringVisuals, m_typeText.getText(), m_wildcard);
		}
	}
}
void TextAreaWithOneWildcard::setWildcard(const Unicode::UnicodeChar* value){
	m_wildcard = value;
}

const Unicode::UnicodeChar* TextAreaWithOneWildcard::getWildcard() const{
	return m_wildcard;
}

uint16_t TextAreaWithOneWildcard::getTextWidth(){
	return m_typeText.hasValidId() ? m_typeText.getFont()->getStringWidth(m_typeText.getText(), m_wildcard) : 0;
}

uint16_t TextAreaWithOneWildcard::getType() const{
	return (uint16_t) TYPE_TEXTAREAWITHONEWILDCARD;
}
