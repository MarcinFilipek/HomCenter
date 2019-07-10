/*
 * ListLayout.h
 *
 *  Created on: 25 sie 2017
 *      Author: Uzume
 */

#ifndef TOUCH_LISTLAYOUT_LISTLAYOUT_H_
#define TOUCH_LISTLAYOUT_LISTLAYOUT_H_

#include "../Container/Container.h"

class ListLayout : public Container{
public:
	ListLayout() : xOffset(0), yOffset(0) {
	}
	virtual ~ListLayout() {

	}
	void add(Drawable* child);
	void removeAll();
private:
	int16_t xOffset;
	int16_t yOffset;
};

#endif /* TOUCH_LISTLAYOUT_LISTLAYOUT_H_ */
