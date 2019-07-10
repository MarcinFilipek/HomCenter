/*
 * KeyboardPresenter.h
 *
 *  Created on: 28 cze 2017
 *      Author: Marcin
 */

#ifndef KEYBOARDPRESENTER_KEYBOARDPRESENTER_H_
#define KEYBOARDPRESENTER_KEYBOARDPRESENTER_H_

#include "../Touch/Presenter/Presenter.h"
#include "../Model/ModelListener.h"

class KeyboardView;

class KeyboardPresenter: public Presenter, public ModelListener {
public:
	KeyboardPresenter(KeyboardView& v);
	virtual ~KeyboardPresenter();
	void activate(void);
	void deactivate(void);
	void exit(void);
private:
	KeyboardPresenter();
	KeyboardView& view;
};

#endif /* KEYBOARDPRESENTER_KEYBOARDPRESENTER_H_ */
