/*
 * DotIndicator.cpp
 *
 *  Created on: 25 sie 2017
 *      Author: Uzume
 */

#include "DotIndicator.h"

DotIndicator::DotIndicator() :
		numberOfDots(0), currentDot(0) {
	unselectedDots.setXY(0, 0);
	dotHighlighted.setXY(0, 0);

	add(&unselectedDots);
	add(&dotHighlighted);
}

DotIndicator::~DotIndicator() {
}

void DotIndicator::setnumberOfDots(uint8_t num){
	numberOfDots = num;
	unselectedDots.removeAll();
	for(uint8_t i = 0; i < numberOfDots; i++){
		unselectedDots.add(&dotNormal[i]);
	}

	setWidth(unselectedDots.getWidth());
	setHeight(unselectedDots.getHeight());
	setHighlightPosition(currentDot = 0);

}

void DotIndicator::setBitmaps(const Bitmap& normalDot, const Bitmap& highlightedDot){
	dotHighlighted.setBitmap(highlightedDot);
	for(uint8_t i = 0; i < MAX_SIZE - 1; i++){
		dotNormal[i].setBitmap(normalDot);
	}
	if(numberOfDots > 0){
		setnumberOfDots(numberOfDots);
	}
}

void DotIndicator::goRight(){
	setHighlightPosition(currentDot = (currentDot + 1) % numberOfDots);
}

void DotIndicator::goLeft(){
	setHighlightPosition(currentDot = (currentDot + numberOfDots - 1) % numberOfDots);
}

void DotIndicator::setHighlightPosition(uint8_t index){
	currentDot = index;
	if(index < numberOfDots){
		dotHighlighted.setX(index * dotNormal[0].getWidth());
	}
	invalidate();
}
