/*
 * DMA.c
 *
 *  Created on: 2019年2月3日
 *      Author: asdf2
 */
#include "includes.h"
#if (0 && DMA_EN>0)

//初始化DMA
//使用conf。h进行初始化
//void DMAInit()
//{
   // DMACTL1=1;//The DMA transfer occurs immediately.+DMA channel priority is DMA0 - DMA1 - DMA2+NMI interrupt interrupts a DMA transfer
//#if DMA0_STATIC>0
//    DMAStaticChannelInit(0,DMA0_REQUEST);
//#endif
//#if DMA1_STATIC>0
//    DMAStaticChannelInit(1,DMA0_REQUEST);
//#endif
//#if DMA2_STATIC>0
//    DMAStaticChannelInit(2,DMA0_REQUEST);
//#endif
//}

//void DMAStaticChannelInit(INT8U Channel,s_DMARequest Req)
//{
//
//    DMACTL0=(INT16U)(Req。)
//}

//静态通道启动
//参数：
//  INT8U Channel：通道
//返回：无
//void DMAStaticStart(INT8U Channel)
//{

//}
//动态通道启动
//参数：
//  s_DMARequest Req：DMA请求
//返回：INT8U：0-》成功，非0-》失败
//INT8U DMADynamicStart(s_DMARequest Req)
//{

//}

#endif
