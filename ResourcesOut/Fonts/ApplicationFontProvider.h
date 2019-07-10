#ifndef APPLICATIONFONTPROVIDER_H_
#define APPLICATIONFONTPROVIDER_H_
#include "FontManager.h"

struct Typography {
	static const FontId Normal = 0;
	static const FontId Keyboard = 1;
	static const FontId Info = 2;
};

class ApplicationFontProvider : public FontProvider {
	public:
		virtual Font* getFont(FontId fontId);
};
#endif