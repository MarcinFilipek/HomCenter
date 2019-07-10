/*
 * ListLayout.cpp
 *
 *  Created on: 25 sie 2017
 *      Author: Uzume
 */

#include "ListLayout.h"

void ListLayout::add(Drawable* child){
	child->setParent(this);
	if (!m_firstChild) {
		m_firstChild = child;
	} else {
		Drawable* temp = m_firstChild;
		while (temp->getNextSibling()) {
			temp = temp->getNextSibling();
		}
		temp->setNextSibling(child);
	}
	child->setX(xOffset);
	xOffset += child->getWidth();
	setWidth(getWidth() + child->getWidth());
	setHeight(child->getHeight());
}

void ListLayout::removeAll(){
	xOffset = 0;
	setWidth(0);
	setHeight(0);
	if (m_firstChild) {
		Drawable* actualChild = m_firstChild;
		Drawable* nextChild = m_firstChild;
		do {
			nextChild = actualChild->getNextSibling();
			actualChild->setNextSibling(0);
			actualChild = nextChild;
		} while (nextChild);
		m_firstChild = 0;
	}
}
