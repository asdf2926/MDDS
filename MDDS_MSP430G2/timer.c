/*
 * timer.c
 *
 *  Created on: 2019Äê1ÔÂ24ÈÕ
 *      Author: asdf2
 */
#include <includes.h>
#if TIMER_0A_EN>0
#define _TA_NAME TA0
#define _TA_FULL_NAME Timer0A
#define _TA_INT_NAME TIMER0_A
#define _TA_MACRO_NAME TIMER_0A
#include "_timer_make.h"
#undef _TA_NAME
#undef _TA_FULL_NAME
#undef _TA_INT_NAME
#undef _TA_MACRO_NAME
#endif

#if TIMER_1A_EN>0
#define _TA_NAME TA1
#define _TA_FULL_NAME Timer1A
#define _TA_INT_NAME TIMER1_A
#define _TA_MACRO_NAME TIMER_1A
#include "_timer_make.h"
#endif

