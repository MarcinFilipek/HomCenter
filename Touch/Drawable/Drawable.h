/*
 * Drawable.h
 *
 *  Created on: 1 wrz 2016
 *      Author: Uzume
 */

#ifndef DRAWABLE_DRAWABLE_H_
#define DRAWABLE_DRAWABLE_H_

#include "../Rect/Rect.h"
#include "../ClickEvent/ClickEvent.h"
#include "../DragEvent/DragEvent.h"
#include "../GestureEvent/GestureEvent.h"

class Drawable {
public:
	typedef enum{
		TYPE_DRAWABLE,
		TYPE_WIDGET,
		TYPE_IMAGE,
		TYPE_ABSTRACTBUTTON,
		TYPE_BUTTON,
		TYPE_CONTAINER,
		TYPE_TEXTAREA,
		TYPE_TEXTAREAWITHONEWILDCARD
	} DrawableType;

	Drawable();
	virtual ~Drawable();
	virtual void draw(const Rect& invalidatedarea) const = 0;
	virtual void childGeometryChanged(void);
	Drawable* getNextSibling(void);
	void setNextSibling(Drawable* d);
	virtual void setX(int16_t x);
	virtual int16_t getX(void);
	virtual void setY(int16_t y);
	virtual int16_t getY(void);
	virtual void setXY(int16_t x, int16_t y);
	virtual void setWidth(int16_t width);
	virtual int16_t getWidth(void);
	virtual void setHeight(int16_t height);
	virtual int16_t getHeight(void);
	virtual void setPosition(int16_t x, int16_t y, int16_t width, int16_t height);
	virtual uint16_t getType(void) const;
	void setVisible(bool vis);
	void setTouchable(bool touch);
	bool isVisible(void) const;
	bool isTouchable(void) const;
	void setParent(Drawable* parent);
	Drawable* getParent(void);
	virtual void getLastChild(int16_t x, int16_t y, Drawable** last) = 0;
	virtual void translateRectToAbsolute(Rect& r) const;
	virtual void handleClickEvent(const ClickEvent& event){}
	virtual void handleDragEvent(const DragEvent& event) { }
	virtual void handleGestureEvent(const GestureEvent& event) { }
	virtual void handleTickEvent() { }
	const Rect& getRect(void) const;
	const Rect& getOldRect(void) const;
	virtual void invalidate(void);
	virtual void getVisibleRect(Rect& rect) const;
	Rect getAbsoluteRect() const;
	void moveRelative(int16_t x, int16_t y);
    void moveTo(int16_t x, int16_t y);
protected:
	Drawable* m_nextSibling;
	Drawable* m_parent;
	Rect m_rect;	//The coordinates of this drawable, relative to its parent.
	Rect m_oldRect;	//The coordinates of this drawable, relative to its parent.
	bool m_visible;
	bool m_touchable;
};

#endif /* DRAWABLE_DRAWABLE_H_ */
