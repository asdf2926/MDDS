/*
 * _timer_make.h
 *
 *  Created on: 2019年2月2日
 *      Author: asdf2
 */
#ifndef _TA_NAME//like TA0
#error "Making code for a timerA must have a timer module name"
#endif
#ifndef _TA_FULL_NAME//like Timer0A
#error "Making code for a timerA must have a full timer module name"
#endif
#ifndef _TA_INT_NAME//like TIMER0_A
#error "Making code for a timerA must have a timer interrupt name"
#endif
#ifndef _TA_MACRO_NAME//like TIMER_0A
#error "Making code for a timerA must have a timer interrupt name"
#endif
#undef CCTL0
#undef CCTL1
#undef CCTL2
#undef CCR0
#undef CCR1
#undef CCR2


#define _GETREG(a,b) __COMB_AB(a,b)//所有宏的参数在这层里全部展开
#define __COMB_AB(a,b) a##b
#define GETREG(a) _GETREG(_TA_NAME,a)// 转换宏
#define GETVAL(a) _GETREG(_TA_FULL_NAME,a)// 转换宏
#define GETINT(a) _GETREG(_TA_INT_NAME,a)// 转换宏
#define GETMACRO(a) _GETREG(_TA_MACRO_NAME,a)// 转换宏

enum e_TimerBaseClockSource GETVAL(SourceClk);//时钟源
enum e_CLKDiv GETVAL(Div);//分频
enum e_TimerBaseMode GETVAL(BaseCountMode);//时基计数模式
void (*(GETVAL(CallBackFunc)[3]))();//回调函数
INT16U GETVAL(ExternTimer);//拓展计时器
INT32U GETVAL(CompareBak)[3];//比较模式计数
BL GETVAL(ExternMode)[3],GETVAL(SingleShot)[3];//拓展模式启用，单次定时

//
/*时基初始化
参数：
    enum e_TimerBaseClockSource SourceClkSel：时钟源设置
    enum e_CLKDiv ClkDiv：时钟输入分配
    BL InterruptEnable：中断启动（如果使用位数拓展，则必须启用）
    enum e_TimerBaseMode TimerBaseMode：时基工作模式
返回：无
    */
void GETVAL(Init)(enum e_TimerBaseClockSource SourceClkSel,enum e_CLKDiv ClkDiv,
                BL InterruptEnable,enum e_TimerBaseMode TimerBaseMode)
{
    GETVAL(CallBackFunc)[2]=GETVAL(CallBackFunc)[1]=GETVAL(CallBackFunc)[0]=0;
    GETVAL(SourceClk)=SourceClkSel;
    GETVAL(Div)=ClkDiv;GETVAL(BaseCountMode)=TimerBaseMode;
    GETREG(CTL)=(SourceClkSel<<8)|(ClkDiv<<6)|((InterruptEnable>0)<<1);
}
/*额外模块初始化
参数：
    INT8U Channel,：通道
    enum e_TimerAModuleInputMode InputModeSet,：捕获/比较模块工作模式
    enum e_TimerAModuleCaptureMode    CaptureModeSet,：捕获模式
    enum e_TimerAModuleInputSelect  InputSelectSet,：输入选择
    enum e_TimerAModuleSynchronizeCaptureSource SynchronizeCaptureSourceSet,：异步/同步捕获
    enum e_TimerAModuleOutputMode   OutputModeSet,：输出模式设置
    BL  InterruptEnable：中断允许
返回：无
 */
void GETVAL(ModuleInit)(INT8U Channel,
                      enum e_TimerAModuleInputMode InputModeSet,
                      enum e_TimerAModuleCaptureMode    CaptureModeSet,
                      enum e_TimerAModuleInputSelect  InputSelectSet,
                      enum e_TimerAModuleSynchronizeCaptureSource SynchronizeCaptureSourceSet,
                      enum e_TimerAModuleOutputMode   OutputModeSet,
                      BL  InterruptEnable)
{
#define VAL ((InputModeSet<<8)|((InterruptEnable>0)<<4)|(OutputModeSet<<5)|(SynchronizeCaptureSourceSet<<11)|(InputSelectSet<<12)|(CaptureModeSet<<14))
    switch(Channel)
    {
    case 0:
        GETREG(CCTL0)=VAL;
        break;
    case 1:
        GETREG(CCTL1)=VAL;
        break;
    case 2:
        GETREG(CCTL2)=VAL;
        break;
    }

}
/*时基频率设置
参数：
    INT32U Freq：频率
    INT32U ClkFreq：时钟频率（如果使用内部时钟，可以填0自动计算）
返回：无
 */
