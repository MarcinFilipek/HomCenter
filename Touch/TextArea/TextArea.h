/*
 * TextArea.h
 *
 *  Created on: 30 wrz 2016
 *      Author: Uzume
 */

#ifndef TEXTAREA_TEXTAREA_H_
#define TEXTAREA_TEXTAREA_H_

#include "../Types/Types.h"
#include "../TypedText/TypedText.h"
#include "../Widget/Widget.h"

class TextArea : public Widget{
public:
	TextArea();
	virtual ~TextArea();
	void setColor(colortype c);
	colortype getColor(void);
	void setAlpha(uint8_t alpha);
	uint8_t getAlpha(void);
	virtual void draw(const Rect& invalidatedArea) const;
	void setTypedText(TypedText t);
	TypedText getTypedText(void) const;
	void setLinespace(uint16_t linesspace);
	uint16_t getLinespace(void) const;
	void setIndentation(uint8_t indent);
	uint8_t getIndentation(void);
	virtual int16_t getTextHeight();
	virtual uint16_t getTextWidth() const;
	void resizeToCurrentText(void);
	virtual uint16_t getType() const;
protected:
	TypedText m_typeText;
	colortype m_color;
	uint8_t m_alpha;
	uint8_t m_indentation;
	uint16_t m_linespace;

};

#endif /* TEXTAREA_TEXTAREA_H_ */
