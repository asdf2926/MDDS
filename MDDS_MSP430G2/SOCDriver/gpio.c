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
    //P1
    GPIOOutPutMode[0]=(((P1_7_MODE&0x08)>0)<<7)|(((P1_6_MODE&0x08)>0)<<6)|(((P1_5_MODE&0x08)>0)<<5)|(((P1_4_MODE&0x08)>0)<<4)|(((P1_3_MODE&0x08)>0)<<3)|(((P1_2_MODE&0x08)>0)<<2)|(((P1_1_MODE&0x08)>0)<<1)|(((P1_0_MODE&0x08)>0));
    P1DIR=0;
    GPIOWrite(GPIOA,P1_OUTPUT);


    P1DIR|=((P1_7_MODE&0x01)<<7)|((P1_6_MODE&0x01)<<6)|((P1_5_MODE&0x01)<<5)|((P1_4_MODE&0x01)<<4)|((P1_3_MODE&0x01)<<3)|((P1_2_MODE&0x01)<<2)|((P1_1_MODE&0x01)<<1)|(P1_0_MODE&0x01);
    P1IES=(((P1_7_MODE&0x04)>0)<<7)|(((P1_6_MODE&0x04)>0)<<6)|(((P1_5_MODE&0x04)>0)<<5)|(((P1_4_MODE&0x04)>0)<<4)|(((P1_3_MODE&0x04)>0)<<3)|(((P1_2_MODE&0x04)>0)<<2)|(((P1_1_MODE&0x04)>0)<<1)|(((P1_0_MODE&0x04)>0));
    P1IE=(((P1_7_MODE&0x02)>0)<<7)|(((P1_6_MODE&0x02)>0)<<6)|(((P1_5_MODE&0x02)>0)<<5)|(((P1_4_MODE&0x02)>0)<<4)|(((P1_3_MODE&0x02)>0)<<3)|(((P1_2_MODE&0x02)>0)<<2)|(((P1_1_MODE&0x02)>0)<<1)|(((P1_0_MODE&0x02)>0));
    P1SEL=(((P1_7_MODE&0x10)>0)<<7)|(((P1_6_MODE&0x10)>0)<<6)|(((P1_5_MODE&0x10)>0)<<5)|(((P1_4_MODE&0x10)>0)<<4)|(((P1_3_MODE&0x10)>0)<<3)|(((P1_2_MODE&0x10)>0)<<2)|(((P1_1_MODE&0x10)>0)<<1)|(((P1_0_MODE&0x10)>0));
    P1SEL2=(((P1_7_MODE&0x20)>0)<<7)|(((P1_6_MODE&0x20)>0)<<6)|(((P1_5_MODE&0x20)>0)<<5)|(((P1_4_MODE&0x20)>0)<<4)|(((P1_3_MODE&0x20)>0)<<3)|(((P1_2_MODE&0x20)>0)<<2)|(((P1_1_MODE&0x20)>0)<<1)|(((P1_0_MODE&0x20)>0));

    //P2

    GPIOOutPutMode[1]=(((P2_7_MODE&0x08)>0)<<7)|(((P2_6_MODE&0x08)>0)<<6)|(((P2_5_MODE&0x08)>0)<<5)|(((P2_4_MODE&0x08)>0)<<4)|(((P2_3_MODE&0x08)>0)<<3)|(((P2_2_MODE&0x08)>0)<<2)|(((P2_1_MODE&0x08)>0)<<1)|(((P2_0_MODE&0x08)>0));
    P2DIR=0;
    GPIOWrite(GPIOB,P2_OUTPUT);


    P2DIR|=((P2_7_MODE&0x01)<<7)|((P2_6_MODE&0x01)<<6)|((P2_5_MODE&0x01)<<5)|((P2_4_MODE&0x01)<<4)|((P2_3_MODE&0x01)<<3)|((P2_2_MODE&0x01)<<2)|((P2_1_MODE&0x01)<<1)|(P2_0_MODE&0x01);
    P2IES=(((P2_7_MODE&0x04)>0)<<7)|(((P2_6_MODE&0x04)>0)<<6)|(((P2_5_MODE&0x04)>0)<<5)|(((P2_4_MODE&0x04)>0)<<4)|(((P2_3_MODE&0x04)>0)<<3)|(((P2_2_MODE&0x04)>0)<<2)|(((P2_1_MODE&0x04)>0)<<1)|(((P2_0_MODE&0x04)>0));
    P2IE=(((P2_7_MODE&0x02)>0)<<7)|(((P2_6_MODE&0x02)>0)<<6)|(((P2_5_MODE&0x02)>0)<<5)|(((P2_4_MODE&0x02)>0)<<4)|(((P2_3_MODE&0x02)>0)<<3)|(((P2_2_MODE&0x02)>0)<<2)|(((P2_1_MODE&0x02)>0)<<1)|(((P2_0_MODE&0x02)>0));
    P2SEL=(((P2_7_MODE&0x10)>0)<<7)|(((P2_6_MODE&0x10)>0)<<6)|(((P2_5_MODE&0x10)>0)<<5)|(((P2_4_MODE&0x10)>0)<<4)|(((P2_3_MODE&0x10)>0)<<3)|(((P2_2_MODE&0x10)>0)<<2)|(((P2_1_MODE&0x10)>0)<<1)|(((P2_0_MODE&0x10)>0));
    P2SEL=(((P2_7_MODE&0x20)>0)<<7)|(((P2_6_MODE&0x20)>0)<<6)|(((P2_5_MODE&0x20)>0)<<5)|(((P2_4_MODE&0x20)>0)<<4)|(((P2_3_MODE&0x20)>0)<<3)|(((P2_2_MODE&0x20)>0)<<2)|(((P2_1_MODE&0x20)>0)<<1)|(((P2_0_MODE&0x20)>0));

    P3DIR=0xFF;

}

