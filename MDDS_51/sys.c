/*
 * sys.c
 *
 *  Created on: 2019锟斤拷1锟斤拷17锟斤拷
 *      Author: Lucas S
 */
#include <includes.h>


//---------------------------------------------------
//Name:SystemInit
//Description:System Initial
//Author:Lucas S
//Test:none
//---------------------------------------------------
//系统初始化
//注意：此函数用于主函数进行初始化，并不应再调用其他初始化函数（特殊说明的除外）
void SystemInit()
{
   

//定时器，gpio
   GPIOInit();
   TimerInit();
	BasicTimerInit();
   DriverInit();
	MiddlewareInit();

}
//空闲处理
//注意：此函数不应在中断中调用

void IdleProcess()
{
#if BTIMER_COUNT>0
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
#endif
#if APPE_EN>0
    AppEPendSolve();
	
#endif
}

//---------------------------------------------------
//Name:
//Description:
//Author:Lucas S
//Test:none
//---------------------------------------------------
