/*
 * ConstFont.cpp
 *
 *  Created on: 5 paŸ 2016
 *      Author: Uzume
 */

#include "ConstFont.h"

ConstFont::ConstFont(const GlyphNode* list, uint16_t size, uint16_t height,
		uint8_t pixBelowBase, uint8_t bitPerPixel) : Font(height, pixBelowBase, bitPerPixel) {
	m_glyphList = list;
	m_listSize = size;
}

ConstFont::~ConstFont() {
	// TODO Auto-generated destructor stub
}

const GlyphNode* ConstFont::getGlyph(Unicode::UnicodeChar unicode, const uint8_t*& pixelData, uint8_t& bitsPerPixel) const{
	const GlyphNode* result = 0;
	uint16_t l,p,s;
	l = 0;
	p = m_listSize;
	while (1) {
		if (l > p) {
			break;
		}
		s = (l + p) / 2;
		if (m_glyphList[s]._unicode == unicode) {
			result = &m_glyphList[s];
			pixelData = getPixelData(result);
			break;
		} else if (m_glyphList[s]._unicode < unicode) {
			l = s + 1;
		} else {
			p = s - 1;
		}
	}
	return result;
}
