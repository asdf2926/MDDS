
#include <stdint.h>
#include <stdbool.h>

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
//-------------------------------------------------------------
#define PIN0 1
#define PIN1 2
#define PIN2 4
#define PIN3 8
#define PIN4 0x10
#define PIN5 0x20
#define PIN6 0x40
#define PIN7 0x80
#define PIN8 0x100
#define PIN9 0x200
#define PIN10 0x400
#define PIN11 0x800
#define PIN12 0x1000
#define PIN13 0x2000
#define PIN14 0x4000
#define PIN15 0x8000
//-------------------------------------------------------------
#define GetTimeStampRaw() MAP_SysTickValueGet()
#define GPIOWrite(port,pin,state) port->DATA=(state)?port->DATA|(pin):port->DATA&~(pin)
void Delay_ms(INT32U time_ms);

