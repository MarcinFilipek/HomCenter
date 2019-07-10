/*
 * InternalFlashFont.cpp
 *
 *  Created on: 5 paŸ 2016
 *      Author: Uzume
 */

#include "InternalFlashFont.h"

InternalFlashFont::InternalFlashFont(const GlyphNode* list, uint16_t size,
		uint16_t height, uint8_t pixBelowBase, uint8_t bitPerPixel,
		const uint8_t* glyphDataInternalFlash) :
		ConstFont(list, size, height, pixBelowBase, bitPerPixel) {
	m_glyphData = glyphDataInternalFlash;
}

InternalFlashFont::~InternalFlashFont() {
	// TODO Auto-generated destructor stub
}

const uint8_t* InternalFlashFont::getPixelData(const GlyphNode* glyph) const{
	uint32_t offset = 0;
	uint16_t l,p,s;
	l = 0;
	p = m_listSize;
	while (1) {
		if (l > p) {
			break;
		}
		s = (l + p) / 2;
		if (m_glyphList[s]._unicode == glyph->_unicode) {
			offset = m_glyphList[s]._dataOffset;
			break;
		} else if (m_glyphList[s]._unicode < glyph->_unicode) {
			l = s + 1;
		} else {
			p = s - 1;
		}
	}
	return m_glyphData + offset;
}
