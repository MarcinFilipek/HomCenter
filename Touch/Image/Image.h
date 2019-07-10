/*
 * Image.h
 *
 *  Created on: 2 wrz 2016
 *      Author: Uzume
 */

#ifndef IMAGE_IMAGE_H_
#define IMAGE_IMAGE_H_

#include "../Bitmap/Bitmap.h"
#include "../Widget/Widget.h"

class Image : public Widget{
public:
	Image(const Bitmap& bmp = Bitmap());
	virtual ~Image();
	virtual void setBitmap(const Bitmap& bmp);
	virtual void draw(const Rect& invalidatedarea) const;
	void setAlpha(uint8_t alpha);
	uint8_t getAlpha(void);
	BitmapId getBitmap();
	virtual uint16_t getType() const;
protected:
	Bitmap m_bitmap;
	uint8_t m_alpha;
};

#endif /* IMAGE_IMAGE_H_ */
