/*
 * AbstractButton.h
 *
 *  Created on: 21 wrz 2016
 *      Author: Uzume
 */

#ifndef ABSTRACTBUTTON_ABSTRACTBUTTON_H_
#define ABSTRACTBUTTON_ABSTRACTBUTTON_H_

#include "../Widget/Widget.h"
#include "../Callback/Callback.h"

class AbstractButton : public Widget {
public:
	AbstractButton();
	virtual ~AbstractButton();
	virtual void handleClickEvent(const ClickEvent& event);
	bool getPressedState(void);
	void setAction(GenericCallback<const AbstractButton&>& callback);
	virtual uint16_t getType() const;
protected:
	bool m_pressed;
	GenericCallback<const AbstractButton&>* action;
};

#endif /* ABSTRACTBUTTON_ABSTRACTBUTTON_H_ */
