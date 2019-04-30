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
    //enum e_LFXT1Freq crystalfreq;
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
/*    if(CRYSTAL1_ENABLE)
    {
        if(CRYSTAL1_FREQ==32768)crystalfreq=F32768;
        else if(CRYSTAL1_FREQ<1000000)crystalfreq=F400K_1M;
        else if(CRYSTAL1_FREQ<3000000)crystalfreq=F1M_3M;
        else if(CRYSTAL1_FREQ<16000000)crystalfreq=F3M_16M;
    }else crystalfreq=FVLOCLK;*/
   SysClockInit(DCOCLK_FREQ,LFXT1CLK_SEL,CRYSTAL1_CAP,
                MCLK_SEL,DIV1,
                ACLK_SEL,DIV1,
                SMCLK_SEL,SMCLK_DIV);
   GPIOInit();
#if TIMER_0A_EN>0
   Timer0AInit(TIMER_0A_SOURCE,TIMER_0A_SOURCE_DIV,TIMER_0A_BASE_INTR_EN,TIMER_0A_BASE_MODE);
   Timer0ABaseMaxCountSet(TIMER_0A_BASE_MAX_COUNT);
//   Timer0ABaseFreqSet(TIMER_0A_BASE_FREQ,0);
#endif
#if TIMER_1A_EN>0
   Timer1AInit(TIMER_1A_SOURCE,TIMER_1A_SOURCE_DIV,TIMER_1A_BASE_INTR_EN,TIMER_1A_BASE_MODE);
//   Timer1ABaseFreqSet(TIMER_1A_BASE_FREQ,0);
   Timer1ABaseMaxCountSet(TIMER_1A_BASE_MAX_COUNT);
#endif
#if BTIMER_COUNT>0
   BasicTimerInit();
#endif
   IE2&=0xf0;
#if HSPI_EN>0
   HSPIInit(HSPI_CLK_SEL,HSPI_CLK_DIV,HSPI_CPHA,HSPI_CPOL,HSPI_TX_INTERRUPT_EN,HSPI_RX_INTERRUPT_EN);
#endif

#if UART_EN>0
   UARTInit(UART_CLK_SEL,UART_CLK_DIV,UART_TX_INTERRUPT_EN,UART_RX_INTERRUPT_EN);
#endif
#if IIC_EN>0
   IICInit();
#endif

#if ADC_EN>0
   ADCInit();
#endif

   DriverInit();

#if RTC_EN>0
   RTCInit();
#endif
   __enable_interrupt();
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
                    BasicTimer[i].CallBack=0;
                    (*BasicTimer[i].CallBack)();
                }
            }else{
                while(BasicTimer[i].CallCount!=0)
                {
                    (*BasicTimer[i].CallBack)();
                    BasicTimer[i].CallCount--;
                }

            }

        }
    }
#endif
}

//---------------------------------------------------
//Name:
//Description:
//Author:Lucas S
//Test:none
//---------------------------------------------------
