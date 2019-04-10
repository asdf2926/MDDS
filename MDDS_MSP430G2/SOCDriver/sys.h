/*
 * sys.h
 *
 *  Created on: 2019年1月17日
 *      Author: asdf2
 */

#ifndef SYS_H_
#define SYS_H_
#define assert(a)
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

typedef INT64S UTime;

#define _COMB_AB(a,b) __COMB_AB(a,b)//所有宏的参数在这层里全部展开
#define __COMB_AB(a,b) a##b
//系统初始化
//注意：此函数用于主函数进行初始化，并不应再调用其他初始化函数（特殊说明的除外）
void SystemInit();
//空闲处理
//注意：此函数不应在中断中调用
void IdleProcess();
#define SystemDelay(us) __delay_cycles(us)
#endif /* SYS_H_ */
