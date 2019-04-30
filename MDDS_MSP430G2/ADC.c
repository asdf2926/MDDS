/*
 * ADC.c
 *
 *  Created on: 2019年2月8日
 *      Author: asdf2
 */
#include "includes.h"
#if ADC_EN>0
const INT8S *Sequence;
INT16U *Result;//Count,CountBak;
INT8U ADCStatus;//0:none.1:converting.2:finished
//ADC初始化
void ADCInit()
{
    ADC10CTL0&=0xfffc;
    ADC10CTL0=(ADC_REF_SEL<<13)|(ADC_SAMP_TIME<<11)|(ADC_SAMP_RATE<<10)|(ADC_REF_GEN_VOL<<6)|0x1b8;//9:Reference output off.8:Reference buffer on only during sample-and-conversion.7:The first rising edge of the SHI signal triggers the sampling timer, but further sample-andconversions are performed automatically as soon as the prior conversion is completed.5:Reference on.4:ADC10 on.3:Interrupt enabled.1:ADC10 disabled.
    ADC10CTL1=/*(ADC_CH_HIGNEST)<<12|*/(ADC_CLK_DIV)<<5|(ADC_CLK_SOURCE)<<3|(ADC_DATA_LEFT_ALIGN<<9);//11-10:ADC10SC bit as Sample-and-hold source select.
    ADC10AE0=(ADC_CH_A7_EN<<7)|(ADC_CH_A6_EN<<6)|(ADC_CH_A5_EN<<5)|(ADC_CH_A4_EN<<4)|(ADC_CH_A3_EN<<3)|(ADC_CH_A2_EN<<2)|(ADC_CH_A1_EN<<1)|(ADC_CH_A0_EN<<0);
    ADC10CTL0|=0x2;
    ADCStatus=0;
}
//ADC启动一次转换
//注意：Sequence自增
void ADCStartCmd()
{
    ADC10CTL0&=0xfffc;
    ADC10CTL1&=0x0FFF;
    ADC10CTL1|=(*Sequence)<<12;
    ADC10CTL0|=0x3;
    Sequence++;
}
//ADC启动
//参数：
//  const INT8S *pSequence：转换序列指针，指向数组，数组为转换通道，-1代表数组结束
//  INT16U *dat：指向存放转换结果的指针
//返回：
//  BL：指示转换是否完成
//注意：这个函数几乎包含了所有功能，可以反复调用以查询，若返回1，则在下一次调用时再次启动转换
BL ADCStart(const INT8S *pSequence,INT16U *dat)
{
    Sequence=pSequence;Result=dat;
    if(ADCStatus==2)
    {
        ADCStatus=0;
        return 1;
    }
    if(ADCStatus)return 0;
    if(*Sequence!=-1)
    {
        ADCStartCmd();
        ADCStatus=1;
    }
    else return 1;
    return 0;
}

//ADC10中断
#pragma vector = ADC10_VECTOR
__interrupt void ADCInterrupt()
{
    *Result=ADC10MEM;
    Result++;
    if(*Sequence==-1)
    {
        ADCStatus=2;
        return;
    }
    ADCStartCmd();
}
#endif
