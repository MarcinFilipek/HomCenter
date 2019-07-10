#ifndef BITMAPDATABASE_H
#define BITMAPDATABASE_H

#include "Bitmap.h";

const uint16_t BITMAP_BACKGROUND_ID = 0; // Size: 480x272
const uint16_t BITMAP_BG_ROOM_ID = 1; // Size: 480x272
const uint16_t BITMAP_CHECKED_ID = 2; // Size: 64x64
const uint16_t BITMAP_CUBE_ID = 3; // Size: 64x64
const uint16_t BITMAP_CUBE_DOWN_ID = 4; // Size: 64x64
const uint16_t BITMAP_EXIT_ID = 5; // Size: 32x32
const uint16_t BITMAP_HIGHLIGHT_DOT_ID = 6; // Size: 16x16
const uint16_t BITMAP_KAFELEK_ID = 7; // Size: 110x110
const uint16_t BITMAP_KEYBOARD_BACKGROUND_ID = 8; // Size: 480x272
const uint16_t BITMAP_KEYBOARD_KEY2_HIGHLIGHTED_ID = 9; // Size: 84x26
const uint16_t BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID = 10; // Size: 40x26
const uint16_t BITMAP_KEYBOARD_SPACE_HIGHLIGHTED_ID = 11; // Size: 304x26
const uint16_t BITMAP_MESSAGE_ID = 12; // Size: 384x218
const uint16_t BITMAP_NORMAL_DOT_ID = 13; // Size: 16x16
const uint16_t BITMAP_PLUS_ID = 14; // Size: 64x64
const uint16_t BITMAP_PLUS_DOWN_ID = 15; // Size: 64x64
const uint16_t BITMAP_POWER_ID = 16; // Size: 64x64
const uint16_t BITMAP_POWER_DOWN_ID = 17; // Size: 64x64
const uint16_t BITMAP_ROOM_ICON_ID = 18; // Size: 64x64
const uint16_t BITMAP_ROOM_ICON_DOWN_ID = 19; // Size: 64x64
const uint16_t BITMAP_SWITCHOFF_ID = 20; // Size: 128x128
const uint16_t BITMAP_SWITCHOFFOFF_ID = 21; // Size: 64x64
const uint16_t BITMAP_SWITCHOFF_DOWN_ID = 22; // Size: 128x128
const uint16_t BITMAP_SWITCHON_ID = 23; // Size: 128x128
const uint16_t BITMAP_SWITCHON_DOWN_ID = 24; // Size: 128x128

namespace BitmapDatabase
{
	class BitmapData;
	const Bitmap::BitmapData* getInstance();
	uint16_t getInstanceSize();
}

#endif
