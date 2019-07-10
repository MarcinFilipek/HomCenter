/*
 * ModelListener.h
 *
 *  Created on: 21 lut 2018
 *      Author: Uzume
 */

#ifndef APP_MODEL_MODELLISTENER_H_
#define APP_MODEL_MODELLISTENER_H_

#include "../../Touch/Unicode/Unicode.h"

class Model;

class ModelListener {
public:
	ModelListener();
	virtual ~ModelListener();
	void bind(Model* m);
	Unicode::UnicodeChar* getBuffor(){ return 0;}
protected:
	Model* model;
};

#endif /* APP_MODEL_MODELLISTENER_H_ */
