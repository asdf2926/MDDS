/*
 * conf_ext.h
 *
 *  Created on: 2019年1月30日
 *      Author: asdf2
 */

#ifndef CONF_EXT_H_
#define CONF_EXT_H_
//SSPI--------------------------------------------------------
#define SSPI_EN 0
#if SSPI_EN>0
//SSPI固定为SPI模式3，MSB First
//CPOL=1
//CPHA=1
#define SSPI_CK GPIOA,PIN4      //SCK引脚，为GPIOx,PINx的二元组
#define SSPI_MOSI  GPIOA,PIN2   //MOSI引脚，为GPIOx,PINx的二元组
#endif
//LX_12864----------------------------------------------------
#define LCD_EN 0
#if LCD_EN>0
#define LCD_DRIVER HSPI         //LCD接口驱动，取值有HSPI和SSPI
#define LCD_INTR_EN 1           //LCD数据传输由中断控制
#define LCD_DMA_EN 0
#define LCD_BUF_SIZE 40         //LCD缓冲区大小，仅在中断模式时有效
#define LCD_RST_PIN GPIOA,PIN0  //RST引脚号，为GPIOx,PINx的二元组
#define LCD_CS_PIN GPIOA,PIN6  //CS引脚号，为GPIOx,PINx的二元组
#define LCD_A0_PIN GPIOA,PIN7  //A0引脚号，为GPIOx,PINx的二元组

//SCLK->P1.4
//MOSI->P1.2
#define LCD_INIT_FILL_DATA 0x55

#define LCD_BUFFER_EN 1//ÆôÓÃLCDÈ«ÆÁË¢ÐÂÄ£Ê½£»»º³åÇø1KBÓÉÓÃ»§¶¨Òå

#endif
//--------------------------TCA6416A---------------------------
#define TCA6416A_EN 1//使能
#if TCA6416A_EN>0
#define TCA6416A_INTERFACE IIC //IIC only
#define TCA6416A_PORT_0_DIR 0//GPIOA（P0口）模式：0=输出，1=输入，
#define TCA6416A_PORT_1_DIR 0x0f//GPIOB（P1口）模式：0=输出，1=输入
#define TCA6416A_PORT_0_OUT 0xaa//GPIOA（P0口）数据
#define TCA6416A_PORT_1_OUT 0xff//GPIOB（P1口）数据
#endif
//-------------------------HT1621-----------------------------
#define HT1621_EN 1//使能
#if HT1621_EN>0
#define HT1621_INTERFACE EXIO//驱动接口（GPIO或EXIO）
#define HT1621_CS_PIN       GPIOB,PIN4//片选端
#define HT1621_RD_PIN       GPIOB,PIN5//not necessary,always 1，若未定义，则不使用
#define HT1621_WR_PIN   	GPIOB,PIN6//写入使能
#define HT1621_DATA_PIN     GPIOB,PIN7//数据引脚
#endif
//-------------------------SegLCD_G2--------------------------
#if HT1621_EN>0
#define SegLCD_G2_EN 1
#endif
//-------------------------DAC8411----------------------------
#define DAC8411_EN 0
#if DAC8411_EN>0
#define SYNC_HIGH       P1OUT |=BIT0//SYNC信号写1
#define SYNC_LOW        P1OUT &=~BIT0//SYNC信号写0
#define SCLK_HIGH       P2OUT |=BIT2//SCLK信号写1
#define SCLK_LOW        P2OUT &=~BIT2//SCLK信号写0
#define DIN_HIGH        P1OUT |=BIT3//DIN信号写1
#define DIN_LOW             P1OUT &=~BIT3//DIN信号写1
#endif
//-------------------------G2Platform-------------------------
#define G2PLATFORM 1
#if G2PLATFORM>0

#endif
#endif /* CONF_EXT_H_ */
