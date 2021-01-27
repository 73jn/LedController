/*
 * ButtonStateSm.h
 *
 *  Created on: 3 nov. 2020
 *      Author: jeann
 */


#ifndef BUTTON_BUTTONSTATESM_H_
#define BUTTON_BUTTONSTATESM_H_
#include <xf/behavior.h>
#include <mdw/button/ButtonEventsHandler.h>
class ButtonEventsHandler;
using namespace interface;

class ButtonStateSm : public XFBehavior{
public:
	typedef enum{STATE_INITIAL,
		WAIT_BUTTON_PRESSED,
		BUTTON_PRESSED,
		BUTTON_SHORT_PRESSED,
		BUTTON_LONG_PRESSED} ButtonState;
	typedef uint8_t ButtonIndex;


	ButtonState btnState;
	ButtonState oldState;
	ButtonIndex btnIndex;

	ButtonEventsHandler* _theHandler;


	ButtonStateSm(ButtonIndex index, ButtonEventsHandler* handler);
	virtual ~ButtonStateSm();

	XFEventStatus processEvent() override;		///< Remplementation from XFBehavior

	void doNotifyButtonShortPressed();
	void doNotifyButtonLongPressed();

};

#endif /* BUTTON_BUTTONSTATESM_H_ */
