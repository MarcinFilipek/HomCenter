/*
 * TypedText.cpp
 *
 *  Created on: 30 wrz 2016
 *      Author: Uzume
 */

#include "TypedText.h"

const TypedText::TypedTextData* TypedText::m_typedTexts;
uint16_t TypedText::m_numberOfTypedTexts;
const Font* const* TypedText::m_fonts;
const Texts* TypedText::m_texts;

TypedText::~TypedText() {
	// TODO Auto-generated destructor stub
}

TypedTextId TypedText::getTypeTextId(void) const{
	return m_typedTextId;
}

bool TypedText::hasValidId(void) const{
	return m_typedTextId != TYPED_TEXT_INVALID;
}

const Font* TypedText::getFont() const{
	return m_fonts[m_typedTexts[m_typedTextId].fontIdx];
}

const Aligment TypedText::getAligment(void){
	return m_typedTexts[m_typedTextId].aligment;
}

const TextDirection TypedText::getTextDirection(void){
	return m_typedTexts[m_typedTextId].direction;
}

void TypedText::registerTypedTextDatabase(const TypedTextData* data, const Font* const* f, uint16_t n){
	m_typedTexts = data;
	m_numberOfTypedTexts = n;
	m_fonts = f;
}

void TypedText::registerTexts(const Texts* t){
	m_texts = t;
}

const Unicode::UnicodeChar* TypedText::getText() const{
	return m_texts->getText(m_typedTextId);
}
