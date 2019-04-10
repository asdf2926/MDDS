/*
 * SSPI.h
 *
 *  Created on: 2019年1月31日
 *      Author: asdf2
 */

#ifndef DRIVER_SSPI_H_
#define DRIVER_SSPI_H_
#if SSPI_EN>0
//初始化SSPI（无作用）
inline void SSPIInit();
//SSPI发送数据
//参数：
//  INT8U dat：数据
//返回：无
//SPI模式3，MSB First
//CPOL=1
//CPHA=1
void SSPIWriteByte(INT8U dat);
//SSPI等待数据发送完成（无作用）
inline void SSPIWaitTransmit(){}
#endif
#endif /* DRIVER_SSPI_H_ */