void GETVAL(BaseFreqSet)(INT32U Freq,INT32U ClkFreq)
{
    //INT32U clkgetClockFreq(GETVAL(SourceClk))
    if(ClkFreq==0)
    {
        assert((GETVAL(SourceClk)==ACLK)||(GETVAL(SourceClk)==SMCLK));
        ClkFreq=getClockFreq((enum e_ClockType)GETVAL(SourceClk));
    }
    Freq=Freq<<GETVAL(Div);
    if(GETVAL(BaseCountMode)==UpDownMode)Freq=Freq<<1;
    GETREG(CCR0)=(ClkFreq+(Freq>>1))/Freq;//四舍五入
}
/*时基频率设置
参数：
    INT16U count：计数次数
返回：无
 */

inline void GETVAL(BaseMaxCountSet)(INT16U count)
{
    GETREG(CCR0)=count;
}
/*定时器启动
参数：无
返回：无
 */

void GETVAL(Start)()
{
    GETVAL(ExternTimer)=0;
    GETREG(R)=0;
    GETREG(CTL)|=GETVAL(BaseCountMode)<<4;

}
/*定时器停止
参数：无
返回：无
 */

void GETVAL(Stop)()
{
    GETREG(CTL)&=0xFFCF;
}
/*PWM模式设置占空比
参数：
    INT8U Channel,：通道
    INT16U Value：值（0xffff对于100%）
返回：无
 */
void GETVAL(ModulePWMSet)(INT8U Channel,INT16U Value)
{
#define VAL1(n) (((INT32U)Value*n)>>16)
    switch(Channel)
    {
    case 0:
        GETREG(CCR0)=VAL1(GETREG(CCR0));
        break;
    case 1:
        GETREG(CCR1)=VAL1(GETREG(CCR0));
        break;
    case 2:
        GETREG(CCR2)=VAL1(GETREG(CCR0));
        break;
    }
}
/*捕获模式初始化
参数：
    INT8U Channel,：通道
    BL ExternModeEN：拓展模式，可以捕获32位值
    void (*pCallBackFunc)(INT32U time)：指向回调函数的指针
返回：无
注意：TimerAModuleInit仍然要调用
 */
void GETVAL(ModuleCaptureInit)(INT8U Channel,BL ExternModeEN,void (*pCallBackFunc)(INT32U time))
{
    GETVAL(ExternMode)[Channel]=ExternModeEN;
    GETVAL(CallBackFunc)[Channel]=pCallBackFunc;
    GETVAL(SingleShot)[Channel]=1;
    switch(Channel)
    {
    case 0:
        GETREG(CCTL0)|=0x10;
        break;
    case 1:
        GETREG(CCTL1)|=0x10;
        break;
    case 2:
        GETREG(CCTL2)|=0x10;
        break;
    }
}
/*比较模式初始化
参数：
    INT8U Channel,：通道
    INT32U Cycles：时间
    void (*pCallBackFunc)(INT32U time)：指向回调函数的指针
返回：无
注意：TimerAModuleInit仍然要调用
 */
