

//
// What is seen only by the C++ compiler
//
#ifdef __cplusplus

#ifndef FACTORY_H
#define FACTORY_H
#include "trace/trace.h"
#include "ButtonEventsLogger.h"
#include "platform/f7-disco-gcc/board/ButtonController.h"
#include "mdw/button/ButtonEventsHandler.h"
#include "LedEventsLogger.h"
#include <platform/f7-disco-gcc/board/ledcontroller.h>
// TODO: Add C++ specific includes here

namespace app
{

class Factory
{
public:
    Factory();
    static void initialize();           ///< Initializes the factory
    static void build();                ///< Creates components and initializes relations
    static ButtonEventsLogger *_theButtonEventsLogger;
    static ButtonController* _theButtonController;
    static ButtonEventsHandler* _theButtonEventsHandler;
    static LedEventsLogger* _theLedEventsLogger;
    //static LedController* _theLedController;
protected:
    // TODO: Add static attributes here
};

} /* namespace app */
#endif // __cplusplus

//
// What is seen by the C and C++ compiler
//
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void Factory_initialize();
void Factory_build();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // FACTORY_H
