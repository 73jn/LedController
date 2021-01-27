/*
 * ButtonStateSm.cpp
 *
 *  Created on: 3 nov. 2020
 *      Author: jeann
 */

#include <button/ButtonStateSm.h>
#include <trace/trace.h>
#include <config/debug-config.h>

ButtonStateSm::ButtonStateSm(ButtonIndex index, ButtonEventsHandler* handler) {
	// TODO Auto-generated constructor stub
	this->btnIndex = index;
	btnState = STATE_INITIAL;

	_theHandler = handler;

	startBehavior();
}

ButtonStateSm::~ButtonStateSm() {
	// TODO Auto-generated destructor stub
}

void ButtonStateSm::doNotifyButtonShortPressed(){
	_theHandler->notifyButtonShortPressed(btnIndex);

}
void ButtonStateSm::doNotifyButtonLongPressed(){
	_theHandler->notifyButtonLongPressed(btnIndex);
}

XFEventStatus ButtonStateSm::processEvent() {
#ifdef TRACEDEBUG
	Trace::out("Went in ButtonStateSm%d::processEvent\r\n", this->btnIndex);
#endif
	eEventStatus eventStatus = XFEventStatus::Unknown;

	oldState = btnState;
	switch (btnState){
		case STATE_INITIAL:
			if (getCurrentEvent()->getEventType() == XFEvent::Initial)
			{
				btnState = WAIT_BUTTON_PRESSED;
				eventStatus = XFEventStatus::Consumed;
			}
			break;
		case WAIT_BUTTON_PRESSED:
			if (getCurrentEvent()->getEventType() == XFEvent::Event
					&& getCurrentEvent()->getId() == EventIds::evButtonPressedId){
				scheduleTimeout(EventIds::evButtonLongPressedId, 1000);
				btnState = BUTTON_PRESSED;
				eventStatus = XFEventStatus::Consumed;
			}
			break;
		case BUTTON_PRESSED:
			//SHORT PRESS
			if(getCurrentEvent()->getEventType() == XFEvent::Event
					&& getCurrentEvent()->getId() == EventIds::evButtonReleasedId){ //On a release le button < timeLongPress
#ifdef TRACEDEBUG
				Trace::out("SHORT PRESS\r\n");
#endif
				btnState = BUTTON_SHORT_PRESSED;
				unscheduleTimeout(EventIds::evButtonLongPressedId); //On désactive le schedule long press
				eventStatus = XFEventStatus::Consumed;
			}
			//LONG PRESS
			if (getCurrentEvent()->getEventType() == XFEvent::Timeout
					&& getCurrentEvent()->getId() == EventIds::evButtonLongPressedId){
#ifdef TRACEDEBUG
				Trace::out("LONG PRESS\r\n");
#endif
				btnState = BUTTON_LONG_PRESSED;
				eventStatus = XFEventStatus::Consumed;
			}
			break;
		case BUTTON_SHORT_PRESSED:
			if(getCurrentEvent()->getEventType() == XFEvent::NullTransition)
			{
				btnState = WAIT_BUTTON_PRESSED;
				break;
			}
		case BUTTON_LONG_PRESSED:
			if(getCurrentEvent()->getEventType() == XFEvent::NullTransition)
			{
				btnState = WAIT_BUTTON_PRESSED;
				break;
			}
		default:
			break;
	}
	if (oldState!=btnState){
		switch(btnState)
		{
			case BUTTON_SHORT_PRESSED:
#ifdef TRACEDEBUG
				Trace::out("SEND SHORT PRESS\r\n");
#endif
				doNotifyButtonShortPressed();
				GEN(XFNullTransition);
				break;
			case BUTTON_LONG_PRESSED:
#ifdef TRACEDEBUG
				Trace::out("SEND LONG PRESS\r\n");
#endif
				doNotifyButtonLongPressed();
				GEN(XFNullTransition);
				break;
			default:
				break;
		}
	}
	return eventStatus;
}
