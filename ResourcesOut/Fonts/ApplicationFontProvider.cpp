#include "ApplicationFontProvider.h"
#include "InternalFlashFont.h"

extern InternalFlashFont& getFont_Arial_11_8bpp();
extern InternalFlashFont& getFont_Calibri_16_8bpp();
extern InternalFlashFont& getFont_Cambria_10_8bpp();

Font* ApplicationFontProvider::getFont(FontId fontId){
	switch(fontId){
		case Typography::Normal:
			return &(getFont_Arial_11_8bpp());
		case Typography::Keyboard:
			return &(getFont_Calibri_16_8bpp());
		case Typography::Info:
			return &(getFont_Cambria_10_8bpp());
		default:
			return 0;
	}
}
