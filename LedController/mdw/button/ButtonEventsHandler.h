/*
 * ButtonEventsHandler.h
 *
 *  Created on: 3 nov. 2020
 *      Author: jeann
 */

#ifndef BUTTONEVENTSHANDLER_H_
#define BUTTONEVENTSHANDLER_H_
#include <interface/ButtonEventsHandlerSubject.h>
#include "interface/ButtonsControllerCallbackProvider.h"
#include <interface/buttoneventshandlerobserver.h>
#include "ButtonStateSm.h"
#include <xf/behavior.h>
#include <event/events.h>
#include <assert.h>
using namespace interface;
class ButtonStateSm;

class ButtonEventsHandler: public ButtonsControllerCallbackProvider, public ButtonEventsHandlerSubject {
public:
	ButtonEventsHandler();
	virtual ~ButtonEventsHandler();

	void onButtonChanged(ButtonIndex buttonIndex, bool pressed);
	bool subscribe(ButtonEventsHandlerObserver *observer) override;
	void unsubscribe(ButtonEventsHandlerObserver *observer) override;


	void notifyButtonShortPressed(ButtonIndex buttonIndex) override;	///< @brief Notifies observers about a button short pressed.
	void notifyButtonLongPressed(ButtonIndex buttonIndex) override; ///< @brief Notifies observers about a button long pressed.


	//ButtonEventsHandlerObserver* _subscriber;
	std::vector<ButtonStateSm*> _vectBtnStateSM;
	std::vector<ButtonEventsHandlerObserver*> _vectSubscribers;
    static ButtonEventsHandler* _pInstance;

};

#endif /* BUTTONEVENTSHANDLER_H_ */
