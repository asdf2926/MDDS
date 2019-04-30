/*
 * HSPI.c
 *
 *  Created on: 2019年1月30日
 *      Author: asdf2
 */
#include <includes.h>
#define USCI_REG(a) _COMB_AB(HSPI_INTERFACE_NAME,a)// 转换宏

#if HSPI_INTERFACE==0
#define HSPI_INTERFACE_NAME UCA0
#else
#define HSPI_INTERFACE_NAME UCB0
#endif

#if UART_INTERFACE==0
#define UART_INTERFACE_NAME UCA0
#else
#error "USCIB doesn't support UART mode"
#define UART_INTERFACE_NAME UCB0
#endif

#if IIC_EN&&(IIC_INTERFACE==0)
#error "USCIB doesn't support IIC mode"
#endif

#if (HSPI_EN>0)&&(UART_EN>0)&&(UART_INTERFACE==HSPI_INTERFACE)
#error "USCI设备冲突"
#endif
#if (HSPI_EN>0)&&(IIC_EN>0)&&(IIC_INTERFACE==HSPI_INTERFACE)
#error "USCI设备冲突"
#endif


#if UARI_EN+HSPI_EN+IIC_EN>0
void (*CallBackFunc[4])();


INT16U Cnt[4]={0,0,0,0};

#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIInterruptT()
{
    if(IFG2&0x2)
    {
        IFG2&=~0x2;
        if(CallBackFunc[0]!=0){(*(CallBackFunc[0]))();}
        Cnt[0]+=1;
    }
    if(IFG2&0x8)
    {
        IFG2&=~0x8;
        if(CallBackFunc[1]!=0)(*(CallBackFunc[1]))();
        Cnt[1]+=1;

    }

}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIInterruptR()
{
    if(IFG2&0x1)
    {
        IFG2&=~0x1;
        if(CallBackFunc[2]!=0)(*(CallBackFunc[2]))();
        Cnt[2]+=1;
    }
    if(IFG2&0x4)
    {
        IFG2&=~0x4;
        if(CallBackFunc[3]!=0)(*(CallBackFunc[3]))();
        Cnt[3]+=1;

    }


}
#endif


#if HSPI_EN>0
//HPSI初始化
//参数：
//  enum e_HSPIClkSource ClkSourceSel：时钟源选择
//  INT16U Div：分频数
//  BL CPHASel：CPHA
//  BL CPOLSel：CPOL
//  BL TxInterruptEN：使能中断
//返回：无
//注意：所有数据传输应放在初始化之后，包括其他USCIx0模块，因为初始化可能影响数据传输
void HSPIInit(enum e_USCIClkSource ClkSourceSel,INT16U Div,BL CPHASel,BL CPOLSel,BL TxInterruptEN,BL RxInterruptEN)
{
    CallBackFunc[3]=CallBackFunc[2]=CallBackFunc[1]=CallBackFunc[0]=0;
    USCI_REG(CTL1)=(ClkSourceSel<<6)|1;//Reset UCSI
    USCI_REG(CTL0)=((HSPI_CPHA==0)<<7)|(HSPI_MSB_F<<5)|(CPOLSel<<6)|0x9;//8-bit data,Master Mode,3-pin SPI,Synchronous mode
    USCI_REG(BR0)=Div&0xff;
    USCI_REG(BR1)=Div>>8;
    USCI_REG(CTL1)&=0xfe;//

    if(TxInterruptEN)
    {
#if HSPI_INTERFACE==UCA0
        IE2|=0x2;
#else
        IE2|=0x8;
#endif
    }
    if(RxInterruptEN)
    {
#if HSPI_INTERFACE==UCA0
        IE2|=0x1;
#else
        IE2|=0x4;
#endif
    }
    IFG2=0;
}
//HSPI等待数据发送完成（仅用于无中断模式）
#if HSPI_TX_INTERRUPT_EN==0

void HSPIWaitTransmit()
{
#if HSPI_INTERFACE==0
    while((IFG2&0x2)==0);//PowerPolicySet(Idle);

#else
    while((IFG2&0x8)==0);//PowerPolicySet(Idle);


#endif
}
#endif
//HSPI设置回调函数
//参数：
//  void (*pFunc)()：回调函数
//返回：无

void HSPISetTxCallBack(void (*pFunc)())
{
    CallBackFunc[HSPI_INTERFACE]=pFunc;
}

void HSPISetRxCallBack(void (*pFunc)())
{
    CallBackFunc[HSPI_INTERFACE+2]=pFunc;
}

//HSPI发送数据
//参数：
//  INT8U dat：数据
//返回：无

