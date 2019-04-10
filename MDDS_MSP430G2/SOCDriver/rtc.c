/*
 * rtc.c
 *
 *  Created on: 2019年2月2日
 *      Author: asdf2
 */
#include <includes.h>
#if RTC_EN>0

UTime RTCTime;
BL TimeERROR;
//初始化

void RTCInit()
{
#if RTC_MODE==RTC_Internal
    RTCTime=0;
    BasicTimerAdd(1000000,0,RTCInterrupt);
#else
#error "Other mode is not supported"
#endif
}
//设置时间
//参数：
//  UTime time：时间戳

void RTCTimeSet(UTime time)
{
    RTCTime=time;
    TimeERROR=0;
}
//获取时间
//返回：UTime：时间戳
UTime RTCTimeGet()
{
    assert(TimeERROR);
    return RTCTime;
}
//RTC中断函数
void RTCInterrupt()
{
#if RTC_MODE==RTC_Internal
    RTCTime+=RTC_INTR_TIME_IN_MS;
#endif
}

#endif
