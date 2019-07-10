/*
 * Application.cpp
 *
 *  Created on: 31 sie 2016
 *      Author: Uzume
 */

#include "Application.h"
#include "../Touch.h"
#include "cmsis_os.h"
#include "stddef.h"

Application* Application::m_instance;
Screen* Application::currentScreen;

Application::Application() {
	currentScreen = NULL;
}

Application::~Application() {
	// TODO Auto-generated destructor stub
}

void Application::initialize(void){
}

Application* Application::getInstance(){
	return m_instance;
}

void Application::switchScreen(Screen* screen) {
	currentScreen = screen;
}

Screen* Application::getCurrentScreen(void){
	return currentScreen;
}

void Application::draw(){
	Rect r = Rect(0, 0, 480, 272);
	osSignalSet(Touch::LCD_ThreadId, Touch::SWITCH_BUFFOR);
	currentScreen->draw(r);
	osSemaphoreWait(Touch::osSemaphoreDmaStopWork, osWaitForever);
	if(Touch::USE_VSYNC){
		osSemaphoreWait(Touch::osSemaphoreVsync, osWaitForever);
	}
	osSignalSet(Touch::LCD_ThreadId, Touch::SHOW_RENDER);
	osSemaphoreRelease(Touch::osSemaphoreDmaStopWork);
}

void Application::draw(Rect& rect){
	currentScreen->draw(rect);
}

void Application::handleClickEvent(const ClickEvent& event){
	if(currentScreen){
		currentScreen->handleClickEvent(event);
	}
}

void Application::handleDragEvent(const DragEvent& event){
	if(currentScreen){
		currentScreen->handleDragEvent(event);
	}
}

void Application::handleGestureEvent(const GestureEvent& event){
	if(currentScreen){
		currentScreen->handleGestureEvent(event);
	}
}
void Application::handlePendingScreenTransition(void){

}

void Application::handleTickEvent(){
	if(currentScreen){
		currentScreen->handleTickEvent();
	}
}
