/*
 * TextAreaWithWildcard.h
 *
 *  Created on: 14 lis 2016
 *      Author: Uzume
 */

#ifndef TEXTAREAWITHWILDCARD_TEXTAREAWITHWILDCARD_H_
#define TEXTAREAWITHWILDCARD_TEXTAREAWITHWILDCARD_H_

#include "../TextArea/TextArea.h"
class TextAreaWildcardBase : public TextArea{
public:
	TextAreaWildcardBase() :
			TextArea() {
	}
	int16_t calculateTextHeight(const Unicode::UnicodeChar* format, ...) const;
};
class TextAreaWithOneWildcard : public TextAreaWildcardBase {
public:
	TextAreaWithOneWildcard() :
			TextAreaWildcardBase(), m_wildcard(0) {

	}
	virtual ~TextAreaWithOneWildcard(){}
	virtual int16_t getTextHeight();
	virtual void draw(const Rect& invalidatedArea) const;
	virtual uint16_t getTextWidth();
	void setWildcard(const Unicode::UnicodeChar* value);
	const Unicode::UnicodeChar* getWildcard() const;
	virtual uint16_t getType() const;
protected:
	const Unicode::UnicodeChar* m_wildcard;
};

#endif /* TEXTAREAWITHWILDCARD_TEXTAREAWITHWILDCARD_H_ */
