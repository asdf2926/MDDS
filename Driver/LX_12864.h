/*
 * LX_12864.h
 *
 *  Created on: 2019年1月30日
 *      Author: asdf2
 */

#ifndef DRIVER_LX_12864_H_
#define DRIVER_LX_12864_H_
#if LCD_EN>0
#define LCD_WIDTH 128//LCD宽度
#define LCD_HEIGHT 64//LCD高度
//SPI模式3，MSB First
//CPOL=1
//CPHA=1

//LCD初始化
//参数：无
//返回：无
#ifndef PLATFORM_STM32
inline 
#endif	
void LCDInit(void);
#if BT_EXT_CALLBACK>0
void LCDHotInit(INT8U ul);
#else
void LCDHotInit(void);
#endif
void LCDDeInit(void);

//清LCD
//参数：
//  INT8U FillData：填充数据
//返回：无
void LCDClear( INT8U FillData );

//LCD写入图像
//参数：
//  INT8U Page：页
//  INT8U Column：列
//  INT8U width：宽度
//  INT16U size：数据大小
//  const INT8U *dat：数据的指针
//返回：无
//注意：会完全覆盖原来内容
void LCDWriteImageRaw(INT8U Page,INT8U Column,INT8U width,INT16U size,const INT8U *dat);
//LCD写入字符
//参数：
//  INT8U Page：页
//  INT8U Column：列
//  INT8U fontwidth：字体宽度
//  INT16U fontsize：字体字符数据大小
//  const INT8U *fontdat：字体数据的指针
//  char dat：字节
//返回：无
//注意：会完全覆盖原来内容，字体信息部分可以直接用字体提供的信息三元组代替
void LCDWriteCharRaw(INT8U Page,INT8U Column,INT8U fontwidth,INT16U fontsize,const INT8U *fontdat,const char dat);
//LCD写入字符串
//参数：
//  INT8U Page：页
//  INT8U Column：列
//  INT8U fontwidth：字体宽度
//  INT16U fontsize：字体字符数据大小
//  const INT8U *fontdat：字体数据的指针
//  char *dat：字符串
//返回：无
//注意：会完全覆盖原来内容，字体信息部分可以直接用字体提供的信息三元组代替
void LCDWriteStringRaw(INT8U Page,INT8U Column,INT8U fontwidth,INT16U fontsize,const INT8U *fontdat,const char *dat);
#if LCD_BUFFER_EN>0
//#if LCD_DMA_EN>0

//#else
extern INT8U LCDBuffer[1024];
void LCDRefresh(void);

/*
void LCDWriteChar(INT8U Line,INT8U Column,INT8U Column,INT8U fontwidth,INT16U fontsize,const INT8U *fontdat,char dat);
void LCDWriteStringRaw(INT8U Line,INT8U Column,INT8U fontwidth,INT16U fontsize,const INT8U *fontdat,char *dat);
*/
//   #endif
#endif

#endif
#endif /* DRIVER_LX_12864_H_ */
