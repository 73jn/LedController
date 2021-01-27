/*
 * ButtonEventsLogger.h
 *
 *  Created on: 29 oct. 2020
 *      Author: jeann
 */

#ifndef BUTTONEVENTSLOGGER_H_
#define BUTTONEVENTSLOGGER_H_
#include <interface/buttoneventshandlerobserver.h>
#include <xf/behavior.h>
using namespace interface;

class ButtonEventsLogger : public ButtonEventsHandlerObserver
{
public:
	ButtonEventsLogger();
	virtual ~ButtonEventsLogger();

protected:
	void onButtonShortPressed(ButtonIndex buttonIndex) override;
	void onButtonLongPressed(ButtonIndex buttonIndex) override;
};

#endif /* BUTTONEVENTSLOGGER_H_ */
