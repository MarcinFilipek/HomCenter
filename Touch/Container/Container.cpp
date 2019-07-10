/*
 * Container.cpp
 *
 *  Created on: 1 wrz 2016
 *      Author: Uzume
 */

#include "Container.h"
#include "stddef.h"

Container::Container() {
	m_childGeometryChanged = true;
	m_firstChild = NULL;
}

Container::~Container() {

}

void Container::add(Drawable* child) {
	child->setParent(this);
	if (m_firstChild == NULL) {
		m_firstChild = child;
	} else {
		Drawable* temp = m_firstChild;
		while (temp->getNextSibling() != NULL) {
			temp = temp->getNextSibling();
		}
		temp->setNextSibling(child);
	}
}

void Container::remove(Drawable* d){
	if(m_firstChild != NULL){
		Drawable* prevChild = NULL;
		Drawable* tempChild = m_firstChild;
		do{
			if(d == tempChild){
				if(tempChild == m_firstChild){
					m_firstChild->setParent(0);
					m_firstChild = m_firstChild->getNextSibling();
					break;
				}
				prevChild->setNextSibling(tempChild->getNextSibling());
				tempChild->setParent(0);
			}
			prevChild = tempChild;
			tempChild = tempChild->getNextSibling();
		}while(tempChild != NULL);
	}
}

void Container::insert(Drawable* prev, Drawable* d){
	if(prev == NULL){
		Drawable* tempChild = m_firstChild;
		m_firstChild = d;
		m_firstChild->setNextSibling(tempChild);
		m_firstChild->setParent(this);
	} else {
		if(m_firstChild != NULL){
			Drawable* tempChild = m_firstChild;
			do{
				if(tempChild == prev){
					Drawable* tempNextChild = tempChild->getNextSibling();
					tempChild->setNextSibling(d);
					d->setNextSibling(tempNextChild);
					d->setParent(this);
					break;
				}
				tempChild = tempChild->getNextSibling();
			}while(tempChild != NULL);
		}
	}
}

void Container::removeAll(){

}

void Container::forEachChild(void (Drawable::*function)(void)) {
	if (m_firstChild != NULL) {
		Drawable* tempChild = m_firstChild;
		do {
			if(tempChild->isVisible()){
				(tempChild->*function)();
			}
			tempChild = tempChild->getNextSibling();
		} while (tempChild != NULL);
	}
}

void Container::draw(const Rect& invalidatedArea) const{
	if(m_firstChild != NULL){
		Drawable* tempChild = m_firstChild;
		do{
			if(tempChild->isVisible()){
				tempChild->draw(invalidatedArea);
			}
			tempChild = tempChild->getNextSibling();
		} while(tempChild != NULL);
	}
}
void Container::childGeometryChanged(void){
	m_childGeometryChanged = true;
}

bool Container::getChildGeometryChanged(void){
	return m_childGeometryChanged;
}

void Container::getLastChild(int16_t x, int16_t y, Drawable** last){
	uint16_t type = 0;
	if(m_firstChild != NULL){
		if(isVisible() && isTouchable()){
			*last = this;
		}
		Drawable* tempChild = m_firstChild;
		do{
			tempChild->getType();
			if(tempChild->getAbsoluteRect().intersect(x, y)){
				tempChild->getLastChild(x, y, last);
			}
			tempChild = tempChild->getNextSibling();
		} while (tempChild != NULL);
	}
}

uint16_t Container::getType() const{
	return (uint16_t)TYPE_CONTAINER;
}
