/*
 * ButtonEventsLogger.cpp
 *
 *  Created on: 29 oct. 2020
 *      Author: jeann
 */
#include "config/trace-config.h"
#include "trace/trace.h"
#include <app/ButtonEventsLogger.h>

ButtonEventsLogger::ButtonEventsLogger() {
	// TODO Auto-generated constructor stub
	Trace::out("Hello World\r\n");

}

ButtonEventsLogger::~ButtonEventsLogger() {
	// TODO Auto-generated destructor stub
}

void ButtonEventsLogger::onButtonShortPressed(ButtonIndex buttonIndex){
	Trace::out("Short press : %d\r\n", buttonIndex);
}
void ButtonEventsLogger::onButtonLongPressed(ButtonIndex buttonIndex){
	Trace::out("Long press : %d\r\n", buttonIndex);
}

