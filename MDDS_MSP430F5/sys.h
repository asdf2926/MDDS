/*
 * sys.h
 *
 *  Created on: 2019年1月17日
 *      Author: asdf2
 */

#ifndef SYS_H_
#define SYS_H_
typedef unsigned char INT8U;
typedef signed char INT8S;
typedef unsigned short INT16U;
typedef short INT16S;
typedef unsigned long INT32U;
typedef long INT32S;
typedef unsigned long long INT64U;
typedef long long INT64S;
typedef unsigned char BL;

//typedef unsigned short size_t;
typedef struct{
    INT16U Year;
    INT8U Month;
    INT8U Date;
    INT8U Day; /* 0 = Sunday */
    INT8U Hour;
    INT8U Min;
    INT8U Sec;
    INT16U MSec;
} Time;
enum e_PowerPolicy{//电源策略
    Off,//关闭，所有部件停止，可用外部中断唤醒
    Stop,//停止，RTC模块运行，内存数据保持，端口保持，其余停止，可用外部中断唤醒
    Idle,//空闲，CPU停止
    LowPower,//低功耗（未实现）
    Normal,//正常（未实现）
    HighPerformance//高性能（未实现）
};

#define GPIOA                                                          1
#define GPIOB                                                          2
#define GPIOC                                                          3
#define GPIOD                                                          4
#define GPIOE                                                          5
#define GPIOF                                                          6
#define GPIOG                                                          7
#define GPIOH                                                          8
#define GPIOI                                                          9
#define GPIOJ                                                        10
#define GPIOK                                                        11

#define PIN0                                                      (0x0001)
#define PIN1                                                      (0x0002)
#define PIN2                                                      (0x0004)
#define PIN3                                                      (0x0008)
#define PIN4                                                      (0x0010)
#define PIN5                                                      (0x0020)
#define PIN6                                                      (0x0040)
#define PIN7                                                      (0x0080)
#define PIN8                                                      (0x0100)
#define PIN9                                                      (0x0200)
#define PIN10                                                     (0x0400)
#define PIN11                                                     (0x0800)
#define PIN12                                                     (0x1000)
#define PIN13                                                     (0x2000)
#define PIN14                                                     (0x4000)
#define PIN15                                                     (0x8000)
#define PIN_ALL8                                                    (0xFF)
#define PIN_ALL16                                                 (0xFFFF)

typedef INT64S UTime;
typedef INT16U Color;

#define _COMB_AB(a,b) __COMB_AB(a,b)//所有宏的参数在这层里全部展开
#define __COMB_AB(a,b) a##b
//系统初始化
//注意：此函数用于主函数进行初始化，并不应再调用其他初始化函数（特殊说明的除外）
void SystemInit();
//空闲处理
//注意：此函数不应在中断中调用
void IdleProcess();
#define SystemDelay(us) __delay_cycles(us)
void delay_10us(int count);
//#define GPIOWritePin(g,p,s) s?GPIO_setOutputHighOnPin(g,p):GPIO_setOutputLowOnPin(g,p)
#define GPIOReadPin(g,p) GPIO_getInputPinValue(g,p)

#endif /* SYS_H_ */
