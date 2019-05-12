/*
 * rcc.c
 *
 *  Created on: 2019年1月14日
 *      Author: Lucas S
 */
#include <includes.h>
enum e_DCOFreq DCOFreq;
enum e_LFXT1Freq LFXT1Freq;
enum e_LFXT1Cap LFXT1Cap;
enum e_ClockSource CLKSource[3];
enum e_CLKDiv CLKDiv[3];

//---------------------------------------------------
//Name:SysClockInit
//Description:System clock initial
//Author:Lucas S
//Test:partly
//---------------------------------------------------
void SysClockInit(enum e_DCOFreq DCOSel,
                  enum e_LFXT1Freq LFXT1FreqSel,enum e_LFXT1Cap LFXT1CapSel,
                  enum e_ClockSource MCLKSel,enum e_CLKDiv MCLKDivSel,
                  enum e_ClockSource ACLKSel,enum e_CLKDiv ACLKDivSel,
                  enum e_ClockSource SMCLKSel,enum e_CLKDiv SMCLKDivSel)
{
    INT32U count;
    DCOFreq=DCOSel;//记录设置
    LFXT1Freq=LFXT1FreqSel;
    LFXT1Cap=LFXT1CapSel;
    CLKSource[0]=MCLKSel;
    CLKDiv[0]=MCLKDivSel;
    CLKSource[1]=ACLKSel;
    CLKDiv[1]=ACLKDivSel;
    CLKSource[2]=SMCLKSel;
    CLKDiv[2]=SMCLKDivSel;
    DCOCTL=0;
    switch(DCOSel)//初始化DCO
    {
    case F1000K:
        DCOCTL=CALDCO_1MHZ;
        BCSCTL1=CALBC1_1MHZ;
        break;
     case F8000K:
        DCOCTL=CALDCO_8MHZ;
        BCSCTL1=CALBC1_8MHZ;
        break;
    case F12000K:
        DCOCTL=CALDCO_12MHZ;
        BCSCTL1=CALBC1_12MHZ;
        break;
     case F16000K:
        DCOCTL=CALDCO_16MHZ;
        BCSCTL1=CALBC1_16MHZ;
        break;
     default:
        DCOCTL=0x60;
        BCSCTL1=DCOSel;
        break;
    }
    BCSCTL1&=0x0F;
    if(LFXT1FreqSel>=F400K_1M)//初始化LFXT1
    {
        LFXT1FreqSel-=F400K_1M;
        BCSCTL1|=0x40;
    }
    BCSCTL1|=ACLKDivSel<<4;
    BCSCTL2=0;
    switch(MCLKSel)//初始化MCLK
    {
    case DTOCLK:
        break;
    case LFXT1CLK:
    case VLOCLK:
        BCSCTL2|=0x80;
        break;
    default:
        break;
    }
    BCSCTL2|=MCLKDivSel<<4;
    switch(SMCLKSel)//初始化SMCLK
    {
    case DTOCLK:
        break;
    case XT2CLK:
    case VLOCLK:
        BCSCTL2|=0x08;
        break;
    default:
        break;
    }
    BCSCTL2|=SMCLKDivSel<<1;
    BCSCTL3=0;
    BCSCTL3|=LFXT1FreqSel<<4;
    BCSCTL3|=LFXT1CapSel<<2;
    count=0;
    //!ACLK未完成
    while(IFG1 & OFIFG)//等待LFXT1工作
    {
        IFG1 &= ~OFIFG;
        __delay_cycles(10000);
        if(count++>50)//超时时切换为VLOCLK
        {
            LFXT1Freq=FVLOCLK;
            BCSCTL1&=0xb0;
            BCSCTL3|=0x20;
            BCSCTL3&=0xef;
            break;
        }
    }
    IE1|=OFIE;//使能时钟中断
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
//DCO频率表
const INT32U TABDCOFreq[]={16000000,12000000,8000000,1000000,100000,150000,210000,300000,410000,580000,750000,1200000,1600000,2300000,3400000,4250000,6000000,7800000,11250000,15250000};
INT32U getClockFreq(enum e_ClockType Clk)
{
    INT8U lm;
    enum e_ClockSource cs;
    cs=CLKSource[Clk];//源
    lm=CLKDiv[Clk];//分频
    switch(cs)
    {
    case LFXT1CLK:
        if(LFXT1Freq==FVLOCLK)return 12000>>lm;//VLOCLK=12K
        else return CRYSTAL1_FREQ>>lm;//取conf.h中配置
    case XT2CLK:
        return 0;
    case DTOCLK:
        return TABDCOFreq[DCOFreq+4]>>lm;//取DCO配置
    case VLOCLK:
        return 12000>>lm;//VLOCLK=12K
    }
    return 0;
}
//---------------------------------------------------
//Name:
//Description:
//Author:Lucas S
//Test:none
//---------------------------------------------------
