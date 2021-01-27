/*
 * ButtonController.h
 *
 *  Created on: 3 nov. 2020
 *      Author: jeann
 */

#ifndef BUTTONCONTROLLER_H_
#define BUTTONCONTROLLER_H_
#include "interface/buttonscontrollercallbackcaller.h"
#include "../../interface/buttonirq.h"
#include <xf/behavior.h>
#include "mcu/mcu.h"
#include "event/evbuttonirq.h"
#include "event/events.h"
#include <assert.h>
#include <Inc/main.h>

using namespace interface;
class ButtonController : public ButtonIrq, public ButtonsControllerCallbackCaller, public XFBehavior {
public :
	ButtonController();
	virtual ~ButtonController();
	static ButtonController* getInstance();
    bool registerCallback(ButtonsControllerCallbackProvider * callbackProvider,
                                  ButtonsControllerCallbackProvider::CallbackMethod callbackMethod) override;
	void onIrq() override;	///< @brief Called by the ISR.
protected :
	typedef enum {STATE_INITIAL,STATE_CHECK_BUTTONS,STATE_DEBOUNCE} ButtonControllerState;
	static ButtonController* _pInstance;


	void doCheckButtons();
	XFEventStatus processEvent() override;		///< Remplementation from XFBehavior
	int getState();
private:
	ButtonsControllerCallbackProvider* _theCallBackProvider;
	ButtonsControllerCallbackProvider::CallbackMethod _theCallBackMethod;
	ButtonControllerState state;
	bool btnState[4];
	bool oldBtnState[4];

};

#endif /* BUTTONCONTROLLER_H_ */
