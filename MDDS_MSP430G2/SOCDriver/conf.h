/*
 * conf.h
 *
 *  Created on: 2019年1月17日
 *      Author: asdf2
 */

#ifndef CONF_H_
#define CONF_H_

#define CRYSTAL1_ENABLE 0//外部振荡器使能
#define CRYSTAL1_FREQ 32768//外部振荡器频率
#define CRYSTAL1_CAP C12P//外部振荡器电容
#define DCOCLK_FREQ F16000K
#define LFXT1CLK_SEL FVLOCLK
#define MCLK_SEL DTOCLK
#define MCLK_FREQ 16000000//不用于初始化
#define ACLK_SEL LFXT1CLK
#define SMCLK_SEL DTOCLK
#define SMCLK_DIV DIV1
#define SMCLK_FREQ 16000000//不用于初始化
//----------------------------IO口模式---------------------------------

#define P1_0_MODE PINMODE_OUTPUT
#define P1_1_MODE PINMODE_INPUT
#define P1_2_MODE PINMODE_OUTPUT//|PINMODE_SELECT2)//MOSI
#define P1_3_MODE PINMODE_OUTPUT//|PINMODE_INPUT_INT_R
#define P1_4_MODE (PINMODE_OUTPUT|PINMODE_SELECT2)//SCLK
#define P1_5_MODE PINMODE_INPUT
#define P1_6_MODE (PINMODE_OUTPUT|PINMODE_SELECT2)//SCL
#define P1_7_MODE (PINMODE_INPUT|PINMODE_SELECT2)//SDA

#define P2_0_MODE PINMODE_INPUT
#define P2_1_MODE PINMODE_OUTPUT
#define P2_2_MODE PINMODE_OUTPUT
#define P2_3_MODE PINMODE_INPUT
#define P2_4_MODE PINMODE_OUTPUT
#define P2_5_MODE PINMODE_INPUT
#define P2_6_MODE PINMODE_OUTPUT
#define P2_7_MODE PINMODE_OUTPUT

#define P1_OUTPUT 0xff//初始化时P1口输出状态

#define P2_OUTPUT 0xff//初始化时P2口输出状态

//-------------------------定时器设置-----------------------------------------
#define TIMER_0A_EN 0
#if TIMER_0A_EN>0
#define TIMER_0A_SOURCE T_SMCLK//源
#define TIMER_0A_SOURCE_DIV DIV1//分配
#define TIMER_0A_BASE_INTR_EN 1//中断使能
#define TIMER_0A_BASE_MODE UpMode//计数模式
#define TIMER_0A_BASE_FREQ 1000//溢出频率（已经不用于初始化）
#define TIMER_0A_BASE_MAX_COUNT 12000//时基最大计数
#define TIMER_0A_BASE_INTR_CALLBACK 1//启动时基回调函数
#endif
#define TIMER_1A_EN 1
#if TIMER_1A_EN>0
#define TIMER_1A_SOURCE T_SMCLK//源
#define TIMER_1A_SOURCE_DIV DIV1//分配
#define TIMER_1A_BASE_INTR_EN 1//中断使能
#define TIMER_1A_BASE_MODE UpMode//计数模式
#define TIMER_1A_BASE_CLK_FREQ_KHZ 16//时基频率（已经不用于初始化）小于1的填0
#define TIMER_1A_BASE_FREQ 1000//溢出频率（已经不用于初始化）
#define TIMER_1A_BASE_MAX_COUNT 16000//时基最大计数
#define TIMER_1A_BASE_INTR_CALLBACK 1//启动时基回调函数
#endif
//-------------------------HSPI------------------------------------------
#define HSPI_EN 0               //使能HSPI
#if HSPI_EN>0
#define HSPI_INTERFACE 0     //选择使用模块：0->UCA0或1->UCB0
#define HSPI_CLK_SEL USCI_SMCLK //时钟选择：USCI_NA（无）或USCI_ACLK（ACLK）或USCI_SMCLK（SMCLK）
#define HSPI_CLK_DIV 2         //时钟分频：1~65535
#define HSPI_MSB_F 1            //MSP在前
#define HSPI_CPOL 1             //CPOL
#define HSPI_CPHA 1             //CPHA
#define HSPI_TX_INTERRUPT_EN 1  //使能发送中断
#define HSPI_RX_INTERRUPT_EN 0  //
#endif
//-------------------------UART------------------------------------------
#define UART_EN 0
#if UART_EN>0
#define UART_INTERFACE 0     //选择使用模块：0->UCA0
#define UART_CLK_SEL USCI_SMCLK //时钟选择：USCI_NA（无）或USCI_ACLK（ACLK）或USCI_SMCLK（SMCLK）
#define UART_CLK_DIV 104        //时钟分频：1~65535//9600bps@1M->104
#define UART_MSB_F 1            //MSP在前
#define UART_TX_INTERRUPT_EN 0  //使能发送中断//使用DMA时不要开启
#define UART_RX_INTERRUPT_EN 0  //
#endif
//-------------------------IIC-------------------------------------------
#define IIC_EN 1
#if IIC_EN>0
#define IIC_INTERFACE 1     //选择使用模块：1->UCB0
#define IIC_BAUDRATE_DIV 	(SMCLK_FREQ*3/250000)						/*I2C波特率控制*/
#define IIC_SLAVE_ADDR 				0x20				/*从机TCA6416A的地址*/
//#define IIC_TX_STATE 						0					/*I2C发送状态*/
//#define IIC_RX_STATE						1					/*I2C接收状态*/
#define IIC_TX_INTERRUPT_EN 0  //使能发送中断//使用DMA时不要开启
#define IIC_RX_INTERRUPT_EN 0  //

