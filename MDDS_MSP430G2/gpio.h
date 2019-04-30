/*
 * gpio.h
 *
 *  Created on: 2019年1月19日
 *      Author: asdf2
 */

#ifndef GPIO_H_
#define GPIO_H_
enum e_GPIOPinMode{
//basic 基本模式，二选一
 PINMODE_OUTPUT=1,//输出模式
 PINMODE_INPUT=0,//输入模式
//additional 额外的模式
 PINMODE_OUTPUT_OD=8,//开漏输出（仅输出低电平）
 PINMODE_INPUT_INT_R=2,//上升沿中断
 PINMODE_INPUT_INT_F=6,//下降沿中断
 PINMODE_SELECT=0x10,//第二功能
 PINMODE_SELECT2=0x30//第二功能

};
//各位意义：4:第二功能 3:输出模式 2:中断边沿 1:中断使能 0:IN/OUT
enum e_GPIOGroup
{
    GPIOA,//P1
    GPIOB//P2
};
//GPIOA：P1，GPIOB：P2

//位掩码
#define PIN0 1
#define PIN1 2
#define PIN2 4
#define PIN3 8
#define PIN4 0x10
#define PIN5 0x20
#define PIN6 0x40
#define PIN7 0x80
//以conf.h初始化GPIO，
void GPIOInit();
//写GPIO
//参数：Group:GPIOA或GPIOB
//    data:数据（8位）
void GPIOWrite(enum e_GPIOGroup Group,INT8U data);
//写GPIO部分位
//参数：Group:GPIOA或GPIOB
//    PinMask:PIN0~7及它们的组合
//    Statu:值(0/1)
void GPIOWritePin(enum e_GPIOGroup Group,INT8U PinMask,BL Statu);
//快速版本，但不支持开漏输出
inline void GPIOWritePinF(enum e_GPIOGroup Group,INT8U PinMask,BL Statu);
//读GPIO
//参数：Group:GPIOA或GPIOB
//返回值：数据
INT8U GPIORead(enum e_GPIOGroup Group);
//读GPIO部分位
//参数：Group:GPIOA或GPIOB
//    PinMask:PIN0~7及它们的组合
//返回值：状态（0/1）
BL GPIOReadPin(enum e_GPIOGroup Group,INT8U PinMask);
//设置GPIO模式
//参数：Group:GPIOA或GPIOB
//    PinMask:PIN0~7及它们的组合
//    Mode:模式
void GPIOSetMode(enum e_GPIOGroup Group,INT8U PinMask,enum e_GPIOPinMode Mode);
//中断处理程序
//应由用户定义
//参数：Group:GPIOA或GPIOB
//    Pin:0~7
void GPIOISR(enum e_GPIOGroup Group,INT8U Pin);

#endif /* GPIO_H_ */
