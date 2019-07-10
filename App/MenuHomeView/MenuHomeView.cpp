/*
 * MenuHomeView.cpp
 *
 *  Created on: 22 sie 2017
 *      Author: Uzume
 */

#include "MenuHomeView.h"
#include "../../ResourcesOut/Images/BitmapDatabase.h"
#include "../Touch/Color/Color.h"
#include "../../ResourcesOut/Texts/TextKeysAndLanguages.h"

MenuHomeView::MenuHomeView() :
		buttonPressedCallback(this, &MenuHomeView::buttonPressedHandler),
		buttonRoomPressedCallback(this, &MenuHomeView::buttonRoomPressedHandler),
		menuStateChangeInitiatedCallback(this, &MenuHomeView::menuStateChangeInitiatedHandler),
		menuStateChangeEndedCallback(this, &MenuHomeView::menuStateChangeEndedHandler),
		cordMainButton{
			{{48, 35}, {208, 35}, {368, 35}},
			{{48, 140}, {208, 140}, {368, 140}}}
{
}
MenuHomeView::~MenuHomeView() {
}

void MenuHomeView::setupScreen(void){
	menuContainer.setXY(0, 0);
	menuContainer.setSwipeCutoff(80);
	menuContainer.setEndSwipeElasticWidth(50);
	menuContainer.setDotIndicatorBitmaps(Bitmap(BITMAP_NORMAL_DOT_ID), Bitmap(BITMAP_HIGHLIGHT_DOT_ID));
	menuContainer.setDotIndicatorXYWithCenteredX(480 / 2, 272 - 16);
	menuContainer.setMenuChangeInitiatedCallback(menuStateChangeInitiatedCallback);
	menuContainer.setMenuChangeEndedCallback(menuStateChangeEndedCallback);
	menuContainer.setTouchable(true);

	textHeader.setTypedText(T_DOM);
	textHeader.setColor(Color::getColorFrom24BitRGB(0x00, 0x00, 0x00));
	textHeader.setPosition(225,5, 50, 20);

	uint8_t numOfRoom = presenter->getNumOfRoom();
	for(uint8_t i = 0; i < NUM_OF_COL_MAIN_BUTTON * NUM_OF_ROW_MAIN_BUTTON; i++){
		buttonRoom[i].setBitmaps(Bitmap(BITMAP_ROOM_ICON_ID), Bitmap(BITMAP_ROOM_ICON_DOWN_ID));
		buttonRoom[i].setXY(cordMainButton[i / NUM_OF_COL_MAIN_BUTTON][i % NUM_OF_COL_MAIN_BUTTON].x,
				cordMainButton[i / NUM_OF_COL_MAIN_BUTTON][i % NUM_OF_COL_MAIN_BUTTON].y);
		buttonRoom[i].setAction(buttonRoomPressedCallback);
		if(i + 1 > numOfRoom){
			buttonRoom[i].setVisible(false);
		}
	}

	uint8_t corX = numOfRoom % NUM_OF_COL_MAIN_BUTTON;
	uint8_t corY = numOfRoom / NUM_OF_COL_MAIN_BUTTON;
	buttonAddRoom.setBitmaps(Bitmap(BITMAP_PLUS_ID), Bitmap(BITMAP_PLUS_DOWN_ID));
	buttonAddRoom.setXY(cordMainButton[corY][corX].x, cordMainButton[corY][corX].y);
	buttonAddRoom.setAction(buttonPressedCallback);

	textAddRoom.setTypedText(TypedText(T_DODAJ_POKOJ));
	textAddRoom.setColor(Color::getColorFrom24BitRGB(0x00, 0x00, 0x00));
	textAddRoom.setPosition(cordMainButton[corY][corX].x,cordMainButton[corY][corX].y + 70, 95, 25);

	if(numOfRoom >= 6){
		buttonAddRoom.setVisible(false);
		textAddRoom.setVisible(false);
	}

	textNameOfRoom.setWildcard(presenter->getBuffor());
	textNameOfRoom.setTypedText(TypedText(T_ENTEREDTEXT));
	textNameOfRoom.setPosition(0, 220, 100, 30);
	textNameOfRoom.setColor(Color::getColorFrom24BitRGB(0xFF, 0x00, 0x00));


	for(uint8_t i = 0; i < NUMBER_OF_SCREENS; i++){
		backgroundScreen[i].setBitmap(Bitmap(BITMAP_BG_ROOM_ID));
		backgroundScreen[i].setXY(0, 0);
		containerScreen[i].setPosition(0, 0, backgroundScreen[i].getWidth(), backgroundScreen[i].getHeight());
		containerScreen[i].add(&backgroundScreen[i]);
		if(i == 0){
			containerScreen[i].add(&textHeader);
			for(uint8_t j = 0; j < NUM_OF_COL_MAIN_BUTTON * NUM_OF_ROW_MAIN_BUTTON; j++){
				containerScreen[i].add(&buttonRoom[j]);
			}
			containerScreen[i].add(&buttonAddRoom);
			containerScreen[i].add(&textAddRoom);
			containerScreen[i].add(&textNameOfRoom);
		}

		menuContainer.add(&containerScreen[i]);
	}
	add(&menuContainer);
}

void MenuHomeView::tearDownScreen(void){

}

void MenuHomeView::menuStateChangeInitiatedHandler(const SwipeContainer& sc){

}

void MenuHomeView::menuStateChangeEndedHandler(const SwipeContainer& sc){

}

void MenuHomeView::setSelectedMenuIndex(uint8_t index)
{
    menuContainer.setSelectedScreen(index);
}

void MenuHomeView::buttonPressedHandler(const AbstractButton& button){
	if(&button == &buttonAddRoom){
		presenter->addRoom();
	}
}

void MenuHomeView::buttonRoomPressedHandler(const AbstractButton& button){
	for(uint8_t j = 0; j < NUM_OF_COL_MAIN_BUTTON * NUM_OF_ROW_MAIN_BUTTON; j++){
		if(&button == &buttonRoom[j]){
			presenter->goToRoom(j);
		}
	}
}
