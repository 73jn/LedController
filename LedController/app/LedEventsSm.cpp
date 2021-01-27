/*
 * LedEventsLogger.cpp
 *
 *  Created on: 23 nov. 2020
 *      Author: jeann
 */
#include "LedEventsLogger.h"
LedEventsSm::LedEventsSm(LedEventsLogger* handler, uint8_t index, LedController* LedController){
	state = STATE_INITIAL;
	_theLedController = LedController;

	startBehavior();
	_theHandler = handler;
	this->index = index;
}
LedEventsSm::~LedEventsSm(){

}
XFEventStatus LedEventsSm::processEvent(){
			///< Remplementation from XFBehavior

		eEventStatus eventStatus = XFEventStatus::Unknown;

		oldState = state;
		switch (state){
			case STATE_INITIAL:
				if (getCurrentEvent()->getEventType() == XFEvent::Initial)
				{
					state = WAIT_PRESSED_BUTTON;
					eventStatus = XFEventStatus::Consumed;
				}
				break;
			case WAIT_PRESSED_BUTTON:
				if (getCurrentEvent()->getEventType() == XFEvent::Event
						&& getCurrentEvent()->getId() == EventIds::evButtonShortPressedId){
					scheduleTimeout(EventIds::tmOnLedId, 500);
					state = SET_LED_1;
					eventStatus = XFEventStatus::Consumed;
				}
				if (getCurrentEvent()->getEventType() == XFEvent::Event
						&& getCurrentEvent()->getId() == EventIds::evButtonLongPressedId){
					scheduleTimeout(EventIds::tmOnLedId, 500);
					state = SET_LED_2;
					eventStatus = XFEventStatus::Consumed;
				}
				break;
			case SET_LED_1:
				//SHORT PRESS
				if(getCurrentEvent()->getEventType() == XFEvent::Timeout
						&& getCurrentEvent()->getId() == EventIds::tmOnLedId){ //On a release le button < timeLongPress
					state = OFF_LED_1;
					eventStatus = XFEventStatus::Consumed;
				}
				break;
			case OFF_LED_1:
				if(getCurrentEvent()->getEventType() == XFEvent::NullTransition)
				{
					state = WAIT_PRESSED_BUTTON;
					break;
				}
			case SET_LED_2:
				if(getCurrentEvent()->getEventType() == XFEvent::Timeout
						&& getCurrentEvent()->getId() == EventIds::tmOnLedId){ //On a release le button < timeLongPress
					scheduleTimeout(EventIds::tmOffLedId, 200);
					state = OFF_LED_2;
					eventStatus = XFEventStatus::Consumed;
				}
				break;
			case OFF_LED_2:
				if(getCurrentEvent()->getEventType() == XFEvent::Timeout
						&& getCurrentEvent()->getId() == EventIds::tmOffLedId){ //On a release le button < timeLongPress
					scheduleTimeout(EventIds::tmOnLedId, 500);
					state = SET_LED_1;
					eventStatus = XFEventStatus::Consumed;
				}
				break;
			default:
				break;
		}
		if (oldState!=state){
			switch(state)
			{
				case OFF_LED_1:
					_theLedController->setLed(index, 0);
					GEN(XFNullTransition);
					break;
				case SET_LED_1:
				case SET_LED_2:
					_theLedController->setLed(index, 1);
					break;
				case OFF_LED_2:
					_theLedController->setLed(index, 0);
					break;
				default:
					break;
			}
		}
		return eventStatus;
}


