/*
 * conf.h
 *
 *  Created on: 2019年5月1日
 *      Author: asdf2
 */

#ifndef CONF_H_
#define CONF_H_

//----------------------------IO口模式---------------------------------
#define P1_OUTPUT_PIN PIN1|PIN2|PIN3
#define P2_OUTPUT_PIN PIN1|PIN2|PIN3
#define P3_OUTPUT_PIN PIN1|PIN2|PIN3
#define P4_OUTPUT_PIN PIN1|PIN2|PIN3
#define P5_OUTPUT_PIN PIN1|PIN2|PIN3
#define P6_OUTPUT_PIN PIN1|PIN2|PIN3
#define P7_OUTPUT_PIN PIN1|PIN2|PIN3
#define P8_OUTPUT_PIN PIN1|PIN2|PIN3
#define P9_OUTPUT_PIN PIN1|PIN2|PIN3
#define P10_OUTPUT_PIN PIN1|PIN2|PIN3
#define P11_OUTPUT_PIN PIN1|PIN2|PIN3

#define P1_INPUT_PIN PIN1|PIN2|PIN3
#define P2_INPUT_PIN PIN1|PIN2|PIN3
#define P3_INPUT_PIN PIN1|PIN2|PIN3
#define P4_INPUT_PIN PIN1|PIN2|PIN3
#define P5_INPUT_PIN PIN1|PIN2|PIN3
#define P6_INPUT_PIN PIN1|PIN2|PIN3
#define P7_INPUT_PIN PIN1|PIN2|PIN3
#define P8_INPUT_PIN PIN1|PIN2|PIN3
#define P9_INPUT_PIN PIN1|PIN2|PIN3
#define P10_INPUT_PIN PIN1|PIN2|PIN3
#define P11_INPUT_PIN PIN1|PIN2|PIN3

#define P1_OUTPUT_FUNC_PIN PIN1|PIN2|PIN3
#define P2_OUTPUT_FUNC_PIN PIN1|PIN2|PIN3
#define P3_OUTPUT_FUNC_PIN PIN1|PIN2|PIN3
#define P4_OUTPUT_FUNC_PIN PIN1|PIN2|PIN3
#define P5_OUTPUT_FUNC_PIN PIN1|PIN2|PIN3
#define P6_OUTPUT_FUNC_PIN PIN1|PIN2|PIN3
#define P7_OUTPUT_FUNC_PIN PIN1|PIN2|PIN3
#define P8_OUTPUT_FUNC_PIN PIN1|PIN2|PIN3
#define P9_OUTPUT_FUNC_PIN PIN1|PIN2|PIN3
#define P10_OUTPUT_FUNC_PIN PIN1|PIN2|PIN3
#define P11_OUTPUT_FUNC_PIN PIN1|PIN2|PIN3

#define P1_INPUT_FUNC_PIN PIN1|PIN2|PIN3
#define P2_INPUT_FUNC_PIN PIN1|PIN2|PIN3
#define P3_INPUT_FUNC_PIN PIN1|PIN2|PIN3
#define P4_INPUT_FUNC_PIN PIN1|PIN2|PIN3
#define P5_INPUT_FUNC_PIN PIN1|PIN2|PIN3
#define P6_INPUT_FUNC_PIN PIN1|PIN2|PIN3
#define P7_INPUT_FUNC_PIN PIN1|PIN2|PIN3
#define P8_INPUT_FUNC_PIN PIN1|PIN2|PIN3
#define P9_INPUT_FUNC_PIN PIN1|PIN2|PIN3
#define P10_INPUT_FUNC_PIN PIN1|PIN2|PIN3
#define P11_INPUT_FUNC_PIN PIN1|PIN2|PIN3

//#define P1_INTERRUPT_PIN PIN1|PIN2|PIN3
//#define P2_INTERRUPT_PIN PIN1|PIN2|PIN3

//-------------------------定时器设置-----------------------------------------

//-------------------------HSPI------------------------------------------
//-------------------------UART------------------------------------------
//-------------------------IIC-------------------------------------------
//-------------------------Basic Timer-----------------------------------
#define BTIMER_COUNT 3
#if BTIMER_COUNT>0
#define BTIMER_INTERFACE Timer1A
#endif

//--------------------------RTC------------------------------------------
//--------------------------ADC-----------------------------------------
//--------------------------DMA-----------------------------------------
#endif /* CONF_H_ */
