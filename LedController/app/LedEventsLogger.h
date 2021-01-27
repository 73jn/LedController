/*
 * LedEventsLogger.h
 *
 *  Created on: 23 nov. 2020
 *      Author: jeann
 */
#ifdef __cplusplus
#ifndef LEDEVENTSLOGGER_H_
#define LEDEVENTSLOGGER_H_

#include <interface/buttoneventshandlerobserver.h>
#include <xf/behavior.h>
#include <platform/f7-disco-gcc/board/ledcontroller.h>
#include "LedEventsSm.h"
#include <assert.h>
using namespace interface;

class LedEventsLogger : public ButtonEventsHandlerObserver
{
public :
	LedEventsLogger();
	~LedEventsLogger();
protected:
	std::vector<LedEventsSm*> _vectLedEventsSm;
	LedController* _ledController;
	void onButtonShortPressed(ButtonIndex buttonIndex) override;
	void onButtonLongPressed(ButtonIndex buttonIndex) override;
    static LedEventsLogger* _pInstance;
};

#endif /* LEDEVENTSLOGGER_H_ */
#endif
