/*
 * Font.h
 *
 *  Created on: 3 paü 2016
 *      Author: Uzume
 */

#ifndef FONT_FONT_H_
#define FONT_FONT_H_

#include "../Unicode/Unicode.h"

typedef struct {
	uint32_t _dataOffset;
	Unicode::UnicodeChar _unicode;
	uint8_t _width;
	uint8_t _height;

	uint16_t width(void) const {
		return (uint16_t) _width;
	}

	uint16_t height(void) const {
		return (uint16_t) _height;
	}
} GlyphNode;

typedef uint16_t FontId;

class Font {
public:
	virtual ~Font() {}

	virtual const GlyphNode* getGlyph(Unicode::UnicodeChar unicode,
			const uint8_t*& pixelData, uint8_t& bitsPerPixel) const = 0;
	virtual const GlyphNode* getGlyph(Unicode::UnicodeChar unicode) const {
		const uint8_t* dummyPixelDataPointer = 0;
		uint8_t bitsPerPixelDummy = 0;
		return getGlyph(unicode, dummyPixelDataPointer, bitsPerPixelDummy);
	}
	virtual uint8_t getBitsPerPixel() const;
	virtual uint16_t getFontHeight() const;
	virtual uint16_t getStringWidth(const Unicode::UnicodeChar* text, ...) const;
//	virtual uint16_t getStringWidth(TextDirection textDirection, const Unicode::UnicodeChar* text, ...) const;
	virtual uint16_t getCharWidth(const Unicode::UnicodeChar c) const;
protected:
	Font(uint16_t height, uint8_t pixBelowBase, uint8_t bPerPixel) :
			m_fontHeight(height), m_pixelsBelowBaseline(pixBelowBase), m_bitsPerPixel(
					bPerPixel) {
	}
	uint16_t m_fontHeight;
	uint8_t m_pixelsBelowBaseline;
	uint8_t m_bitsPerPixel;
private:
	Font();
};

#endif /* FONT_FONT_H_ */
