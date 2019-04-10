/*
 * basic_timer.h
 *
 *  Created on: 2019年2月2日
 *      Author: asdf2
 */

#ifndef DRIVER_BASIC_TIMER_H_
#define DRIVER_BASIC_TIMER_H_

//基本定时器，用以提供一个通用接口
#define GETFUNC(a) _COMB_AB(BTIMER_INTERFACE,a)// 转换宏

//硬件计时器资源
#define INTERFACE_CHANNEL_MIN 1//可用的最低通道
#define INTERFACE_CHANNEL_MAX 2//可用的最高通道

//#define BasicTimerInit(Name)
//#define BasicTimerStart(Name,Func,TimeUs,SingleShot) \
    GETFUNC(ModuleInit)(_COMB_AB(Name,_CHANNEL),Compare,No,GND,Synchronous,OutBitValue,1);\
    GETFUNC(ModuleCompareInit)(_COMB_AB(Name,_CHANNEL),(INT16U)((INT32U)TimeUs*GETFUNC(BaseFreqGet)()/1000000),Func,SingleShot);
//基本定时器存储结构
typedef struct{
    void (*CallBack)();//回调函数
    INT32U TimeUS;//定时时间/μS
    INT32U CurTime;//现计时（减少）
    INT8S CallCount;//已超时次数，-1代表单次定时
} s_BasicTimer;

//保存用
extern s_BasicTimer BasicTimer[];
//硬件资源使用标志（按位）
extern INT8U TimerUsage;
//初始化
void BasicTimerInit();
//添加一个定时器
//参数：
//  INT32U TimeUS：时间（μS）
//  BL SingleShot：单次
//  void (*pCallBack)()：回调函数
//返回：
//  INT8S：定时器号，-1代表失败
INT8S BasicTimerAdd(INT32U TimeUS,BL SingleShot,void (*pCallBack)());
//删除一个定时器
//参数：
//  INT8U index：编号
void BasicTimerDel(INT8U index);

#endif /* DRIVER_BASIC_TIMER_H_ */
