/*
 * Application.h
 *
 *  Created on: 31 sie 2016
 *      Author: Uzume
 */

#ifndef APPLICATION_APPLICATION_H_
#define APPLICATION_APPLICATION_H_

#include "../Screen/Screen.h"
#include "../UIEventListener/UIEventListener.h"

class Application : public UIEventListener{
public:
	virtual ~Application();
	static Application* getInstance();
	void initialize(void);
	void switchScreen(Screen* screen);
	Screen* getCurrentScreen(void);
	void handleClickEvent(const ClickEvent& event);
	void handleDragEvent(const DragEvent& event);
	void handleGestureEvent(const GestureEvent& event);
	virtual void handlePendingScreenTransition(void);
	virtual void handleTickEvent();
	void draw(void);
	void draw(Rect& rect);
protected:
	Application();
	static Screen* currentScreen;
	static Application* m_instance;
};

#endif /* APPLICATION_APPLICATION_H_ */