void GPIOWrite(enum e_GPIOGroup Group,INT8U data)
{
    //推挽输出：DIR=1，OUT=data
    //开漏输出：DIR=0，OUT=任意
    if(Group==GPIOA)
    {
        P1DIR&=~(data&GPIOOutPutMode[0]);
        P1OUT=data;
        P1DIR|=(~data)&GPIOOutPutMode[0];
    }else{
        P2DIR&=~(data&GPIOOutPutMode[1]);
        P2OUT=data;
        P2DIR|=(~data)&GPIOOutPutMode[1];

    }
}

void GPIOWritePin(enum e_GPIOGroup Group,INT8U PinMask,BL Statu)
{
    //推挽输出：DIR=1，OUT=data
    //开漏输出：DIR=0，OUT=任意
    if(Group==GPIOA)
    {
        P1DIR&=Statu?~(PinMask&GPIOOutPutMode[0]):0xff;
        P1OUT&=Statu?0xff:~PinMask;
        P1OUT|=Statu?PinMask:0;
        P1DIR|=Statu?0:PinMask&GPIOOutPutMode[0];
    }else{
        P2DIR&=Statu?~(PinMask&GPIOOutPutMode[1]):0xff;
        P2OUT&=Statu?0xff:~PinMask;
        P2OUT|=Statu?PinMask:0;
        P2DIR|=Statu?0:PinMask&GPIOOutPutMode[1];

    }

}

inline void GPIOWritePinF(enum e_GPIOGroup Group,INT8U PinMask,BL Statu)
{
    if(Group==GPIOA)
    {
        P1OUT&=Statu?0xff:~PinMask;
        P1OUT|=Statu?PinMask:0;
    }else{
        P2OUT&=Statu?0xff:~PinMask;
        P2OUT|=Statu?PinMask:0;

    }
}

INT8U GPIORead(enum e_GPIOGroup Group)
{
    if(Group==GPIOA)
    {
      return P1IN;
    }else{
      return P2IN;

    }

}

BL GPIOReadPin(enum e_GPIOGroup Group,INT8U PinMask)
{
    if(Group==GPIOA)
    {
      return (P1IN&PinMask)>0;
    }else{
      return (P2IN&PinMask)>0;

    }

}

void GPIOSetMode(enum e_GPIOGroup Group,INT8U PinMask,enum e_GPIOPinMode Mode)
{
    if(Group==GPIOA)
    {
        if(Mode&0x10)
        {
            P1SEL|=PinMask;//第二功能
        }else
        {
            P1SEL&=~PinMask;
        }
        if(Mode&8)
         {
            GPIOOutPutMode[0]|=PinMask;//开漏输出
            GPIOWrite(GPIOA,P1OUT);
         }else
         {
             GPIOOutPutMode[0]&=~PinMask;
         }
        if(Mode&4)
         {
             P1IES|=PinMask;//中断下降沿
         }else
         {
             P1IES&=~PinMask;
         }
        if(Mode&2)
         {
            P1IE|=PinMask;//使能中断
         }else
         {
             P1IE&=~PinMask;
         }
        if(Mode&1)
         {
            if(Mode&8==0)P1DIR|=PinMask;//输出模式
         }else
         {
             P1DIR&=~PinMask;
         }


    }else{

        if(Mode&0x10)
         {
             P2SEL|=PinMask;//第二功能
         }else
         {
             P2SEL&=~PinMask;
         }
         if(Mode&8)
          {
             GPIOOutPutMode[1]|=PinMask;//开漏输出
             GPIOWrite(GPIOB,P2OUT);
          }else
          {
              GPIOOutPutMode[1]&=~PinMask;
          }
         if(Mode&4)
          {
              P2IES|=PinMask;//中断下降沿
          }else
          {
              P2IES&=~PinMask;
          }
         if(Mode&2)
          {
             P2IE|=PinMask;//使能中断
          }else
          {
              P2IE&=~PinMask;
          }
         if(Mode&1)
          {
             if(Mode&8==0)P2DIR|=PinMask;//输出模式
          }else
          {
              P2DIR&=~PinMask;
          }




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

#pragma vector = PORT2_VECTOR
__interrupt void P2_Interrupt()
{
    INT8U i;
    for(i=0;i<8;i++)
    {
        if(P2IFG&(1<<i))
        {
            P2IFG&=~(1<<i);
            GPIOISR(GPIOB,i);

        }
    }
}
