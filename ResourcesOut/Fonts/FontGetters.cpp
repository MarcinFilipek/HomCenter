#include "../../Touch/InternalFlashFont/InternalFlashFont.h"

extern const GlyphNode glyphs_Arial_11_8bpp[];
extern const uint8_t unicodes_Arial_11_8bpp[];
InternalFlashFont& getFont_Arial_11_8bpp();

InternalFlashFont& getFont_Arial_11_8bpp(){
	uint16_t size = 34; 
	static InternalFlashFont Arial_11_8bpp(glyphs_Arial_11_8bpp, size, 11 ,0 , 8, unicodes_Arial_11_8bpp);
	return Arial_11_8bpp;
}

extern const GlyphNode glyphs_Calibri_16_8bpp[];
extern const uint8_t unicodes_Calibri_16_8bpp[];
InternalFlashFont& getFont_Calibri_16_8bpp();

InternalFlashFont& getFont_Calibri_16_8bpp(){
	uint16_t size = 114; 
	static InternalFlashFont Calibri_16_8bpp(glyphs_Calibri_16_8bpp, size, 16 ,0 , 8, unicodes_Calibri_16_8bpp);
	return Calibri_16_8bpp;
}

extern const GlyphNode glyphs_Cambria_10_8bpp[];
extern const uint8_t unicodes_Cambria_10_8bpp[];
InternalFlashFont& getFont_Cambria_10_8bpp();

InternalFlashFont& getFont_Cambria_10_8bpp(){
	uint16_t size = 14; 
	static InternalFlashFont Cambria_10_8bpp(glyphs_Cambria_10_8bpp, size, 10 ,0 , 8, unicodes_Cambria_10_8bpp);
	return Cambria_10_8bpp;
}

