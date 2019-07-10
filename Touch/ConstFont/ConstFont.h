/*
 * ConstFont.h
 *
 *  Created on: 5 paü 2016
 *      Author: Uzume
 */

#ifndef CONSTFONT_CONSTFONT_H_
#define CONSTFONT_CONSTFONT_H_

#include "../Font/Font.h"

class ConstFont: public Font {
public:
	ConstFont(const GlyphNode* list, uint16_t size, uint16_t height,
			uint8_t pixBelowBase, uint8_t bitPerPixel);
	virtual ~ConstFont();
	virtual const GlyphNode* getGlyph(Unicode::UnicodeChar unicode, const uint8_t*& pixelData, uint8_t& bitsPerPixel) const;
	virtual const uint8_t* getPixelData(const GlyphNode* glyph) const = 0;
private:
	ConstFont() :
			Font(0, 0, 0) {
		m_glyphList = 0;
		m_listSize = 0;
	}
protected:
	const GlyphNode* m_glyphList;
	uint16_t m_listSize;
};

#endif /* CONSTFONT_CONSTFONT_H_ */
