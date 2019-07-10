/*
 * DotIndicator.h
 *
 *  Created on: 25 sie 2017
 *      Author: Uzume
 */

#ifndef APP_COMMON_DOTINDICATOR_DOTINDICATOR_H_
#define APP_COMMON_DOTINDICATOR_DOTINDICATOR_H_

#include "../../../Touch/Container/Container.h"
#include "../../../Touch/Image/Image.h"
#include "../../../Touch/ListLayout/ListLayout.h"

class DotIndicator : public Container {
public:
	DotIndicator();
	virtual ~DotIndicator();
	void setnumberOfDots(uint8_t num);
	void setBitmaps(const Bitmap& normalDot, const Bitmap& highlightedDot);
	void goRight();
	void goLeft();
	void setHighlightPosition(uint8_t index);
private:
	static const uint8_t MAX_SIZE = 10;

	ListLayout unselectedDots;
	Image dotHighlighted;
	Image dotNormal[MAX_SIZE];

    uint8_t numberOfDots;
    uint8_t currentDot;
};

#endif /* APP_COMMON_DOTINDICATOR_DOTINDICATOR_H_ */
