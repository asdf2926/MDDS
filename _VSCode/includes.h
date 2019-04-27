#ifndef _INCLUDES_H

#define _INCLUDES_H
#define PLATFORM_VSCODE
//#include <stdio.h>
#include "sys.h"
#include "conf.h"
#include "../conf_template/conf_driver.h"
#include "../conf_template/conf_middleware.h"
#include "../conf_template/conf_Math.h"
#include "../conf_template/conf_app.h"
#include "../conf_template/conf_UI.h"
#include "../Driver/includes_driver.h"
#include "../Middleware/includes_Middleware.h"
#include "../Math/includes_Math.h"
#include "../Application/includes_app.h"
#include "../UI/includes_UI.h"
typedef INT32U size_t;
Time RTCTimeRGet();
void RTCTimeRSet(Time);
int snprintf(char *str, size_t size, const char *format, ...);
#endif