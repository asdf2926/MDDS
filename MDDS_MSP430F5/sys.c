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
    GPIO_setAsOutputPin(GPIOA,P1_OUTPUT_PIN);
    GPIO_setAsOutputPin(GPIOB,P2_OUTPUT_PIN);
    GPIO_setAsOutputPin(GPIOC,P3_OUTPUT_PIN);
    GPIO_setAsOutputPin(GPIOD,P4_OUTPUT_PIN);
    GPIO_setAsOutputPin(GPIOE,P5_OUTPUT_PIN);
    GPIO_setAsOutputPin(GPIOF,P6_OUTPUT_PIN);
    GPIO_setAsOutputPin(GPIOG,P7_OUTPUT_PIN);
    GPIO_setAsOutputPin(GPIOH,P8_OUTPUT_PIN);
    GPIO_setAsOutputPin(GPIOI,P9_OUTPUT_PIN);
    GPIO_setAsOutputPin(GPIOJ,P10_OUTPUT_PIN);
    GPIO_setAsOutputPin(GPIOK,P11_OUTPUT_PIN);

    GPIO_setAsInputPin(GPIOA,P1_INPUT_PIN);
    GPIO_setAsInputPin(GPIOB,P2_INPUT_PIN);
    GPIO_setAsInputPin(GPIOC,P3_INPUT_PIN);
    GPIO_setAsInputPin(GPIOD,P4_INPUT_PIN);
    GPIO_setAsInputPin(GPIOE,P5_INPUT_PIN);
    GPIO_setAsInputPin(GPIOF,P6_INPUT_PIN);
    GPIO_setAsInputPin(GPIOG,P7_INPUT_PIN);
    GPIO_setAsInputPin(GPIOH,P8_INPUT_PIN);
    GPIO_setAsInputPin(GPIOI,P9_INPUT_PIN);
    GPIO_setAsInputPin(GPIOJ,P10_INPUT_PIN);
    GPIO_setAsInputPin(GPIOK,P11_INPUT_PIN);

    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIOA,P1_OUTPUT_FUNC_PIN);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIOB,P2_OUTPUT_FUNC_PIN);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIOC,P3_OUTPUT_FUNC_PIN);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIOD,P4_OUTPUT_FUNC_PIN);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIOE,P5_OUTPUT_FUNC_PIN);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIOF,P6_OUTPUT_FUNC_PIN);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIOG,P7_OUTPUT_FUNC_PIN);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIOH,P8_OUTPUT_FUNC_PIN);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIOI,P9_OUTPUT_FUNC_PIN);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIOJ,P10_OUTPUT_FUNC_PIN);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIOK,P11_OUTPUT_FUNC_PIN);

    GPIO_setAsPeripheralModuleFunctionInputPin(GPIOA,P1_INPUT_FUNC_PIN);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIOB,P2_INPUT_FUNC_PIN);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIOC,P3_INPUT_FUNC_PIN);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIOD,P4_INPUT_FUNC_PIN);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIOE,P5_INPUT_FUNC_PIN);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIOF,P6_INPUT_FUNC_PIN);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIOG,P7_INPUT_FUNC_PIN);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIOH,P8_INPUT_FUNC_PIN);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIOI,P9_INPUT_FUNC_PIN);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIOJ,P10_INPUT_FUNC_PIN);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIOK,P11_INPUT_FUNC_PIN);

    //Port select XT1
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P7,
        GPIO_PIN0 + GPIO_PIN1
        );
    //Initializes the XT1 crystal oscillator with no timeout
    //In case of failure, code hangs here.
    //For time-out instead of code hang use UCS_turnOnLFXT1WithTimeout()
    UCS_turnOnLFXT1(
        UCS_XT1_DRIVE_0,
        UCS_XCAP_3
        );

   GPIOInit();
#if BTIMER_COUNT>0
   BasicTimerInit();
#endif
   DriverInit();

#if RTC_EN>0
   RTCInit();
#endif
    // Enable global interrupt
    __bis_SR_register(GIE);

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
//Name:PowerPolicySet
//Description:Set power policy
//Author:Lucas S
//Test:none
//---------------------------------------------------
void PowerPolicySet(enum e_PowerPolicy PowerPolicy)
{
    switch(PowerPolicy)
    {
    case Off:
        __low_power_mode_4();//LPM4
        break;
    case Stop:
        __low_power_mode_3();//LPM3
        break;
    case Idle:
        __low_power_mode_0();//LPM0
        break;
    case LowPower://未实现
        break;
    case Normal://未实现
        break;
    case HighPerformance://未实现
        break;

    }
}

void delay_10us(int count) /* X10ms */
{
	unsigned int i, j;
	for (i = 0; i < count; i++)
		for (j = 0; j < 5; j++)
			;
}

//---------------------------------------------------
//Name:
//Description:
//Author:Lucas S
//Test:none
//---------------------------------------------------