inline void HSPIWriteByte(INT8U dat)
{
    USCI_REG(TXBUF)=dat;
}
#endif
//-----------------------------------------------------------------------------------------------
#if UART_EN>0
//UART初始化
//参数：
//  enum e_HSPIClkSource ClkSourceSel：时钟源选择
//  INT16U Div：分频数
//  BL TxInterruptEN：使能中断
//返回：无
//注意：所有数据传输应放在初始化之后，包括其他USCIx0模块，因为初始化可能影响数据传输
void UARTInit(enum e_USCIClkSource ClkSourceSel,INT16U Div,BL TxInterruptEN,BL RxInterruptEN)
{
    CallBackFunc[3]=CallBackFunc[2]=CallBackFunc[1]=CallBackFunc[0]=0;
    USCI_REG(CTL1)=(ClkSourceSel<<6)|1;//Reset UCSI
    USCI_REG(CTL0)=UART_MSB_F<<5;//校验禁止，8位数据，1位停止，UART模式
    USCI_REG(BR0)=Div&0xff;
    USCI_REG(BR1)=Div>>8;
    USCI_REG(CTL1)&=0xfe;//
    //MCTL=0禁止过采样
    if(TxInterruptEN)
    {
#if UART_INTERFACE==UCA0
        IE2|=0x2;
#else
        IE2|=0x8;
#endif
    }
    if(RxInterruptEN)
    {
#if UART_INTERFACE==UCA0
        IE2|=0x1;
#else
        IE2|=0x4;
#endif
    }
    IFG2=0;

}
//UART等待数据发送完成（仅用于无中断模式）
#if UART_TX_INTERRUPT_EN==0
void UARTWaitTransmit()
{
#if UART_INTERFACE==0
    while((IFG2&0x2)==0);//PowerPolicySet(Idle);

#else
    while((IFG2&0x8)==0);//PowerPolicySet(Idle);
#endif

}
#endif
//UART设置回调函数
//参数：
//  void (*pFunc)()：回调函数
//返回：无
void UARTSetTxCallBack(void (*pFunc)())
{
    CallBackFunc[UART_INTERFACE]=pFunc;

}
void UARTSetRxCallBack(void (*pFunc)())
{
    CallBackFunc[UART_INTERFACE+2]=pFunc;

}
//UART发送数据
//参数：
//  INT8U dat：数据
//返回：无
inline void UARTWriteByte(INT8U dat)
{
    USCI_REG(TXBUF)=dat;

}
#endif
#if IIC_EN>0
/******************************************************************************************************
 * 名       称：IICInit()
 * 功       能：初始化USCI_B0模块为I2C模式
 * 入口参数：无
 * 出口参数：无
 * 说       明：I2C设为2线制主机状态，使能Tx和Rx中断
 * 范       例：无
 ******************************************************************************************************/

void IICInit()
{
      UCB0CTL1 |= UCSWRST;                                           // 软件复位状态
      UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;   // 同步通信I2C主机状态
      UCB0CTL1 = UCSSEL_2 + UCSWRST;                     // 使用SMCLK，软件复位状态
      UCB0BR0 =IIC_BAUDRATE_DIV ;                          // 除了分频系数，实际波特率还与SMCLK有关
      UCB0BR1 = 0;                                                      //这一级别的分频一般不启用
      UCB0I2CSA = IIC_SLAVE_ADDR;                               // I2C从机地址，可在宏定义中修改
      UCB0CTL1 &= ~UCSWRST;                                     // 开启I2C
#if IIC_TX_INTERRUPT_EN
      IE2 |= UCB0TXIE;                                  //允许Tx中断
#endif
#if IIC_RX_INTERRUPT_EN
      IE2 |= UCB0RXIE;                                  //允许Rx中断
#endif
}
#if IIC_TX_INTERRUPT_EN==0
BL IICWaitTransmit()
{
    while((IFG2&0x8)==0)//PowerPolicySet(Idle);
    {
        if((UCB0STAT&UCBBUSY)==0)return 1;
        if((UCB0STAT&UCNACKIFG)>0)
        {
            UCB0CTL1|=UCTXSTP;
            return 1;
        }
    }
    IFG2&=0xf7;
    return 0;
}

BL IICWaitReceive()
{
    while((IFG2&0x4)==0)//PowerPolicySet(Idle);
    {
        if((UCB0STAT&UCSTPIFG)>0)
            return 1;

    }
    IFG2&=0xfb;
    return 0;
}
#endif
void IICSetTxCallBack(void (*pFunc)())
{
    CallBackFunc[IIC_INTERFACE]=pFunc;
}
void IICSetRxCallBack(void (*pFunc)())
{
    CallBackFunc[IIC_INTERFACE+2]=pFunc;
}
inline void IICWriteByte(INT8U dat)
{
    if(UCB0STAT&UCBBUSY) UCB0TXBUF = dat;
}
inline INT8U IICReadByte()
{
    return UCB0RXBUF;
}
void IICStartWrite()
{
    UCB0CTL1 |= UCTR;
    UCB0CTL1 |= UCTXSTT;
    IFG2&=0xf7;

}
void IICStartRead()
{
    UCB0CTL1 &= ~UCTR;
    UCB0CTL1 |= UCTXSTT;
    IFG2&=0xfb;

}
void IICStop()
{
    if(UCB0STAT&UCBBUSY)UCB0CTL1 |= UCTXSTP;
}
void IICNoAckModeSet()
{
    UCB0CTL1 |=UCNACKIFG;
}
#endif
