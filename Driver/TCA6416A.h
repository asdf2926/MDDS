/*
 * TCA6416A.h
 *
 *  Created on: 2019年3月2日
 *      Author: asdf2
 */

#ifndef DRIVER_TCA6416A_H_
#define DRIVER_TCA6416A_H_
#if TCA6416A_EN>0
//初始化
//参数：无
//返回：无
void TCA6416A_Init(void);
//写IO
//参数：Group:GPIOA或GPIOB
//    data:数据（8位）
void EXIOWrite(enum e_GPIOGroup Group,INT8U dat);
//写IO部分位
//参数：Group:GPIOA或GPIOB
//    PinMask:PIN0~7及它们的组合
//    Statu:值(0/1)
void EXIOWritePin(enum e_GPIOGroup Group,INT8U PinMask,BL Statu);
//读IO
//参数：Group:GPIOA或GPIOB
//返回值：数据
INT8U EXIORead(enum e_GPIOGroup Group);
//读IO部分位
//参数：Group:GPIOA或GPIOB
//    PinMask:PIN0~7及它们的组合
//返回值：状态（0/1）
BL EXIOReadPin(enum e_GPIOGroup Group,INT8U PinMask);

#endif

#endif /* DRIVER_TCA6416A_H_ */
