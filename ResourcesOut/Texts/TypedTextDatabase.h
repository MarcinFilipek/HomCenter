#ifndef TYPEDTEXTDATABASE_HPP
#define TYPEDTEXTDATABASE_HPP

#include "../TypedText/TypedText.h"

namespace TypedTextDatabase
{
		class TypedTextData;
		const TypedText::TypedTextData* getInstance(LanguageId language);
		uint16_t getInstanceSize(void);
		const Font* const* getFonts();
}
#endif