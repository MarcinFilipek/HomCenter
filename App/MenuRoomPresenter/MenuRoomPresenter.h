/*
 * MenuRoomPresenter.h
 *
 *  Created on: 22 lut 2018
 *      Author: Uzume
 */

#ifndef APP_MENUROOMPRESENTER_MENUROOMPRESENTER_H_
#define APP_MENUROOMPRESENTER_MENUROOMPRESENTER_H_

#include "../Touch/Presenter/Presenter.h"
#include "../Model/ModelListener.h"

class MenuRoomView;

class MenuRoomPresenter: public Presenter, public ModelListener {
public:
	MenuRoomPresenter(MenuRoomView& v);
	virtual ~MenuRoomPresenter();
	void activate(void);
	void deactivate(void);
	void exit(void);
	uint8_t getNumOfDevices();
	void addDevice();
	uint16_t getBitmapIdForDevice(uint8_t index);
	void goToDevice(uint8_t index);
private:
	MenuRoomView& view;
};

#endif /* APP_MENUROOMPRESENTER_MENUROOMPRESENTER_H_ */
