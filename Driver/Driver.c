/*
 * Driver.c
 *
 *  Created on: 2019年2月1日
 *      Author: asdf2
 */
#include "includes.h"
void DriverInit()
{
#if SSPI_EN>0
    SSPIInit();
#endif
#if LCD_EN>0
    LCDInit();
#endif
#if TCA6416A_EN>0
    TCA6416A_Init();
#endif
#if HT1621_EN>0
    HT1621Init();
#endif
#if DAC8411_EN>0
    DAC8411Init();
#endif
#if TFT_EN>0
	TFT_Init();
	TFT_Clear(TFT_INIT_COLOR);
#endif
}

void DriverDeInit()
{
#if LCD_EN>0
    LCDDeInit();
#endif
	
	
}
