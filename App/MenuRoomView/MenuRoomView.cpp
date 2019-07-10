/*
 * MenuRoomView.cpp
 *
 *  Created on: 22 lut 2018
 *      Author: Uzume
 */

#include "MenuRoomView.h"
#include "../../ResourcesOut/Images/BitmapDatabase.h"
#include "../Touch/Color/Color.h"
#include "../../ResourcesOut/Texts/TextKeysAndLanguages.h"

MenuRoomView::MenuRoomView() :
		buttonPressedCallback(this, &MenuRoomView::buttonPressedHandler),
		buttonDevicePressedCallback(this, &MenuRoomView::buttonDevicePressedHandler),
		cordMainButton{
			{{48, 35}, {208, 35}, {368, 35}},
			{{48, 140}, {208, 140}, {368, 140}}}
{

}
void MenuRoomView::setupScreen(void) {
	background.setBitmap(Bitmap(BITMAP_BG_ROOM_ID));
	background.setXY(0, 0);

	buttonExit.setBitmaps(Bitmap(BITMAP_EXIT_ID), Bitmap(BITMAP_EXIT_ID));
	buttonExit.setXY(445, 3);
	buttonExit.setAction(buttonPressedCallback);

	uint8_t numOfDevices = presenter->getNumOfDevices();
	for(uint8_t i = 0; i < NUM_OF_COL_MAIN_BUTTON * NUM_OF_ROW_MAIN_BUTTON; i++){
		buttonDevice[i].setBitmaps(Bitmap(presenter->getBitmapIdForDevice(i)), Bitmap(BITMAP_CUBE_DOWN_ID));
		buttonDevice[i].setXY(cordMainButton[i / NUM_OF_COL_MAIN_BUTTON][i % NUM_OF_COL_MAIN_BUTTON].x,
				cordMainButton[i / NUM_OF_COL_MAIN_BUTTON][i % NUM_OF_COL_MAIN_BUTTON].y);
		buttonDevice[i].setAction(buttonDevicePressedCallback);
		if(i + 1 > numOfDevices){
			buttonDevice[i].setVisible(false);
		}
	}

	uint8_t corX = numOfDevices % NUM_OF_COL_MAIN_BUTTON;
	uint8_t corY = numOfDevices / NUM_OF_COL_MAIN_BUTTON;
	buttonAddDevice.setBitmaps(Bitmap(BITMAP_PLUS_ID), Bitmap(BITMAP_PLUS_DOWN_ID));
	buttonAddDevice.setXY(cordMainButton[corY][corX].x, cordMainButton[corY][corX].y);
	buttonAddDevice.setAction(buttonPressedCallback);

	textAddDevice.setTypedText(TypedText(T_DODAJ_URZADZENIE));
	textAddDevice.setColor(Color::getColorFrom24BitRGB(0x00, 0x00, 0x00));
	textAddDevice.setPosition(cordMainButton[corY][corX].x,cordMainButton[corY][corX].y + 70, 95, 25);

	if(numOfDevices >= 6){
		buttonAddDevice.setVisible(false);
		textAddDevice.setVisible(false);
	}


	add(&background);
	add(&buttonExit);
	for(uint8_t j = 0; j < NUM_OF_COL_MAIN_BUTTON * NUM_OF_ROW_MAIN_BUTTON; j++){
		add(&buttonDevice[j]);
	}
	add(&buttonAddDevice);
	add(&textAddDevice);
}

void MenuRoomView::buttonPressedHandler(const AbstractButton& button) {
	if (&button == &buttonExit) {
		presenter->exit();
	}
	if (&button == &buttonAddDevice) {
		presenter->addDevice();
	}
}

void MenuRoomView::buttonDevicePressedHandler(const AbstractButton& button){
	for(uint8_t j = 0; j < NUM_OF_COL_MAIN_BUTTON * NUM_OF_ROW_MAIN_BUTTON; j++){
		if(&button == &buttonDevice[j]){
			presenter->goToDevice(j);
		}
	}
}
