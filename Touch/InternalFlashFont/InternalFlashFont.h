/*
 * InternalFlashFont.h
 *
 *  Created on: 5 paü 2016
 *      Author: Uzume
 */

#ifndef INTERNALFLASHFONT_INTERNALFLASHFONT_H_
#define INTERNALFLASHFONT_INTERNALFLASHFONT_H_

#include "../ConstFont/ConstFont.h"

class InternalFlashFont: public ConstFont {
public:
	InternalFlashFont(const GlyphNode* list, uint16_t size, uint16_t height,
			uint8_t pixBelowBase, uint8_t bitPerPixel,
			const uint8_t* glyphDataInternalFlash);
	virtual const uint8_t* getPixelData(const GlyphNode* glyph) const;
	virtual ~InternalFlashFont();
private:
	InternalFlashFont() :
			ConstFont(0, 0, 0, 0, 0) {
	}
	const uint8_t* m_glyphData;
};

#endif /* INTERNALFLASHFONT_INTERNALFLASHFONT_H_ */
