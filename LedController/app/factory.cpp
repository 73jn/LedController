#include "factory.h"

namespace app
{
ButtonEventsLogger* app::Factory::_theButtonEventsLogger;
ButtonEventsHandler* app::Factory::_theButtonEventsHandler;
ButtonController* app::Factory::_theButtonController;
LedEventsLogger* app::Factory::_theLedEventsLogger;
//LedController*app::Factory::_theLedController;
// TODO: Implement app::Factory class
	void app::Factory::initialize(){

	}

	void app::Factory::build(){
		app::Factory::_theButtonEventsLogger = new ButtonEventsLogger();
		app::Factory::_theButtonController = new ButtonController();
		app::Factory::_theButtonEventsHandler = new ButtonEventsHandler();
	    app::Factory::_theLedEventsLogger = new LedEventsLogger();
	    //app::Factory::_theLedController = new LedController();
		_theButtonController->registerCallback(_theButtonEventsHandler,
				(ButtonsControllerCallbackProvider::CallbackMethod)&ButtonEventsHandler::onButtonChanged);
		_theButtonEventsHandler->subscribe(_theButtonEventsLogger);
		_theButtonEventsHandler->subscribe(_theLedEventsLogger);
	}
} /* namespace app */

void Factory_initialize()
{
    app::Factory::initialize();
}

void Factory_build()
{
    app::Factory::build();
}
