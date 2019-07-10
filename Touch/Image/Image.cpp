/*
 * Image.cpp
 *
 *  Created on: 2 wrz 2016
 *      Author: Uzume
 */

#include "Image.h"
#include "../Lcd/Lcd.h"

Image::Image(const Bitmap& bmp) : m_alpha(0xFF) {
}

Image::~Image() {
}

void Image::draw(const Rect& invalidatedArea) const
{
	Lcd lcd;
    Rect meAbs = getAbsoluteRect();
    Rect dirtyBitmapArea = meAbs & invalidatedArea;
    getVisibleRect(dirtyBitmapArea);
    lcd.drawPartialBitmap(m_bitmap, meAbs.m_x, meAbs.m_y, dirtyBitmapArea);
}

void Image::setBitmap(const Bitmap& bmp){
	m_bitmap = bmp;
	setWidth(bmp.getWidth());
	setHeight(bmp.getHeight());
}

void Image::setAlpha(uint8_t alpha){
	m_alpha = alpha;
}

uint8_t Image::getAlpha(void){
	return m_alpha;
}

BitmapId Image::getBitmap(){
	return m_bitmap.getId();
}

uint16_t Image::getType() const{
	return (uint16_t)TYPE_IMAGE;
}
