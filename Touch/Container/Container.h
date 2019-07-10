/*
 * Container.h
 *
 *  Created on: 1 wrz 2016
 *      Author: Uzume
 */

#ifndef CONTAINER_CONTAINER_H_
#define CONTAINER_CONTAINER_H_

#include "../Drawable/Drawable.h"

class Container: public Drawable {
public:
	Container();
	virtual ~Container();
	void add(Drawable* child);
	void remove(Drawable* d);
	void insert(Drawable* prev, Drawable* d);
	void removeAll();
	void forEachChild(void (Drawable::*function)());
	void draw(const Rect& invalidatedArea) const;
	void childGeometryChanged(void);
	bool getChildGeometryChanged(void);
	void getLastChild(int16_t x, int16_t y, Drawable** last);
	virtual uint16_t getType() const;
private:
	bool m_childGeometryChanged;
protected:
	Drawable* m_firstChild;
};

#endif /* CONTAINER_CONTAINER_H_ */
