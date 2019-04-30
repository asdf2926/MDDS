/*
 * basic_timer.c
 *
 *  Created on: 2019年2月6日
 *      Author: asdf2
 */
#include "includes.h"
#if BTIMER_COUNT>0
INT8U TimerUsage;
INT8S pBasicTimer;
s_BasicTimer BasicTimer[BTIMER_COUNT];
//初始化
void BasicTimerInit()
{
    TimerUsage=0;
    for(pBasicTimer=BTIMER_COUNT-1;pBasicTimer>=0;pBasicTimer--)
    {
        BasicTimer[pBasicTimer].CallBack=0;
    }
    pBasicTimer=0;
}
//添加一个定时器
//参数：
//  INT32U TimeUS：时间（μS）
//  BL SingleShot：单次
//  void (*pCallBack)()：回调函数
//返回：
//  INT8S：定时器号，-1代表失败

INT8S BasicTimerAdd(INT32U TimeUS,BL SingleShot,void (*pCallBack)())
{
#if GETFUNC(BaseSourceFreq)>1000000
#define CALCNUM (GETFUNC(BaseSourceFreqKHz)/1000)
#else
#define CALCNUM GETFUNC(BaseSourceFreq)/1000000

#endif
    INT8U i;
    if(TimeUS>=1000000/GETFUNC(BaseFreqGet)())
    {
        //long
        for(i=0;i<BTIMER_COUNT;i++)if(BasicTimer[i].CallBack==0)
        {
            BasicTimer[i].CallBack=pCallBack;
            BasicTimer[i].CurTime=BasicTimer[i].TimeUS=TimeUS*GETFUNC(BaseFreqGet)()/1000000;
            BasicTimer[i].CallCount=-SingleShot;
            return i+1+INTERFACE_CHANNEL_MAX;
        }
    }else{
        //short
        for(i=INTERFACE_CHANNEL_MIN;i<=INTERFACE_CHANNEL_MAX;i++)
        {
            if((TimerUsage&(1<<i))==0)
            {
                TimerUsage|=1<<i;
                _COMB_AB(BTIMER_INTERFACE,ModuleInit)(i,Compare,No,GND,Synchronous,OutBitValue,1);
                _COMB_AB(BTIMER_INTERFACE,ModuleCompareInit)(i,(INT16U)(TimeUS*CALCNUM),pCallBack,SingleShot);
                return i;
            }
        }
        return -1;
    }
    return -1;
}
//删除一个定时器
//参数：
//  INT8U index：编号

void BasicTimerDel(INT8U index)
{
    if(index<=INTERFACE_CHANNEL_MAX)_COMB_AB(BTIMER_INTERFACE,ModuleInit)(1<<index,Capture,No,GND,Synchronous,OutBitValue,1);
    else BasicTimer[index-1-INTERFACE_CHANNEL_MAX].CallBack=0;
}

void _COMB_AB(BTIMER_INTERFACE,BaseInterruptHook)()
{
    INT8U i;
    for(i=0;i<BTIMER_COUNT;i++)
    {
        if(BasicTimer[i].CallBack)
        {
            if(BasicTimer[i].CurTime==0)continue;
            BasicTimer[i].CurTime-=1;
            if(BasicTimer[i].CurTime)continue;
            //(*BasicTimer[i].CallBack)();
            //if(BasicTimer[i].CallCount==-1)BasicTimer[i].CallBack=0;
            if(BasicTimer[i].CallCount!=-1)
            {
                BasicTimer[i].CurTime=BasicTimer[i].TimeUS;
                BasicTimer[i].CallCount++;
            }


        }
    }
}
#endif
