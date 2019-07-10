/*
 * FontManager.cpp
 *
 *  Created on: 21 lis 2016
 *      Author: Uzume
 */

#include "FontManager.h"

FontProvider* FontManager::m_provider;

void FontManager::setFontProvider(FontProvider* fontProvider){
	m_provider = fontProvider;
}
Font* FontManager::getFont(FontId fontId){
	return m_provider->getFont(fontId);
}
