#include "BitmapDatabase.h";

extern uint8_t Background[];
extern uint8_t Bg_room[];
extern uint8_t Checked[];
extern uint8_t Cube[];
extern uint8_t Cube_down[];
extern uint8_t Exit[];
extern uint8_t Highlight_dot[];
extern uint8_t Kafelek[];
extern uint8_t Keyboard_background[];
extern uint8_t Keyboard_key2_highlighted[];
extern uint8_t Keyboard_key_highlighted[];
extern uint8_t Keyboard_space_highlighted[];
extern uint8_t Message[];
extern uint8_t Normal_dot[];
extern uint8_t Plus[];
extern uint8_t Plus_down[];
extern uint8_t Power[];
extern uint8_t Power_down[];
extern uint8_t Room_icon[];
extern uint8_t Room_icon_down[];
extern uint8_t SwitchOff[];
extern uint8_t SwitchOffOff[];
extern uint8_t SwitchOff_Down[];
extern uint8_t SwitchOn[];
extern uint8_t SwitchOn_Down[];
const Bitmap::BitmapData bitmap_database[] = {
	{ Background, 480, 272, Bitmap::RGB565},
	{ Bg_room, 480, 272, Bitmap::RGB565},
	{ Checked, 64, 64, Bitmap::ARGB8888},
	{ Cube, 64, 64, Bitmap::ARGB8888},
	{ Cube_down, 64, 64, Bitmap::ARGB8888},
	{ Exit, 32, 32, Bitmap::ARGB8888},
	{ Highlight_dot, 16, 16, Bitmap::ARGB8888},
	{ Kafelek, 110, 110, Bitmap::RGB565},
	{ Keyboard_background, 480, 272, Bitmap::RGB565},
	{ Keyboard_key2_highlighted, 84, 26, Bitmap::ARGB8888},
	{ Keyboard_key_highlighted, 40, 26, Bitmap::ARGB8888},
	{ Keyboard_space_highlighted, 304, 26, Bitmap::ARGB8888},
	{ Message, 384, 218, Bitmap::ARGB8888},
	{ Normal_dot, 16, 16, Bitmap::ARGB8888},
	{ Plus, 64, 64, Bitmap::ARGB8888},
	{ Plus_down, 64, 64, Bitmap::ARGB8888},
	{ Power, 64, 64, Bitmap::ARGB8888},
	{ Power_down, 64, 64, Bitmap::ARGB8888},
	{ Room_icon, 64, 64, Bitmap::ARGB8888},
	{ Room_icon_down, 64, 64, Bitmap::ARGB8888},
	{ SwitchOff, 128, 128, Bitmap::ARGB8888},
	{ SwitchOffOff, 64, 64, Bitmap::ARGB8888},
	{ SwitchOff_Down, 128, 128, Bitmap::ARGB8888},
	{ SwitchOn, 128, 128, Bitmap::ARGB8888},
	{ SwitchOn_Down, 128, 128, Bitmap::ARGB8888},
};
namespace BitmapDatabase
{
	const Bitmap::BitmapData* getInstance()
	{
			return bitmap_database;
	}
	uint16_t getInstanceSize()
	{
			return (uint16_t)(sizeof(bitmap_database) / sizeof(Bitmap::BitmapData));
	}
}
