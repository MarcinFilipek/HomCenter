/*
 * Font.cpp
 *
 *  Created on: 3 paü 2016
 *      Author: Uzume
 */

#include "Font.h"
#include <cstdarg>

Font::Font() {
	m_fontHeight = 0;
	m_bitsPerPixel = 0;
	m_pixelsBelowBaseline = 0;
}

uint8_t Font::getBitsPerPixel() const {
	return m_bitsPerPixel;
}

uint16_t Font::getFontHeight() const{
	return m_fontHeight;
}
uint16_t Font::getCharWidth(const Unicode::UnicodeChar c) const{
	return getGlyph(c)->width();
}

uint16_t Font::getStringWidth(const Unicode::UnicodeChar* text, ...) const{
	uint16_t stringWidth = 0;
	uint16_t tempWidth = 0;
	Unicode::UnicodeChar* wildcard = 0;
	va_list ap;
	va_start(ap, text);
	while(*text != 0x00){
		if(*text == 0x0A){
			if(tempWidth > stringWidth){
				stringWidth = tempWidth;
			}
			tempWidth = 0;
		} else {
			if(*text == 0x02){
				wildcard = va_arg(ap, Unicode::UnicodeChar*);
				while(*wildcard != 0x00){
					tempWidth += getCharWidth(*wildcard);
					tempWidth += 2;	//odleglosci miedzy literami
					wildcard++;
				}
			} else {
				tempWidth += getCharWidth(*text);
				tempWidth += 2;	//odleglosci miedzy literami
			}
		}
		text++;
	}
	if(tempWidth > stringWidth){
			stringWidth = tempWidth;
	}
	va_end(ap);
	return stringWidth;
}