void GETVAL(ModuleCompareInit)(INT8U Channel, INT16U Cycles,void (*pCallBackFunc)(),BL isSingleShot)
{
    GETVAL(CallBackFunc)[Channel]=pCallBackFunc;
    GETVAL(CompareBak)[Channel]=Cycles;
    GETVAL(SingleShot)[Channel]=isSingleShot;
    switch(Channel)
    {
    case 0:
        GETREG(CCTL0)|=0x10;
        GETREG(CCR0)=Cycles+GETREG(R);
        break;
    case 1:
        GETREG(CCTL1)|=0x10;
        GETREG(CCR1)=Cycles+GETREG(R);
        break;
    case 2:
        GETREG(CCTL2)|=0x10;
        GETREG(CCR2)=Cycles+GETREG(R);
        break;
    }

}
//中断函数：时基，1、2模块
#pragma vector = GETINT(1_VECTOR)
__interrupt void GETVAL(Interrupt1)()
{
#if 0
    INT16U flag=GETREG(IV);
    if(flag&0x10)//TAIFG
    {
        GETVAL(ExternTimer)++;
#if GETMACRO(A_BASE_INTR_CALLBACK)>0
        TimerABaseInterruptHook();
#endif
    }
    if(flag&0x02)//CCIFG1
    {
        if(!GETVAL(SingleShot)[1])GETREG(CCR1)=GETVAL(CompareBak)[1]+GETREG(CCR1);
        else GETREG(CCTL1)=0x2100;//No capture,GND,Asynchronous capture,Capture mode,OUT bit value,Interrupt disabled,output 0,No interrupt pending
        if(GETVAL(CallBackFunc)[1])(*(GETVAL(CallBackFunc)[1]))();
    }
    if(flag&0x04)//CCIFG2
    {
        if(!GETVAL(SingleShot)[2])GETREG(CCR2)=GETVAL(CompareBak)[2]+GETREG(CCR2);
        else GETREG(CCTL2)=0x2100;//No capture,GND,Asynchronous capture,Capture mode,OUT bit value,Interrupt disabled,output 0,No interrupt pending
        if(GETVAL(CallBackFunc)[2])(*(GETVAL(CallBackFunc)[2]))();

    }
#endif
#if 1
    switch(__even_in_range(GETREG(IV), 0x0A))
    {
    case 10://TAIFG
        GETVAL(ExternTimer)++;
#if GETMACRO(_BASE_INTR_CALLBACK)>0
        GETVAL(BaseInterruptHook)();
#endif
#define Timer0A 0
#define Timer1A 1
#if (BTIMER_COUNT>0)&&(_TA_FULL_NAME==BTIMER_INTERFACE)
        __low_power_mode_off_on_exit();
#endif
#undef Timer0A
#undef Timer1A
        break;
    case 02://CCIFG1
        if(!GETVAL(SingleShot)[1])
        {
            GETREG(CCR1)=GETVAL(CompareBak)[1]+GETREG(CCR1);
            if(GETMACRO(_BASE_MODE)==UpMode)while(GETREG(CCR1)>GETREG(CCR0))GETREG(CCR1)-=GETREG(CCR0);
        }else
        {
            GETREG(CCTL1)=0x2100;//No capture,GND,Asynchronous capture,Capture mode,OUT bit value,Interrupt disabled,output 0,No interrupt pending
#define Timer0A 0
#define Timer1A 1
#if (BTIMER_COUNT>0)&&(_TA_FULL_NAME==BTIMER_INTERFACE)
            TimerUsage&=0xfd;
#endif
#undef Timer0A
#undef Timer1A

        }
        if(GETVAL(CallBackFunc)[1])(*(GETVAL(CallBackFunc)[1]))();
        break;
    case 04://CCIFG2
        if(!GETVAL(SingleShot)[2])
        {
            GETREG(CCR2)=GETVAL(CompareBak)[2]+GETREG(CCR2);
            if(GETMACRO(_BASE_MODE)==UpMode)while(GETREG(CCR2)>GETREG(CCR0))GETREG(CCR2)-=GETREG(CCR0);

        }else
        {
             GETREG(CCTL2)=0x2100;//No capture,GND,Asynchronous capture,Capture mode,OUT bit value,Interrupt disabled,output 0,No interrupt pending
#define Timer0A 0
#define Timer1A 1
#if (BTIMER_COUNT>0)&&(_TA_FULL_NAME==BTIMER_INTERFACE)
            TimerUsage&=0xfb;
#endif
#undef Timer0A
#undef Timer1A

        }
        if(GETVAL(CallBackFunc)[2])(*(GETVAL(CallBackFunc)[2]))();
        break;

    }
#endif
}



