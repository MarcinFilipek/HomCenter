#include "TypedTextDatabase.h"
#include "../InternalFlashFont/InternalFlashFont.h"

extern InternalFlashFont& getFont_Arial_11_8bpp();
extern InternalFlashFont& getFont_Calibri_16_8bpp();
extern InternalFlashFont& getFont_Cambria_10_8bpp();

const Font* const fonts[] = {
	&(getFont_Arial_11_8bpp()),
	&(getFont_Calibri_16_8bpp()),
	&(getFont_Cambria_10_8bpp()),
};

const TypedText::TypedTextData typedText_database_DEFAULT[] = {
	{ 0, LEFT, TEXT_DIRECTION_LTR },
	{ 2, CENTER, TEXT_DIRECTION_LTR },
	{ 0, LEFT, TEXT_DIRECTION_LTR },
	{ 0, LEFT, TEXT_DIRECTION_LTR },
	{ 1, LEFT, TEXT_DIRECTION_LTR },
	{ 1, LEFT, TEXT_DIRECTION_LTR },
	{ 1, LEFT, TEXT_DIRECTION_LTR },
	{ 1, LEFT, TEXT_DIRECTION_LTR },
	{ 1, LEFT, TEXT_DIRECTION_LTR },
	{ 1, LEFT, TEXT_DIRECTION_LTR },
	{ 1, LEFT, TEXT_DIRECTION_LTR },
	{ 1, LEFT, TEXT_DIRECTION_LTR },
	{ 1, LEFT, TEXT_DIRECTION_LTR },
};

const TypedText::TypedTextData* const typedTestDatabaseArray[] = {
	typedText_database_DEFAULT, 
	typedText_database_DEFAULT, 
};

namespace TypedTextDatabase
{
	const TypedText::TypedTextData* getInstance(LanguageId language) {
		return typedTestDatabaseArray[language];
	}

	uint16_t getInstanceSize(void) {
		return sizeof(typedText_database_DEFAULT) / sizeof(TypedText::TypedTextData);
	}

	const Font* const * getFonts(){
		return fonts;
	}
}
