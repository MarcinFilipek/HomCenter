/*
 * TypedTextDatabase.cpp
 *
 *  Created on: 3 paü 2016
 *      Author: Uzume
 */

#include "TypedTextDatabase.h"
#include "../InternalFlashFont/InternalFlashFont.h"

const TypedText::TypedTextData typedText_database_DEFAULT[] = {
		{ 0, LEFT, TEXT_DIRECTION_LTR },
		{ 0, LEFT, TEXT_DIRECTION_LTR },
		{ 0, LEFT, TEXT_DIRECTION_LTR },
		{ 0, LEFT, TEXT_DIRECTION_LTR },
		{ 0, LEFT, TEXT_DIRECTION_LTR },
		{ 0, LEFT, TEXT_DIRECTION_LTR },
		{ 0, LEFT, TEXT_DIRECTION_LTR },
};


const TypedText::TypedTextData* const typedTestDatabaseArray[] = {
		typedText_database_DEFAULT,
		typedText_database_DEFAULT};




extern InternalFlashFont& getFont_My_15_4bpp();
const Font* const fonts[] = {
		&(getFont_My_15_4bpp())
};

const TypedText::TypedTextData* TypedTextDatabase::getInstance(
		LanguageId language) {
	return typedTestDatabaseArray[language];
}

uint16_t TypedTextDatabase::getInstanceSize(void) {
	return sizeof(typedText_database_DEFAULT) / sizeof(TypedText::TypedTextData);
}

const Font* const * TypedTextDatabase::getFonts(){
	return fonts;
}