#endif
//-------------------------Basic Timer-----------------------------------
#define BTIMER_COUNT 3
#if BTIMER_COUNT>0
#define BTIMER_INTERFACE Timer1A
#endif

//--------------------------RTC------------------------------------------
#define RTC_EN 0//使能RTC
#if RTC_EN>0
#define RTC_MODE RTC_Internal//RTC_Internal/RTC_External(Don't use)
#define RTC_INTR_TIME_IN_MS 1000//RTC计时中断时间/ms
#define RTC_INTERNAL_TIMER RTC_1S//基本定时器接口（弃用）

#endif
//--------------------------ADC-----------------------------------------
#define ADC_EN 1
#if ADC_EN>0
#define ADC_REF_SEL VREF_GND
#define ADC_SAMP_TIME ADCCLK64
#define ADC_SAMP_RATE ADC50KSPS
#define ADC_REF_GEN_VOL ADC1500MV
#define ADC_CLK_SOURCE ADC_SMCLK
#define ADC_DATA_LEFT_ALIGN 0

#define ADC_CLK_DIV 1//1~8

#define ADC_CH_A0_EN 0//0
#define ADC_CH_A1_EN 0//1
#define ADC_CH_A2_EN 0//2
#define ADC_CH_A3_EN 0//3
#define ADC_CH_A4_EN 0//4
#define ADC_CH_A5_EN 0//5
#define ADC_CH_A6_EN 0//6
#define ADC_CH_A7_EN 0//7
#define ADC_CH_VEREF_P_EN 1//8//useless
#define ADC_CH_VREF_N_EN 0//9//useless
#define ADC_CH_TEMP_EN 1//10//useless
#define ADC_CH_VCC_VSS_EN 0//11//(VCC - VSS) / 2//useless
#define ADC_CH_A12_EN 0//12//(VCC - VSS) / 2, A12 on MSP430F22xx devices
#define ADC_CH_A13_EN 0//13//(VCC - VSS) / 2, A13 on MSP430F22xx devices
#define ADC_CH_A14_EN 0//14//(VCC - VSS) / 2, A14 on MSP430F22xx devices
#define ADC_CH_A15_EN 0//15//(VCC - VSS) / 2, A15 on MSP430F22xx devices

//#define ADC_CH_HIGNEST 10

#endif
//--------------------------DMA-----------------------------------------
#define DMA_EN 0    //DMA is supported only in MSP430x2xx device family
#if DMA_EN>0
#define DMA_DYNAMIC_POLICY DMA_DIRECT//DMA_DIRECT/DMA_LIST

#define DMA_LIST_SIZE 5

#define DMA0_STATIC 1//DMA功能固定，不能被动态调度
#if DMA0_STATIC>0
#define DMA0_REQUEST {SoftwareTrigger,BlockMode,RisingEdge,0,WordData,Increase,0,WordData,Increase,0}
#endif

#define DMA1_STATIC 1//DMA功能固定，不能被动态调度
#if DMA1_STATIC>0
#define DMA1_REQUEST {SoftwareTrigger,BlockMode,RisingEdge,0,WordData,Increase,0,WordData,Increase,0}
#endif

#define DMA2_STATIC 1//DMA功能固定，不能被动态调度
#if DMA2_STATIC>0
#define DMA2_REQUEST {SoftwareTrigger,BlockMode,RisingEdge,0,WordData,Increase,0,WordData,Increase,0}
#endif

#endif
//----------------------自动配置----------------------------
#if LFXT1_FREQ>1000000
#define LFXT1_HIGHSPEED 1//高速外部振荡器
#else
#define LFXT1_HIGHSPEED 0//低速外部振荡器
#endif

#endif /* CONF_H_ */
