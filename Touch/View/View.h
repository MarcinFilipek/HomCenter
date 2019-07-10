/*
 * View.h
 *
 *  Created on: 5 maj 2017
 *      Author: Uzume
 */

#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include "../Screen/Screen.h"

template<class T>
class View : public Screen {
public:
	View() : presenter(0){

	}
	virtual ~View(){

	}
	void bind(T& pres){
		presenter = &pres;
	}
protected:
	T* presenter;
};

#endif /* VIEW_VIEW_H_ */
