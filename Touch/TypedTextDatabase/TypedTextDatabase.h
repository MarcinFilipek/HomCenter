/*
 * TypedTextDatabase.h
 *
 *  Created on: 3 paü 2016
 *      Author: Uzume
 */

#ifndef TYPEDTEXTDATABASE_TYPEDTEXTDATABASE_H_
#define TYPEDTEXTDATABASE_TYPEDTEXTDATABASE_H_

#include "../TypedText/TypedText.h"


class TypedTextDatabase {
public:
	static const TypedText::TypedTextData* getInstance(LanguageId language);
	static uint16_t getInstanceSize(void);
	static const Font* const* getFonts();
};

#endif /* TYPEDTEXTDATABASE_TYPEDTEXTDATABASE_H_ */
