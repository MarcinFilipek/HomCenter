/*
 * TypedText.h
 *
 *  Created on: 30 wrz 2016
 *      Author: Uzume
 */

#ifndef TYPEDTEXT_TYPEDTEXT_H_
#define TYPEDTEXT_TYPEDTEXT_H_

#include "../Types/Types.h"
#include "../Texts/Texts.h"
#include "../Font/Font.h"

const TypedTextId TYPED_TEXT_INVALID = 0xFFFFU;
class TypedText {
public:
	struct TypedTextData {
		const uint8_t fontIdx;
		const Aligment aligment :2;
		const TextDirection direction :2;
	};
	TypedText(const TypedTextId id = TYPED_TEXT_INVALID) :
			m_typedTextId(id) {

	}
	virtual ~TypedText();
	TypedTextId getTypeTextId(void) const;
	const Font* getFont(void) const;
	const Aligment getAligment(void);
	const TextDirection getTextDirection(void);
	bool hasValidId(void) const;
	const Unicode::UnicodeChar* getText() const;
	static void registerTypedTextDatabase(const TypedTextData* data, const Font* const* f, uint16_t n);
	static void registerTexts(const Texts* t);
private:
	TypedTextId m_typedTextId;
	static const TypedTextData* m_typedTexts;
	static uint16_t m_numberOfTypedTexts;
	static const Texts* m_texts;
	static const Font* const* m_fonts;
};

#endif /* TYPEDTEXT_TYPEDTEXT_H_ */
