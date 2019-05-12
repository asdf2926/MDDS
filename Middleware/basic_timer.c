/*
 * basic_timer.c
 *
 *  Created on: 2019年2月6日
 *      Author: asdf2
 */
#include "includes.h"
#if BTIMER_COUNT>0
INT8S pBasicTimer;
s_BasicTimer BasicTimer[BTIMER_COUNT];
//初始化
void BasicTimerInit()
{
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
    #if BT_EXT_CALLBACK>0
INT8S BasicTimerAdd(INT32U TimeUS,BL SingleShot,void (*pCallBack)(INT8U index))
    #else
INT8S BasicTimerAdd(INT32U TimeUS,BL SingleShot,void (*pCallBack)())
    #endif
{
    INT8U i;
    for(i=0;i<BTIMER_COUNT;i++)
        if(BasicTimer[i].CallBack==0)
			{
					BasicTimer[i].CallBack=pCallBack;
					BasicTimer[i].CurTime=BasicTimer[i].TimeTick=TimeUS/1000;
					BasicTimer[i].CallCount=-SingleShot;
					return i;
			}
    return -1;
}
void BasicTimerTick()
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
                BasicTimer[i].CurTime=BasicTimer[i].TimeTick;
				if(BasicTimer[i].CallCount!=-2)
					BasicTimer[i].CallCount++;
            }


        }
    }
}

void BasicTimerProcess()
{
    INT8U i;
    for(i=0;i<BTIMER_COUNT;i++)
    {
        if(BasicTimer[i].CallBack)
        {
            if(BasicTimer[i].CallCount==-1)
            {
                if(BasicTimer[i].CurTime==0)
                {
    #if BT_EXT_CALLBACK>0
                    (*BasicTimer[i].CallBack)(i);
    #else
                    (*BasicTimer[i].CallBack)();
    #endif
                    BasicTimer[i].CallBack=0;
                }
            }else{
                while(BasicTimer[i].CallCount!=0)
                {
    #if BT_EXT_CALLBACK>0
                    (*BasicTimer[i].CallBack)(i);
    #else
                    (*BasicTimer[i].CallBack)();
    #endif
                    BasicTimer[i].CallCount--;
                }

            }

        }
    }
}

//删除一个定时器
//参数：
//  INT8U index：编号

void BasicTimerDel(INT8U index)
{
	BasicTimer[index].CallBack=0;
}
#endif
