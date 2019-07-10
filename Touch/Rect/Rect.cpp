/*
 * Rect.cpp
 *
 *  Created on: 25 sie 2016
 *      Author: Uzume
 */

#include "Rect.h"

Rect::Rect() {
	m_x = 0;
	m_y = 0;
	m_width = 0;
	m_height = 0;
}

Rect::Rect(int16_t x, int16_t y, int16_t width, int16_t height) {
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
}

Rect::~Rect() {
	// TODO Auto-generated destructor stub
}

int16_t Rect::right() const{
	return m_x + m_width;
}

int16_t Rect::bottom() const {
	return m_y + m_height;
}

bool Rect::intersect(int16_t otherX, int16_t otherY) const{
    return (otherX >= m_x && otherX < right() &&
            otherY >= m_y && otherY < bottom());
}

bool Rect::intersect(const Rect& otherRect) const{
    return !(m_x >= otherRect.right() || right() <= otherRect.m_x ||
             m_y >= otherRect.bottom() || bottom() <= otherRect.m_y);
}

bool Rect::includes(const Rect& otherRect) const {
    return (otherRect.m_x >= m_x &&
    		otherRect.m_y >= m_y &&
			otherRect.right() <= right() &&
			otherRect.bottom() <= bottom());
}

Rect Rect::operator &(const Rect& otherRect) const {
	Rect r = *this;
	r &= otherRect;
	return r;
}

void Rect::operator &=(const Rect& otherRect)
    {
        if (intersect(otherRect))
        {
            int16_t newX = MAX(m_x, otherRect.m_x);
            int16_t newY = MAX(m_y, otherRect.m_y);

            m_width = MIN(right(), otherRect.right()) - newX;
            m_height = MIN(bottom(), otherRect.bottom()) - newY;
            m_x = newX;
            m_y = newY;
        }
        else
        {
            m_x = 0;
            m_y = 0;
            m_width = 0;
            m_height = 0;
        }
    }

bool Rect::operator==(const Rect& otherRect) const {
	return isEqual(otherRect);
}

bool Rect::isEqual(const Rect& otherRect) const {
	return ((m_x == otherRect.m_x) && (m_y == otherRect.m_y) && (m_width == otherRect.m_width)
			&& (m_height == otherRect.m_height));
}

bool Rect::operator !=(const Rect& other) const {
	return !isEqual(other);
}

bool Rect::isEmpty() const
{
    return ((m_width == 0) || (m_height == 0));
}

uint32_t Rect::area() const
{
    return m_width * m_height;
}
