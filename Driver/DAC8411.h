/*
 * DAC8411.h
 *
 *  Created on: 2019年3月2日
 *      Author: asdf2
 */

#ifndef DRIVER_DAC8411_H_
#define DRIVER_DAC8411_H_

#if DAC8411_EN>0
void DAC8411Init();//初始化
//写数据
//参数：INT16U Data ：数据
//返回：无
void DAC8411Write(INT16U Data);
//自动写入初始化
//参数：const INT16U *dat：数据地址
//			size_t len：长度
//返回：无
void DAC8411AutoWriteInit(const INT16U *dat,size_t len);
//自动写入执行函数
//进行实际的DAC写入，常常作为定时器的回调函数
//参数：无
//返回：无
void DAC8411AutoWrite();

#endif
#endif /* DRIVER_DAC8411_H_ */
