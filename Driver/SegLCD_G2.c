/*
 * SegLCD_G2.c
 *
 *  Created on: 2019年3月2日
 *      Author: asdf2
 */
#include "includes.h"
#if SegLCD_G2_EN>0
const INT8U LCDLookupTab[][7]={
                                 {_LCD_1A,_LCD_1B,_LCD_1C,_LCD_1D,_LCD_1E,_LCD_1F,_LCD_1G},
                                 {_LCD_2A,_LCD_2B,_LCD_2C,_LCD_2D,_LCD_2E,_LCD_2F,_LCD_2G},
                                 {_LCD_3A,_LCD_3B,_LCD_3C,_LCD_3D,_LCD_3E,_LCD_3F,_LCD_3G},
                                 {_LCD_4A,_LCD_4B,_LCD_4C,_LCD_4D,_LCD_4E,_LCD_4F,_LCD_4G},
                                 {_LCD_5A,_LCD_5B,_LCD_5C,_LCD_5D,_LCD_5E,_LCD_5F,_LCD_5G},
                                 {_LCD_6A,_LCD_6B,_LCD_6C,_LCD_6D,_LCD_6E,_LCD_6F,_LCD_6G},
                                 {_LCD_10A,_LCD_10B,_LCD_10C,_LCD_10D,_LCD_10E,_LCD_10F,_LCD_10G},
                                 {_LCD_9A,_LCD_9B,_LCD_9C,_LCD_9D,_LCD_9E,_LCD_9F,_LCD_9G},
                                 {_LCD_8A,_LCD_8B,_LCD_8C,_LCD_8D,_LCD_8E,_LCD_8F,_LCD_8G},
                                 {_LCD_7A,_LCD_7B,_LCD_7C,_LCD_7D,_LCD_7E,_LCD_7F,_LCD_7G},
};
const INT8U NumToSegTab[]={
    0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0
};

/***********************************************************************
 * 名称：LCD_Clear( )
 * 功能：清屏
  ********************************************************************** */
void LCDClear()
{
	unsigned char i=0;
    for( i=0;i<=15;i++) HT1621Buffer[i]=0;
 }

/***********************************************************************
 *名称：LCDDigitDisplay(unsigned char Position,unsigned char Digit )
 * 功能：让128段式液晶的特定“8字”段显示0~9
 * 说明：大数码“8字”编号左至右为0~5，小数码“8字”编号右至左为6~9；
 *传入参数：Position：显示的数位（第几个“8字”）
 *传入参数：Position：显示的数位（第几个“8字”）Digit：想显示的数 0~9，传入其他数字则为消隐
 *
 *举例：LCD_DisplayDigit(1,9 )，第1个“8字”段显示9
 * 			   LCD_DisplayDigit(1,LCD_DIGIT_CLEAR)，第1个 “8字”段消隐
 ********************************************************************** */
void LCDDigitDisplay(unsigned char Position,unsigned char Digit )
{
    INT8U SegList[7],i,r;
    r=NumToSegTab[Digit];
    for(i=0;i<7;i++)
    {
        SegList[i]=LCDLookupTab[Position][i]|r<<7;
        r=r>>1;
    }
    HT1621SegmentListAppend(SegList, 7);
}
  /****************************************************************************
  * 名    称：LCDDisplayNum()
  * 功    能：在LCD上连续显示一个整型数据。
  * 入口参数：Digit:显示数值  (-32768~32767)
  * 出口参数：无
  * 范    例: LCD_DisplayNum( 12345); 显示结果: 12345
              	  LCD_DisplayNum(-12345); 显示结果:-12345
  * 说    明: 该函数仅限在大屏幕的8字段上显示
  ****************************************************************************/
#if 0
  void LCDNumDisplay( long int Digit)
  {

  }
#endif
  /****************************************************************************
  * 名    称：Calculate_NumBuff()
  * 功    能：计算单个8字的显存和起始地址
  * 入口参数：Position：8字段的位置
  * 				 *Num_Buffer：需要更新的段码的指针
  * 				 *Addr：需要更新的段码的起始地址的指针
  * 出口参数：无
  * 范         例: 无
  * 说         明: 无
  ****************************************************************************/
#if 0
  void Calculate_NumBuff(unsigned char Position,unsigned char *Num_Buffer,unsigned char *Addr)
   {
 	  switch(Position)
 	  {
 	  case 1: *Num_Buffer=(LCD_Buffer[0]&0x0ff0)>>4; 	*Addr=4/4;break;
 	  case 2: *Num_Buffer=((LCD_Buffer[0]&0xf000)>>12+((LCD_Buffer[1]&0x000f)<<4));	*Addr=12/4;break;
 	  case 3: *Num_Buffer=(LCD_Buffer[1]&0x0ff0)>>4; 	*Addr=20/4;break;
 	  case 4: *Num_Buffer=(LCD_Buffer[3]&0x00ff); 	*Addr=48/4;break;
 	  case 5: *Num_Buffer=(LCD_Buffer[3]&0xff00)>>8;	 *Addr=56/4;break;
 	  case 6: *Num_Buffer=(LCD_Buffer[4]&0x00ff); 	*Addr=64/4;break;
 	  case 7: *Num_Buffer=(LCD_Buffer[6]&0x00ff);	*Addr=96/4;break;
 	  case 8: *Num_Buffer=(LCD_Buffer[6]&0xff00)>>8;	*Addr=104/4;break;
 	  case 9: *Num_Buffer=(LCD_Buffer[7]&0x00ff);	*Addr=112/4;break;
 	  case 10: *Num_Buffer=(LCD_Buffer[7]&0xff00)>>8; 	*Addr=120/4;break;
 	  default: break;
 	  }
   }
#endif
#endif
