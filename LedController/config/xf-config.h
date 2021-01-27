#ifndef APP_XF_CONFIG_H
#define APP_XF_CONFIG_H

#define PORT_IDF_STM32CUBE                                              1

#define USE_XF_DEFAULT_IMPLEMENTATION                                   1
#define USE_XF_DISPATCHER_DEFAULT_IMPLEMENTATION                        1
#define USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION                    1
#define USE_XF_RESOURCE_FACTORY_DEFAULT_IMPLEMENTATION                  1
#define USE_XF_MUTEX_DEFAULT_IDF_IMPLEMENTATION                         1
#define USE_XF_EVENT_QUEUE_DEFAULT_IDF_IMPLEMENTATION                   1
#define USE_XF_PORT_IDF_STM32CUBE_PORT_FUNCTIONS_IMPLEMENTATION         1

#include "default-idf/eventqueue-default.h"
#ifdef __cplusplus
    using XFEventQueue = XFEventQueueDefault;
#endif // __cplusplus

#endif // APP_XF_CONFIG_H
