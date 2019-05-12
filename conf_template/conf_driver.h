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
#define LCD_EN 1
#if LCD_EN>0
#define LCD_DRIVER HSPI         //LCD接口驱动，取值有HSPI和SSPI
#define LCD_INTR_EN 0           //LCD数据传输由中断控制
#define LCD_DMA_EN 0
#define LCD_BUF_SIZE 40         //LCD缓冲区大小，仅在中断模式时有效
#define LCD_RST_PIN GPIOB,PIN0  //RST引脚号，为GPIOx,PINx的二元组
#define LCD_CS_PIN GPIOB,PIN1  //CS引脚号，为GPIOx,PINx的二元组
#define LCD_A0_PIN GPIOA,PIN4  //A0引脚号，为GPIOx,PINx的二元组

#define LCD_INIT_FILL_DATA 0x55

#define LCD_BUFFER_EN 1//启用LCD全屏刷新模式；缓冲区1KB由用户定义

//SCLK->P1.4
//MOSI->P1.2
#endif
//--------------------------TCA6416A---------------------------
#define TCA6416A_EN 0
#if TCA6416A_EN>0
#define TCA6416A_INTERFACE IIC //IIC only
#define TCA6416A_PORT_0_DIR 0
#define TCA6416A_PORT_1_DIR 0x0f
#define TCA6416A_PORT_0_OUT 0xaa
#define TCA6416A_PORT_1_OUT 0xff
#endif
//-------------------------HT1621-----------------------------
#define HT1621_EN 0
#if HT1621_EN>0
#define HT1621_INTERFACE GPIO
#define HT1621_CS_PIN       GPIOB,PIN0
//#define HT1621_RD_PIN       GPIOB,PIN5//not necessary,always 1
#define HT1621_WR_PIN   	GPIOB,PIN1
#define HT1621_DATA_PIN     GPIOA,PIN4
#endif
//-------------------------SegLCD_G2--------------------------
#if HT1621_EN>0
#define SegLCD_G2_EN 0
#endif
//-------------------------DAC8411----------------------------
#define DAC8411_EN 0
#if DAC8411_EN>0
#define SYNC_HIGH       P1OUT |=BIT0
#define SYNC_LOW        P1OUT &=~BIT0
#define SCLK_HIGH       P2OUT |=BIT2
#define SCLK_LOW        P2OUT &=~BIT2
#define DIN_HIGH        P1OUT |=BIT3
#define DIN_LOW             P1OUT &=~BIT3
#endif
//-------------------------G2Platform-------------------------
#define G2PLATFORM 0
#if G2PLATFORM>0

#endif
//-------------------------TFT--------------------------------
#define TFT_EN 1
#if TFT_EN>0
#define TFT_INIT_COLOR LIGHTBLUE
#endif
//------------------------TFT_LTDC----------------------------
#define LTDC_EN 1
#if LTDC_EN>0
#define LTDC_TYPE 0x4342
#define LCD_PIXFORMAT LCD_PIXEL_FORMAT_RGB565
//LCD帧缓冲区首地址,这里定义在SDRAM里面.
#define LCD_FRAME_BUF_ADDR			0XC0000000  
#endif
//-------------------------Font-------------------------------
#define FONT_EN 0
//-------------------------SDRAM------------------------------
#define SDRAM_EN 1
//-------------------------GT9147-----------------------------
#define GT9147_EN 1
//-------------------------TFT_ILI9341------------------------
#define TFT_ILI9341_EN 1
#if TFT_ILI9341_EN>0

#endif
#endif /* CONF_EXT_H_ */
