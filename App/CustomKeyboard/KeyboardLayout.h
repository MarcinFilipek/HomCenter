/*
 * KeyboardLayout.h
 *
 *  Created on: 18 lis 2016
 *      Author: Uzume
 */

#ifndef CUSTOMKEYBOARD_KEYBOARDLAYOUT_H_
#define CUSTOMKEYBOARD_KEYBOARDLAYOUT_H_

#include "../Touch/Keyboard/Keyboard.h"
#include "../../ResourcesOut/Texts/TextKeysAndLanguages.h"
#include "../../ResourcesOut/Fonts/ApplicationFontProvider.h"
#include "../../ResourcesOut/Images/BitmapDatabase.h"

static const Keyboard::Key keyArray[30] =
{
    { 1, Rect(0, 140, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 2, Rect(0 + 44, 140, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 3, Rect(0 + 44 * 2, 140, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 4, Rect(0 + 44 * 3, 140, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 5, Rect(0 + 44 * 4, 140, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 6, Rect(0 + 44 * 5, 140, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 7, Rect(0 + 44 * 6, 140, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 8, Rect(0 + 44 * 7, 140, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 9, Rect(0 + 44 * 8, 140, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {10, Rect(0 + 44 * 9, 140, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {11, Rect(0 + 44 * 10, 140, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},

    {12, Rect(0, 172, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {13, Rect(0 + 44, 172, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {14, Rect(0 + 44 * 2, 172, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {15, Rect(0 + 44 * 3, 172, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {16, Rect(0 + 44 * 4, 172, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {17, Rect(0 + 44 * 5, 172, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {18, Rect(0 + 44 * 6, 172, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {19, Rect(0 + 44 * 7, 172, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {20, Rect(0 + 44 * 8, 172, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {21, Rect(0 + 44 * 9, 172, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {22, Rect(0 + 44 * 10, 172, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},

    {23, Rect(88, 204, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {24, Rect(88 + 44, 204, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {25, Rect(88 + 44 * 2, 204, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {26, Rect(88 + 44 * 3, 204, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {27, Rect(88 + 44 * 4, 204, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {28, Rect(88 + 44 * 5, 204, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {29, Rect(88 + 44 * 6, 204, 40, 26), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {30, Rect(88, 235, 304, 26), BITMAP_KEYBOARD_SPACE_HIGHLIGHTED_ID}
};

static Keyboard::CallbackArea callbackAreas[4] =
{
    {Rect(0, 204, 84, 26), 0, BITMAP_KEYBOARD_KEY2_HIGHLIGHTED_ID},     	// caps-lock
    {Rect(396, 204, 84, 26), 0, BITMAP_KEYBOARD_KEY2_HIGHLIGHTED_ID},  	// backspace
    {Rect(0, 235, 84, 26), 0, BITMAP_KEYBOARD_KEY2_HIGHLIGHTED_ID},       // mode
	{Rect(396, 235, 84, 26), 0, BITMAP_KEYBOARD_KEY2_HIGHLIGHTED_ID},     // ok
};

static const Keyboard::Layout layout =
{
	BITMAP_KEYBOARD_BACKGROUND_ID,
    keyArray,
    30,
    callbackAreas,
    4,
    Rect(15, 10, 11 * 28, 40),
    TypedText(T_ENTEREDTEXT),
	0xFF0000,
    Typography::Keyboard,
    0xFFFFFF
};

#endif /* CUSTOMKEYBOARD_KEYBOARDLAYOUT_H_ */
