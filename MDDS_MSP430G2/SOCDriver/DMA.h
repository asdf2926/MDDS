/*
 * DMA.h
 *
 *  Created on: 2019年2月3日
 *      Author: asdf2
 */

#ifndef SOCDRIVER_DMA_H_
#define SOCDRIVER_DMA_H_
//2553不支持DMA
#if DMA_EN>0

enum e_DMADynamicPolicy{
    DMANow,
    DMALater
};

enum e_DMAStartSignal{
    SoftwareTrigger ,// DMAREQ bit (software trigger)
    TimerACCR2Tirgger   ,// TACCR2 CCIFG bit
    TimerBTirgger   ,// TBCCR2 CCIFG bit
    UCA0RxTirgger   ,// Serial data received UCA0RXIFG
    UCA0TxTirgger   ,// Serial data transmit ready UCA0TXIFG
    DAC12Tirgger    ,// DAC12_0CTL DAC12IFG bit
    ADC12Tirgger    ,// ADC12 ADC12IFGx bit
    TimerACCR0Tirgger   ,// TACCR0 CCIFG bit
    TimerBCCR0Tirgger   ,// TBCCR0 CCIFG bit
    UCA1RxTirgger   ,// Serial data received UCA1RXIFG
    UCA1TxTirgger   ,// Serial data transmit ready UCA1TXIFG
    MultiplierTirgger   ,// Multiplier ready
    UCB0RxTirgger   ,// Serial data received UCB0RXIFG
    UCB0TxTirgger   ,// Serial data transmit ready UCB0TXIFG
    LastDMAChannelTirgger   ,// DMAxIFG last channel:0:2,1:0,2:1
    ExternalTirgger // External trigger DMAE0
};

enum e_DMAMode{
    SingleMode  ,// Single transfer Each transfer requires a trigger. DMAEN is automatically cleared when DMAxSZ transfers have been made.
    BlockMode   ,// Block transfer A complete block is transferred with one trigger. DMAEN is automatically cleared at the end of the block transfer.
    HalfSpeedBlockMode  ,// Burst-block transfer CPU activity is interleaved with a block transfer. DMAEN is automatically cleared at the end of the burst-block transfer.
    HalfSpeedBlockMode1 ,// Burst-block transfer CPU activity is interleaved with a block transfer. DMAEN is automatically cleared at the end of the burst-block transfer.
    RepeatedSingleMode  ,// Repeated single transfer Each transfer requires a trigger. DMAEN remains enabled.
    RepeatedBlockMode   ,// Repeated block transfer A complete block is transferred with one trigger. DMAEN remains enabled.
    RepeatedHalfSpeedBlockMode  ,// Repeated burst-block transfer CPU activity is interleaved with a block transfer. DMAEN remains enabled.
    RepeatedHalfSpeedBlockMode1 // Repeated burst-block transfer CPU activity is interleaved with a block transfer. DMAEN remains enabled.
};

enum e_DMAAddrIncrement{
    Unchange,
    Unchange1,
    Increase,
    Decrease
};

enum e_DMADataMode{
    WordData,
    ByteData
};

enum e_DMATriggerMode{
    RisingEdge,
    HighLever
};

typedef struct{
    enum e_DMAStartSignal Signal;//触发信号
    enum e_DMAMode DMAMode;//DMA模式
    enum e_DMATriggerMode TriggerMode;//触发模式

    void *SrcAddr;//源地址
    enum e_DMADataMode SrcDataMode;//源数据模式
    enum e_DMAAddrIncrement SrcAddrInc;//源地址增长方向

    void *DscAddr;//目标地址
    enum e_DMADataMode DscDataMode;//目标数据模式
    enum e_DMAAddrIncrement DscAddrInc;//目标地址增长方向

    INT16U Size;
} s_DMARequest;

//初始化DMA
//使用conf。h进行初始化
void DMAInit();
//静态通道启动
//参数：
//  INT8U Channel：通道
//返回：无
void DMAStaticStart(INT8U Channel);
//动态通道启动
//参数：
//  s_DMARequest Req：DMA请求
//返回：INT8U：0-》成功，非0-》失败
INT8U DMADynamicStart(s_DMARequest Req,enum e_DMADynamicPolicy);
#endif
#endif /* SOCDRIVER_DMA_H_ */
