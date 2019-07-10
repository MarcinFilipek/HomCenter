/*
 * Texts.h
 *
 *  Created on: 3 paü 2016
 *      Author: Uzume
 */

#include "../Unicode/Unicode.h"

#ifndef TEXTS_TEXTS_H_
#define TEXTS_TEXTS_H_

typedef uint8_t LanguageId;

class Texts {
public:
	static void setLanguage(LanguageId id);
	static LanguageId getLanguage() {
		return currentLanguage;
	}
	const Unicode::UnicodeChar* getText(TypedTextId id) const {
		return currentLanguagePtr[id];
	}
private:
	static const Unicode::UnicodeChar* const * currentLanguagePtr;
	static LanguageId currentLanguage;
};

#endif /* TEXTS_TEXTS_H_ */
