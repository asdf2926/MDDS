#ifndef SYS_H_
#define SYS_H_
#define assert(a)
#define PLATFORM_STM32
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
    INT8U Month;//1~12
    INT8U Date;
    INT8U Day; /* 0 = Sunday */
    INT8U Hour;
    INT8U Min;
    INT8U Sec;
    INT16U MSec;
} Time;
typedef INT64S UTime;
typedef INT32U Color;

#define _COMB_AB(a,b) __COMB_AB(a,b)//??????????????
#define __COMB_AB(a,b) a##b
//?????
//??:?????????????,?????????????(???????)
void SystemInit(void);
//????
//??:???????????
void IdleProcess(void);
#define SystemDelay(us) HAL_Delay((us+999)/1000)
#endif /* SYS_H_ */

