/*
 * Rect.h
 *
 *  Created on: 25 sie 2016
 *      Author: Uzume
 */

#ifndef RECT_RECT_H_
#define RECT_RECT_H_

#include "stdint.h"

#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

class Rect {
public:
	int16_t m_x;
	int16_t m_y;
	int16_t m_width;
	int16_t m_height;

	Rect();
	Rect(int16_t x, int16_t y, int16_t width, int16_t height);
	virtual ~Rect();

	/*
	 * Gets the x coordinate of the right edge of the Rect.
	 */
	int16_t right(void) const;

	/*
	 * Gets the y coordinate of the bottom edge of the Rect.
	 */
	int16_t bottom(void) const;

	/*
	 * Determines whether specified point lies inside this rectangle.
	 */
	bool intersect(int16_t otherX, int16_t otherY) const;

	/*
	 * Determines whether specified rectangle intersects with this rectangle.
	 */
	bool intersect(const Rect& otherRect) const;

	/*
	 * Determines whether the specified rectangle is completely included in this rectangle.
	 */
	bool includes(const Rect& otherRect) const;

	/*
	 * Gets a rectangle describing the intersecting area between this rectangle and the
     * supplied rectangle.
	 */
	Rect operator &(const Rect& otherRect) const;

	/*
	 * Assigns this Rect to the intersection of the current Rect and the assigned Rect.
     * The assignment will result in a Rect(0, 0, 0, 0) if they do not intersect.
	 */
	void operator &=(const Rect& other);

	/*
	 * Compares equality of two Rect by the dimensions and position of these.
	 */
	bool operator==(const Rect& otherRect) const;

	/*
	 * Query if this object is empty.
	 */
	bool isEmpty(void) const;

	/*
	 * Opposite of the == operator.
	 */
	bool operator !=(const Rect& other) const;

	/*
	 * Calculate the area of the rectangle.
	 */
	uint32_t area(void) const;
private:
	bool isEqual(const Rect& otherRect) const;
};

#endif /* RECT_RECT_H_ */
