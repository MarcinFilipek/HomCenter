/*
 * UIEventListener.h
 *
 *  Created on: 15 maj 2017
 *      Author: Uzume
 */

#ifndef UIEVENTLISTENER_UIEVENTLISTENER_H_
#define UIEVENTLISTENER_UIEVENTLISTENER_H_

class ClickEvent;
class DragEvent;
class GestureEvent;

class UIEventListener {
public:
	UIEventListener();
	virtual ~UIEventListener();

	virtual void handleClickEvent(const ClickEvent& event) {
	}

	virtual void handleDragEvent(const DragEvent& event) {
	}

	virtual void handleGestureEvent(const GestureEvent& event) {
	}

	virtual void handleTickEvent() {
	}
	virtual void handlePendingScreenTransition() {
	}
};

#endif /* UIEVENTLISTENER_UIEVENTLISTENER_H_ */
