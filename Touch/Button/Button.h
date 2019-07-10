/*
 * Button.h
 *
 *  Created on: 26 sie 2016
 *      Author: Uzume
 */

#ifndef BUTTON_BUTTON_H_
#define BUTTON_BUTTON_H_

#include "../Bitmap/Bitmap.h"
#include "../AbstractButton/AbstractButton.h"

class Button : public AbstractButton {
public:
	Button();
	virtual ~Button();
	void setBitmaps(Bitmap up, Bitmap down);
	virtual void draw(const Rect& invalidatedArea) const;
	uint8_t getAlpha(void);
	void setAlpha(uint8_t alpha);
	Bitmap getCurrentlyDisplayedBitmap(void) const;
	virtual uint16_t getType() const;
private:
	Bitmap m_up;
	Bitmap m_down;
	uint8_t m_alpha;
};

#endif /* BUTTON_BUTTON_H_ */
