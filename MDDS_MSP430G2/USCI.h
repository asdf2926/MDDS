/*
 * HSPI.h
 *
 *  Created on: 2019年1月30日
 *      Author: asdf2
 */

#ifndef USCI_H_
#define USCI_H_
#if UART_EN+HSPI_EN>0
enum e_USCIClkSource{//HSPI时钟源
    USCI_NA,//无
    USCI_ACLK,//ACLK
    USCI_SMCLK,//SMCLK
    USCI_SMCLK1//SMCLK

};
#endif
#if HSPI_EN>0


//HSPI初始化
//参数：
//  enum e_HSPIClkSource ClkSourceSel：时钟源选择
//  INT16U Div：分频数
//  BL CPHASel：CPHA
//  BL CPOLSel：CPOL
//  BL TxInterruptEN：使能中断
//返回：无
//注意：所有数据传输应放在初始化之后，包括其他USCIx0模块，因为初始化可能影响数据传输
void HSPIInit(enum e_USCIClkSource ClkSourceSel,INT16U Div,BL CPHASel,BL CPOLSel,BL TxInterruptEN,BL RxInterruptEN);
//HSPI等待数据发送完成（仅用于无中断模式）
#if HSPI_TX_INTERRUPT_EN==0
void HSPIWaitTransmit();
#endif
//HSPI设置回调函数
//参数：
//  void (*pFunc)()：回调函数
//返回：无
void HSPISetTxCallBack(void (*pFunc)());
//HSPI发送数据
//参数：
//  INT8U dat：数据
//返回：无
inline void HSPIWriteByte(INT8U dat);
#endif
#if UART_EN>0
//UART初始化
//参数：
//  enum e_HSPIClkSource ClkSourceSel：时钟源选择
//  INT16U Div：分频数
//  BL TxInterruptEN：使能中断
//返回：无
//注意：所有数据传输应放在初始化之后，包括其他USCIx0模块，因为初始化可能影响数据传输
void UARTInit(enum e_USCIClkSource ClkSourceSel,INT16U Div,BL TxInterruptEN,BL RxInterruptEN);
//UART等待数据发送完成（仅用于无中断模式）
#if UART_TX_INTERRUPT_EN==0
void UARTWaitTransmit();
#endif
//UART设置回调函数
//参数：
//  void (*pFunc)()：回调函数
//返回：无
void UARTSetTxCallBack(void (*pFunc)());
//UART发送数据
//参数：
//  INT8U dat：数据
//返回：无
inline void UARTWriteByte(INT8U dat);
#endif
#if IIC_EN>0
//IIC初始化
void IICInit();
#if IIC_TX_INTERRUPT_EN==0
//IIC等待数据发送完成（仅用于无中断模式）
BL IICWaitTransmit();
#endif
#if IIC_RX_INTERRUPT_EN==0
//IIC等待接收一个数据（仅用于无中断模式）
BL IICWaitReceive();
#endif
//IIC设置回调函数
//参数：
//  void (*pFunc)()：回调函数
//返回：无
void IICSetTxCallBack(void (*pFunc)());
//IIC设置回调函数
//参数：
//  void (*pFunc)()：回调函数
//返回：无
void IICSetRxCallBack(void (*pFunc)());
//IIC写入开始
void IICStartWrite();
//IIC读取开始
void IICStartRead();
//IIC停止
void IICStop();
//IICNoAck模式
void IICNoAckModeSet();
//IIC写入字节
inline void IICWriteByte(INT8U dat);
//IIC读取一个字节
inline INT8U IICReadByte();

#endif
#endif /* HSPI_H_ */
