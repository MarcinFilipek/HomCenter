/*
 * FontManager.h
 *
 *  Created on: 21 lis 2016
 *      Author: Uzume
 */

#ifndef FONTMANAGER_FONTMANAGER_H_
#define FONTMANAGER_FONTMANAGER_H_

#include "../Font/Font.h"

class FontProvider {
public:
	virtual Font* getFont(FontId fontId) = 0;
	virtual ~FontProvider() {
	}
};

class FontManager {
public:
	static void setFontProvider(FontProvider* fontProvider);
    static Font* getFont(FontId fontId);
private:
    static FontProvider* m_provider;
};

#endif /* FONTMANAGER_FONTMANAGER_H_ */
