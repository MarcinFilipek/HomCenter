/*
 * Presenter.h
 *
 *  Created on: 4 maj 2017
 *      Author: Uzume
 */

#ifndef PRESENTER_PRESENTER_H_
#define PRESENTER_PRESENTER_H_

class Presenter {
public:
	virtual void activate(){

	}
	virtual void deactivate(){

	}
	virtual ~Presenter();
protected:
	Presenter();
};

#endif /* PRESENTER_PRESENTER_H_ */
