/*
 * rtc.h
 *
 *  Created on: 2019年2月2日
 *      Author: asdf2
 */

#ifndef SOCDRIVER_RTC_H_
#define SOCDRIVER_RTC_H_

#if RTC_EN>0
#define RTC_Internal 0
#define RTC_External 1
//初始化
void RTCInit();
//设置时间
//参数：
//  UTime time：时间戳
void RTCTimeSet(UTime time);
//获取时间
//返回：UTime：时间戳
UTime RTCTimeGet();
//RTC中断函数
void RTCInterrupt();

#endif
#endif /* SOCDRIVER_RTC_H_ */
