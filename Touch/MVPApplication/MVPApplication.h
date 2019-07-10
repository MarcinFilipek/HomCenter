/*
 * MVPApplication.h
 *
 *  Created on: 28 kwi 2017
 *      Author: Uzume
 */

#ifndef MVPAPPLICATION_MVPAPPLICATION_H_
#define MVPAPPLICATION_MVPAPPLICATION_H_

#include "../Touch/Application/Application.h"
#include "../Partition/Partition.h"
#include "../Touch/MVPHeap/MVPHeap.h"
#include "../Touch/Callback/Callback.h"
#include <new>

class Presenter;

class MVPApplication : public Application {
public:
	MVPApplication() : currentPresenter(0), pendingScreenTransitionCallback(0) {
		m_instance = this;
	}
	virtual ~MVPApplication(){

	}
	virtual void handlePendingScreenTransition(){
		evaluatePendingScreenTransition();
	}
protected:
	Presenter* currentPresenter;
	GenericCallback<>* pendingScreenTransitionCallback;

	void evaluatePendingScreenTransition(){
		if(pendingScreenTransitionCallback && pendingScreenTransitionCallback->isValid()){
			pendingScreenTransitionCallback->execute();
			pendingScreenTransitionCallback = 0;
		}
	}

};

#endif /* MVPAPPLICATION_MVPAPPLICATION_H_ */
