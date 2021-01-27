/*
 * LedEventsLogger.h
 *
 *  Created on: 23 nov. 2020
 *      Author: jeann
 */
#ifdef __cplusplus
#ifndef LEDEVENTSSM_H_
#define LEDEVENTSSM_H_

#include <interface/buttoneventshandlerobserver.h>
#include <xf/behavior.h>
#include <platform/f7-disco-gcc/board/ledcontroller.h>
#include "LedEventsLogger.h"

using namespace interface;
class LedEventsLogger;
class LedEventsSm : public XFBehavior
{
public :
	LedEventsSm(LedEventsLogger *handler, uint8_t index, LedController* LedController);
	~LedEventsSm();

	uint8_t index=0;
	XFEventStatus processEvent() override;		///< Remplementation from XFBehavior
protected:
	LedEventsLogger* _theHandler;
	LedController* _theLedController;
	typedef enum{STATE_INITIAL,
		WAIT_PRESSED_BUTTON,
		SET_LED_1,
		OFF_LED_1,
		SET_LED_2,
		OFF_LED_2} LedState;

		LedState state;
		LedState oldState;
};

#endif /* LEDEVENTSLOGGER_H_ */
#endif
