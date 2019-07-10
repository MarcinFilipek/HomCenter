/*
 * TestPresenter.h
 *
 *  Created on: 5 maj 2017
 *      Author: Uzume
 */

#ifndef TESTPRESENTER_TESTPRESENTER_H_
#define TESTPRESENTER_TESTPRESENTER_H_

#include "../Touch/Presenter/Presenter.h"
#include "../Model/ModelListener.h"

class MainView;

class TestPresenter : public Presenter, public ModelListener {
public:
	TestPresenter(MainView& v);
	virtual ~TestPresenter();
	void activate(void);
	void deactivate(void);
	void upPressed(void);
	void downPressed(void);
private:
	TestPresenter();
	MainView& view;
};

#endif /* TESTPRESENTER_TESTPRESENTER_H_ */
