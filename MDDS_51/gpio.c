/*
 * gpio.c
 *
 *  Created on: 2019年1月19日
 *      Author: asdf2
 */
#include <includes.h>
INT8U GPIOOutPutMode[2];

void GPIOInit()
{
}

void GPIOWrite(enum e_GPIOGroup Group,INT8U data)
{
    if(Group==GPIOA)
    {
        P0=data;
    }
}

void GPIOWritePin(enum e_GPIOGroup Group,INT8U PinMask,BL Statu)
{
    if(Group==GPIOA)
    {
        P0&=Statu?0xff:~PinMask;
        P0|=Statu?PinMask:0;
    }else if()
    {
        P1&=Statu?0xff:~PinMask;
        P1|=Statu?PinMask:0;
    }

}
INT8U GPIORead(enum e_GPIOGroup Group)
{
    if(Group==GPIOA)
    {
      return P0;
    }
    else if()
    {
        return P1;
    }

}

BL GPIOReadPin(enum e_GPIOGroup Group,INT8U PinMask)
{
    if(Group==GPIOA)
    {
      return (P0&PinMask)>0;
    }
    else if()
    {
    return (P1&PinMask)>0;
    }

}
#pragma vector = PORT1_VECTOR
__interrupt void P1_Interrupt()
{
    INT8U i;
    for(i=0;i<8;i++)
    {
        if(P1IFG&(1<<i))
        {
            P1IFG&=~(1<<i);
            GPIOISR(GPIOA,i);

        }
    }
}
