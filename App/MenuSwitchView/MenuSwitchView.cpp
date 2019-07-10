/*
 * MenuSwitchView.cpp
 *
 *  Created on: 3 paŸ 2018
 *      Author: Uzume
 */

#include "MenuSwitchView.h"
#include "../../ResourcesOut/Images/BitmapDatabase.h"

MenuSwitchView::MenuSwitchView() :
	buttonPressedCallback(this, &MenuSwitchView::buttonPressedHandler)
{

}

MenuSwitchView::~MenuSwitchView() {

}

void MenuSwitchView::setupScreen(void){
	background.setBitmap(Bitmap(BITMAP_BG_ROOM_ID));
	background.setXY(0, 0);

	buttonExit.setBitmaps(Bitmap(BITMAP_EXIT_ID), Bitmap(BITMAP_EXIT_ID));
	buttonExit.setXY(445, 3);
	buttonExit.setAction(buttonPressedCallback);


	switchBitmap();
	buttonRelay1.setXY(56, 72);
	buttonRelay1.setAction(buttonPressedCallback);

	buttonRelay2.setXY(296, 72);
	buttonRelay2.setAction(buttonPressedCallback);

	add(&background);
	add(&buttonExit);
	add(&buttonRelay1);
	add(&buttonRelay2);
}

void MenuSwitchView::tearDownScreen(void){

}

void MenuSwitchView::buttonPressedHandler(const AbstractButton& button){
	if(&button == &buttonExit){
		presenter->exit();
	}
	if(&button == &buttonRelay1){
		presenter->toggleRelay1();
		switchBitmap();
	}
	if(&button == &buttonRelay2){
		presenter->toggleRelay2();
		switchBitmap();
	}
}

void MenuSwitchView::switchBitmap(){
	if(presenter->getStateRelay1()){
		buttonRelay1.setBitmaps(Bitmap(BITMAP_SWITCHON_ID), Bitmap(BITMAP_SWITCHON_DOWN_ID));
	} else {
		buttonRelay1.setBitmaps(Bitmap(BITMAP_SWITCHOFF_ID), Bitmap(BITMAP_SWITCHOFF_DOWN_ID));
	}
	if(presenter->getStateRelay2()){
		buttonRelay2.setBitmaps(Bitmap(BITMAP_SWITCHON_ID), Bitmap(BITMAP_SWITCHON_DOWN_ID));
	} else {
		buttonRelay2.setBitmaps(Bitmap(BITMAP_SWITCHOFF_ID), Bitmap(BITMAP_SWITCHOFF_DOWN_ID));
	}
}
