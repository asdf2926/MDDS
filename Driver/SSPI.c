/*
 * SSPI.c
 *
 *  Created on: 2019年1月31日
 *      Author: asdf2
 */
#include <includes.h>
#if SSPI_EN>0
//初始化SSPI（无作用）
inline void SSPIInit()
{

}

//SSPI发送数据
//参数：
//  INT8U dat：数据
//返回：无
//SPI模式3，MSB First
//CPOL=1
//CPHA=1
void SSPIWriteByte(INT8U dat)
{
    INT8U i;
    for(i=0;i<8;i++)
    {
       GPIOWritePin(SSPI_CK ,1);
       GPIOWritePin(SSPI_MOSI,(dat>>(7-i))&1);
       GPIOWritePin(SSPI_CK ,0);

    }
    GPIOWritePin(SSPI_CK ,1);
}
#endif
