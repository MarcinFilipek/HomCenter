#include "Texts.h"
#include "../TypedText/TypedText.h"
#include "../TypedTextDatabase/TypedTextDatabase.h"

extern const Unicode::UnicodeChar* const textsPL[];
extern const Unicode::UnicodeChar* const textsGB[];

const Unicode::UnicodeChar* const * languagesArray[] = {
	textsPL,
	textsGB,
};

LanguageId Texts::currentLanguage = 0;

const Unicode::UnicodeChar* const * Texts::currentLanguagePtr = languagesArray[currentLanguage];

void Texts::setLanguage(LanguageId id) {
	currentLanguage = id;
	currentLanguagePtr = languagesArray[currentLanguage];

	TypedText::registerTypedTextDatabase(
		TypedTextDatabase::getInstance(currentLanguage),
		TypedTextDatabase::getFonts(),
		TypedTextDatabase::getInstanceSize());
}

