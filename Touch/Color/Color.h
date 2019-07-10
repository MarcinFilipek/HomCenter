/*
 * Color.h
 *
 *  Created on: 30 wrz 2016
 *      Author: Uzume
 */

#ifndef COLOR_COLOR_H_
#define COLOR_COLOR_H_

#include "../Types/Types.h"
#include "../Lcd/Lcd.h"

class Color {
public:
	static colortype getColorFrom24BitRGB(uint8_t red, uint8_t green, uint8_t blue){
		colortype color = (red << 16) | (green << 8) | (blue);
		return color;
	}

    static inline uint8_t getRedColor(colortype color)
    {
        uint8_t bitDepth = Lcd::getBitDepth();
        return bitDepth == 16 ? ((color & 0xF800) >> 8) : bitDepth == 24 ? ((color.getColor32() >> 16) & 0xFF) : bitDepth == 4 ? ((color & 0xF) * 0x11) : bitDepth == 2 ? ((color & 0x3) * 0x55) : 0;
    }

    static inline uint8_t getGreenColor(colortype color)
    {
    	uint8_t bitDepth = Lcd::getBitDepth();
        return bitDepth == 16 ? ((color & 0x07E0) >> 3) : bitDepth == 24 ? ((color.getColor32() >> 8) & 0xFF) : bitDepth == 4 ? ((color & 0xF) * 0x11) : bitDepth == 2 ? ((color & 0x3) * 0x55) : 0;
    }

    static inline uint8_t getBlueColor(colortype color)
    {
    	uint8_t bitDepth = Lcd::getBitDepth();
        return bitDepth == 16 ? ((color & 0x001F) << 3) : bitDepth == 24 ? (color.getColor32() & 0xFF) : bitDepth == 4 ? ((color & 0xF) * 0x11) : bitDepth == 2 ? ((color & 0x3) * 0x55) : 0;
    }
};

#endif /* COLOR_COLOR_H_ */
