/*
 * ModelListener.cpp
 *
 *  Created on: 21 lut 2018
 *      Author: Uzume
 */

#include "ModelListener.h"

ModelListener::ModelListener(): model(0){
	// TODO Auto-generated constructor stub

}

ModelListener::~ModelListener() {
	// TODO Auto-generated destructor stub
}

void ModelListener::bind(Model* m){
	model = m;
}
