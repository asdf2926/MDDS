#ifndef _ADPTER_H_
#define _ADPTER_H_
//#include "stm32f0xx_hal.h"
#define PIN0 1
#define PIN1 2
#define PIN2 4
#define PIN3 8
#define PIN4 0x10
#define PIN5 0x20
#define PIN6 0x40
#define PIN7 0x80
#define PIN8 0x100
#define PIN9 0x200
#define PIN10 0x400
#define PIN11 0x800
#define PIN12 0x1000
#define PIN13 0x2000
#define PIN14 0x4000
#define PIN15 0x8000

void AdapterInit(void);
void AdapterDeInit(void);

//void GPIOInit();

void GPIOWrite(GPIO_TypeDef* Group,INT16U data);

void GPIOWritePin(GPIO_TypeDef* Group,INT16U PinMask,BL Statu);

//void GPIOWritePinF(GPIO_TypeDef* Group,INT16U PinMask,BL Statu);

INT16U GPIORead(GPIO_TypeDef* Group);

BL GPIOReadPin(GPIO_TypeDef* Group,INT16U PinMask);

//void GPIOSetMode(GPIO_TypeDef* Group,INT8U PinMask,enum e_GPIOPinMode Mode);

//void GPIOISR(GPIO_TypeDef* Group,INT8U Pin);
//HSPI等待数据发送完成（仅用于无中断模式）
#if HSPI_EN>0
#define HSPI_NORMAL 0
#define HSPI_INTR 1
#define HSPI_DMA 2


#if HSPI_TX_INTERRUPT_EN==0
void HSPIWaitTransmit(void);
#endif
//HSPI设置回调函数
//参数：
//  void (*pFunc)()：回调函数
//返回：无
//void HSPISetTxCallBack(void (*pFunc)());
//HSPI发送数据
//参数：
//  INT8U dat：数据
//返回：无
void HSPIWriteByte(INT8U dat);
void HSPISetCallBack(void (*pCallBack)());
void HSPIWriteBlock_DMA(const INT8U *dat,INT16U Len);
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi);
#endif
#if 0

void UARTWriteByte(INT8U dat);
void UARTWaitTransmit(void);
#endif
void IdleProcess(void);
#if BTIMER_COUNT>0

typedef struct{
    #if BT_EXT_CALLBACK>0
    void (*CallBack)(INT8U index);//????
    #else
    void (*CallBack)();//????
    
    #endif
    INT32U TimeTick;//????/礢
    INT32U CurTime;//???(??)
    INT8S CallCount;//?????,-1??????
} s_BasicTimer;

//???
extern s_BasicTimer BasicTimer[];
//????????(??)
extern INT8U TimerUsage;
//???
void BasicTimerInit(void);
//???????
//??:
//  INT32U TimeUS:??(礢)
//  BL SingleShot:??
//  void (*pCallBack)():????
//??:
//  INT8S:????,-1????
    #if BT_EXT_CALLBACK>0
INT8S BasicTimerAdd(INT32U TimeUS,BL SingleShot,void (*pCallBack)(INT8U index));
    #else
INT8S BasicTimerAdd(INT32U TimeUS,BL SingleShot,void (*pCallBack)());
    #endif
//???????
//??:
//  INT8U index:??
void BasicTimerDel(INT8U index);
void BasicTimerTick(void);
#endif

Time RTCTimeRGet(void);
void RTCTimeRSet(Time t);

#endif

