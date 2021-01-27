/*
 * LedEventsLogger.cpp
 *
 *  Created on: 23 nov. 2020
 *      Author: jeann
 */
#include "LedEventsLogger.h"
LedEventsLogger* LedEventsLogger::_pInstance = nullptr;
LedEventsLogger::LedEventsLogger(){
	assert(!_pInstance);
	_pInstance = this;
	_ledController = new LedController();
	for (int i = 0; i < 4; i++){
	_vectLedEventsSm.push_back(new LedEventsSm(_pInstance,i,_ledController));
	}
}
LedEventsLogger::~LedEventsLogger(){

}
void LedEventsLogger::onButtonShortPressed(ButtonIndex buttonIndex){
	//pushEvent(new XFEvent(XFEvent::Event,EventIds::evButtonShortPressedId,this));
	LedEventsSm* ledSM;
	ledSM = _vectLedEventsSm.at(buttonIndex);
	ledSM->pushEvent(new XFEvent(XFEvent::Event,EventIds::evButtonShortPressedId,ledSM));
}
void LedEventsLogger::onButtonLongPressed(ButtonIndex buttonIndex){
	LedEventsSm* ledSM;
	ledSM = _vectLedEventsSm.at(buttonIndex);
	ledSM->pushEvent(new XFEvent(XFEvent::Event,EventIds::evButtonLongPressedId,ledSM));
}

