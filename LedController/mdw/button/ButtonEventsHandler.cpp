/*
 * ButtonEventsHandler.cpp
 *
 *  Created on: 3 nov. 2020
 *      Author: jeann
 */
#include "ButtonEventsHandler.h"
#include <mdw/button/ButtonEventsHandler.h>
#include <trace/trace.h>
#include <config/debug-config.h>
#include <config/gpio-config.h>
ButtonEventsHandler* ButtonEventsHandler::_pInstance = nullptr;

ButtonEventsHandler::ButtonEventsHandler() {
	assert(!_pInstance);
	_pInstance = this;
	// TODO Auto-generated constructor stub
	for (int i = 0; i < 4; i++){
	_vectBtnStateSM.push_back(new ButtonStateSm(i,_pInstance));
	}



}

ButtonEventsHandler::~ButtonEventsHandler() {
	// TODO Auto-generated destructor stub
}
void ButtonEventsHandler::onButtonChanged(ButtonIndex buttonIndex, bool pressed) {
#ifdef TRACEDEBUG
	Trace::out("Went in ButtonEventsHandler::onButtonChanged : ");
#endif
	ButtonStateSm* btnSM;
	btnSM = _vectBtnStateSM.at(buttonIndex);
#ifdef PULLUP
	if (!pressed){
#endif
#ifdef PULLDOWN
		if(pressed){
#endif

		//Push pressed event in SM n°index button
#ifdef TRACEDEBUG
		Trace::out("PRESSED\r\n");
#endif
		btnSM->pushEvent(new XFEvent(XFEvent::Event,EventIds::evButtonPressedId,btnSM));
	} else {
		//Push unpressed in SM n°index button
#ifdef TRACEDEBUG
		Trace::out("UNPRESSED\r\n");
#endif
		btnSM->pushEvent(new XFEvent(XFEvent::Event,EventIds::evButtonReleasedId,btnSM));
	}
}
bool ButtonEventsHandler::subscribe(ButtonEventsHandlerObserver *observer) {
	_vectSubscribers.push_back(observer);
	return true;
}
void ButtonEventsHandler::unsubscribe(ButtonEventsHandlerObserver *observer) {
	  for (std::vector<ButtonEventsHandlerObserver*>::iterator it = _vectSubscribers.begin() ; it <_vectSubscribers.end(); it++){
	    if (*it == observer){
	    	_vectSubscribers.erase(it);
	    }
	  }
}

void ButtonEventsHandler::notifyButtonShortPressed(ButtonIndex buttonIndex){
	  for (std::vector<ButtonEventsHandlerObserver*>::iterator it = _vectSubscribers.begin() ; it < _vectSubscribers.end(); it++)
	    	(*it)->onButtonShortPressed(buttonIndex);
}
void ButtonEventsHandler::notifyButtonLongPressed(ButtonIndex buttonIndex){
	  for (std::vector<ButtonEventsHandlerObserver*>::iterator it = _vectSubscribers.begin() ; it < _vectSubscribers.end(); it++)
	    	(*it)->onButtonLongPressed(buttonIndex);
}
