/*
 * TCA6416A.c
 *
 *  Created on: 2019年2月28日
 *      Author: asdf2
 */
#include "includes.h"
#if TCA6416A_EN>0
//-----控制寄存器定义-----
#define		In_CMD0			0x00	//读取管脚输入状态寄存器；只读
#define		In_CMD1			0x01
#define		Out_CMD0		0x02	//控制管脚输出状态寄存器；R/W
#define		Out_CMD1		0x03
#define		PIVS_CMD0		0x04	//反向控制管脚输出状态寄存器；R/W
#define		PIVS_CMD1		0x05
#define		CFG_CMD0		0x06	//管脚方向控制：1：In；0:：Out。
#define		CFG_CMD1		0x07

#define GETIF(a) _COMB_AB(TCA6416A_INTERFACE,a)

INT8U InputReg[2];
unsigned char pinW0 = TCA6416A_PORT_0_OUT;		//用于缓存已写入相应管脚的状态信息，此操作避免读回TCA6416A中当前寄存器的值
unsigned char pinW1 = TCA6416A_PORT_1_OUT;		//用于缓存已写入相应管脚的状态信息，此操作避免读回TCA6416A中当前寄存器的值
/******************************************************************************************************
 * 名       称：TCA6416AInit()
 * 功       能：TCA6416A初始化，
 * 入口参数：无
 * 出口参数：无
 * 说       明：实际是调用I2C初始化程序，将TCA6416A的输入输出口做定义
 * 范       例：无
 ******************************************************************************************************/
void TCA6416A_Init(void)
{
    BL isfail;
	//unsigned char conf[3]={0};
	 __delay_cycles(100000);			//TCA6416的复位时间比单片机长，延迟确保可靠复位
	//----根据扩展板的引脚使用，将按键所在管脚初始化为输入，其余管脚初始化为输出
	 do{
	 isfail=0;
	GETIF(StartWrite)();
	GETIF(WriteByte)(CFG_CMD0);         //TCA6416控制寄存器
	isfail|=GETIF(WaitTransmit)();
	GETIF(WriteByte)(TCA6416A_PORT_0_DIR);	//  0 0 0 0_0 0 0 0  （LED0~LED7）
	isfail|=GETIF(WaitTransmit)();
	GETIF(WriteByte)(TCA6416A_PORT_1_DIR);						//  0 0 0 0_1 1 1 1 (按键)
	isfail|=GETIF(WaitTransmit)();

	GETIF(Stop)();
	 }while(isfail);
//	GETIF(StartWrite)();


//	GETIF(WriteByte)(CFG_CMD1);
//	GETIF(WaitTransmit)();
//	GETIF(WriteByte)(TCA6416A_PORT_1_DIR);						//  0 0 0 0_1 1 1 1 (按键)
//	GETIF(WaitTransmit)();
//	GETIF(Stop)();
	 do{
	 isfail=0;
	GETIF(StartWrite)();

	//----上电先将管脚输出为高（此操作对输入管脚无效）
	GETIF(WriteByte)(Out_CMD0);
	isfail|=GETIF(WaitTransmit)();
	GETIF(WriteByte)(TCA6416A_PORT_0_OUT);						// 某位置1，输出为高，0为低
	isfail|=GETIF(WaitTransmit)();
	GETIF(WriteByte)(TCA6416A_PORT_1_OUT);
	isfail|=GETIF(WaitTransmit)();

//	GETIF(Stop)();
//	GETIF(StartWrite)();

//	GETIF(WriteByte)(Out_CMD1);
//	GETIF(WaitTransmit)();
//	GETIF(WriteByte)(TCA6416A_PORT_1_OUT);
//	GETIF(WaitTransmit)();
	GETIF(Stop)();
	 }while(isfail);
}
/******************************************************************************************************
 * 名       称：EXIOWrite()
 * 功       能：控制TCA6416指定port输出指定电平
 * 入口参数：enum e_GPIOGroup Group,INT8U data
 * 出口参数：无
 * 说       明：无
 * 范       例：无
 ******************************************************************************************************/
inline void EXIOSync(enum e_GPIOGroup Group)
{
    BL isfail;
    do{
    isfail=0;
	GETIF(StartWrite)();
	GETIF(WriteByte)((Group==GPIOA)?Out_CMD0:Out_CMD1);
	isfail|=GETIF(WaitTransmit)();
	GETIF(WriteByte)((Group==GPIOA)?pinW0:pinW1);
	isfail|=GETIF(WaitTransmit)();
	GETIF(Stop)();
	 }while(isfail);
}
void EXIOWrite(enum e_GPIOGroup Group,INT8U dat)
{
	if(Group==GPIOA)pinW0=dat;
	else pinW1=dat;
	EXIOSync(Group);
}
void EXIOWritePin(enum e_GPIOGroup Group,INT8U PinMask,BL Statu)
{
    INT8U r;
    r=(Group==GPIOA)?pinW0:pinW1;
    if(Statu)r|=PinMask;
    else r&=~PinMask;
	if(Group==GPIOA)pinW0=r;
	else pinW1=r;
	EXIOSync(Group);
	EXIOSync(Group);

}
void EXIORSync()
{
    BL isfail;
    do{
    isfail=0;
    GETIF(StartWrite)();
	GETIF(WriteByte)(In_CMD1);
	isfail|=GETIF(WaitTransmit)();
	GETIF(StartRead)();
	isfail|=GETIF(WaitReceive)();
	InputReg[1]=GETIF(ReadByte)();
	GETIF(NoAckModeSet)();
	isfail|=GETIF(WaitReceive)();
	InputReg[0]=GETIF(ReadByte)();
	GETIF(Stop)();
	 }while(isfail);
}

INT8U EXIORead(enum e_GPIOGroup Group)
{
    EXIORSync();
    return InputReg[Group!=GPIOA];
}
BL EXIOReadPin(enum e_GPIOGroup Group,INT8U PinMask)
{
    EXIORSync();
    return (InputReg[Group!=GPIOA]&PinMask)>0;
}

#endif

