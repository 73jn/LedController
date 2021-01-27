/*
 * ButtonController.cpp
 *
 *  Created on: 3 nov. 2020
 *      Author: jeann
 */
#include "board/ButtonController.h"
#include <trace/trace.h>
#include <config/debug-config.h>
ButtonController* ButtonController::_pInstance = nullptr;
ButtonController::ButtonController(){
	// TODO Auto-generated constructor stub
	assert(!_pInstance);
	_pInstance = this;

	_theCallBackProvider = nullptr;
	_theCallBackMethod = nullptr;

	for (int i = 0; i<4; i++){
			oldBtnState[i] = true;
			btnState[i] = true;
		}

	state = STATE_INITIAL;
	startBehavior();
}

ButtonController::~ButtonController() {
	// TODO Auto-generated destructor stub
}

void ButtonController::onIrq(){
	static evButtonIrq e = evButtonIrq();
	pushEvent(&e);


}
bool ButtonController::registerCallback(ButtonsControllerCallbackProvider * callbackProvider,
                              ButtonsControllerCallbackProvider::CallbackMethod callbackMethod){
	_theCallBackProvider = callbackProvider;
	_theCallBackMethod = callbackMethod;
	return true;
}
int ButtonController::getState(){
	return state;
}

XFEventStatus ButtonController::processEvent() {
#ifdef TRACEDEBUG
	Trace::out("Went in ButtonController::processEvent\r\n");
#endif
	eEventStatus eventStatus = XFEventStatus::Unknown;
	ButtonControllerState oldState = state;

	switch(state){
	case STATE_INITIAL:
		if (getCurrentEvent()->getEventType() == XFEvent::Initial)
		{
			state = STATE_CHECK_BUTTONS;
			eventStatus = XFEventStatus::Consumed;
		}
		break;
	case STATE_CHECK_BUTTONS:
		if (getCurrentEvent()->getEventType() == XFEvent::Event &&
				getCurrentEvent()->getId() == EventIds::evButtonIrqId)
		{
			scheduleTimeout(EventIds::tmDebounceId, 100);
			state = STATE_DEBOUNCE;
			eventStatus = XFEventStatus::Consumed;
		}
		break;
	case STATE_DEBOUNCE:
		if (getCurrentEvent()->getEventType() == XFEvent::Timeout &&
				getCurrentEvent()->getId() == EventIds::tmDebounceId)
		{
			state = STATE_CHECK_BUTTONS;
			eventStatus = XFEventStatus::Consumed;
		}
		break;
	default:
		break;
	}
		if(state!=oldState)
		{
			switch(state)
			{
				case STATE_CHECK_BUTTONS:
					doCheckButtons();
					break;
				default:
					break;

			}
		}


		return eventStatus;
	}
void ButtonController::doCheckButtons(){
	btnState[0] = HAL_GPIO_ReadPin(BUTTON0_GPIO_Port, BUTTON0_Pin);
//	btnState[1] = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
//	btnState[2] = HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
//	btnState[3] = HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin);
#ifdef TRACEDEBUG
	Trace::out("Went in ButtonController::doCheckButton\r\n");
	Trace::out("BTN0 : %d, BTN1 : %d, BTN2 : %d, BTN3 : %d\r\n",
			btnState[0], btnState[1], btnState[2] ,btnState[3]);
	Trace::out("OLDBTN0 : %d, OLDBTN1 : %d, OLDBTN2 : %d, OLDBTN3 : %d\r\n",
			oldBtnState[0], oldBtnState[1], oldBtnState[2] ,oldBtnState[3]);
#endif
	for (int i = 0; i<4; i++){
		if (btnState[i] != oldBtnState[i]){
			oldBtnState[i] = btnState[i];
			//NEEED TO SEND TO THE UPPER CLASSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS!!!!!!!!!!!!!!!!!!!!!!!!!
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			(_theCallBackProvider->*_theCallBackMethod)(i, btnState[i]);
		}
	}


}
ButtonController* ButtonController::getInstance(){
	return _pInstance;
}


