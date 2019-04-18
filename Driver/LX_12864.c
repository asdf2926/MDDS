/*
 * LX_12864.c
 *
 *  Created on: 2019年1月30日
 *      Author: asdf2
 */


#include "includes.h"
#if LCD_EN>0
INT8U LCDBuffer[1024];
#define InterFace(a) _COMB_AB(LCD_DRIVER,a)// 转换宏
inline void __LCDTransDoneCallBack(void);

//const INT8U TABCom[]={3,2,1,0,7,6,5,4};
//INT8U DelayLCD=200;
#if LCD_INTR_EN>0
MAKE_BUFFER(LCD,INT16U,LCD_BUF_SIZE,INT8U,,)
BL LCDWorking;INT16U LastDat;
//传输完成时回调函数
inline void __LCDTransDoneCallBack()
{
    LCDWorking=0;
    GPIOWritePin(LCD_CS_PIN,1);
}
//中断模式传输函数
void __LCDTrans()
{
    if(BufLCDR(&LastDat,1))
    {
        __LCDTransDoneCallBack();
        return;
    }
    GPIOWritePin(LCD_A0_PIN,((LastDat&0xff00)==0));
    InterFace(WriteByte)(LastDat&0xFF);
}
void __LCDTransCallBack()
{
//    if(LastDat&0xff00)BasicTimerAdd(DelayLCD,1,__LCDTrans);
//    else
        __LCDTrans();

}

#endif
//向LCD写字节
//参数：
//  const INT16U dat：数据（后8位），第9指示写入何通道（0：数据，1：控制）
//返回：无
void LCDWrite(const INT16U dat)
{
#if LCD_INTR_EN>0
    BufLCDWB(dat);
    if(LCDWorking==0)
    {
        LCDWorking=1;
        GPIOWritePin(LCD_CS_PIN,0);
        __LCDTrans();

    }
#else
    GPIOWritePin(LCD_CS_PIN,0);
    GPIOWritePin(LCD_A0_PIN,((dat&0xff00)==0));
    InterFace(WriteByte)(dat&0xFF);
    InterFace(WaitTransmit)();
//			SystemDelay(1000);
    GPIOWritePin(LCD_CS_PIN,1);
#endif
}
//向LCD写多个字节
//参数：
//  const INT16U *dat：指针：数据（后8位），第9指示写入何通道（0：数据，1：控制）
//  INT8U Len：长度
//返回：无
void LCDWriteMulti(const INT16U *dat,INT8U Len)
{
#if LCD_INTR_EN>0
    BufLCDWB(*(dat++));
    Len--;
    if(LCDWorking==0)
    {
        LCDWorking=1;
        GPIOWritePin(LCD_CS_PIN,0);
        __LCDTrans();

    }
    while(Len-->0)
		{
				BufLCDWB(*(dat++));
		}
#else
        GPIOWritePin(LCD_CS_PIN,0);
    while(Len-->0)
    {
        GPIOWritePin(LCD_A0_PIN,((*dat&0xff00)==0));
        InterFace(WriteByte)(*dat&0xFF);
        InterFace(WaitTransmit)();
//			  SystemDelay(1000);
        dat++;
    }
        GPIOWritePin(LCD_CS_PIN,1);
#endif
}

#if LCD_DMA_EN>0
INT8U DMAPage,DMAColumn,DMAWidth;
INT16U DMASize;
const INT8U *DMAData;
void LCDWriteBlock_DMA_CallBack(void)
{
	if(DMASize>0)
	{
        LCDWrite((INT16U)0x1b0|DMAPage++);
        LCDWrite(0x110|((DMAColumn)>>4));
        LCDWrite(0x100|((DMAColumn)&0x0F));
			HSPIWriteBlock_DMA(DMAData,DMAWidth);
			DMASize-=DMAWidth;
		
	}else{
    GPIOWritePin(LCD_CS_PIN,1);
			HSPISetCallBack(NULL);
		
	}
	
}

void LCDWriteBlock_DMA(void)
{
    GPIOWritePin(LCD_CS_PIN,0);
		GPIOWritePin(LCD_A0_PIN,1);
    if(DMASize>0)
		{
        LCDWrite((INT16U)0x1b0|DMAPage++);
        LCDWrite(0x110|((DMAColumn)>>4));
        LCDWrite(0x100|((DMAColumn)&0x0F));
			HSPISetCallBack(LCDWriteBlock_DMA_CallBack);
			HSPIWriteBlock_DMA(DMAData,DMAWidth);
			DMASize-=DMAWidth;
		}
	
}
#endif

//复位LCD
#ifndef PLATFORM_STM32
inline 
#endif	
void ResetLCD()
{
    GPIOWritePin(LCD_RST_PIN,0);
    SystemDelay(2000);
    GPIOWritePin(LCD_RST_PIN,1);
    SystemDelay(2000);

}

const INT16U _LCDInitCmdList[13]={
                                0x1e3    , // reset signal
                                0x1a3    , //(0xa2 1/9 bias,1/65 duty)
                                0x1a0    , // ADC select
                                0x1c8    , // command output select
                                0x12f    , // power control
                                0x124    , // select resistor ratio Rb/Ra
                                0x181    , // select volume
                                0x119,     //0x115~0x129 , // vop<-----------
                                0x1f8    , // x4
                                0x108    , // x4
                                0x1b0    ,//set page address
                                0x110    ,//set column address
                                0x100     //null command

},_LCDInitCmdList1=0x1af;
//清LCD
//参数：
//  INT8U FillData：填充数据
//返回：无
void LCDClear( INT8U FillData )
{
    INT16U com[]={0x1B0,0x110,0x100};
    INT8U i,j;
    for(i=0;i<8;i++)
    {
        LCDWriteMulti(com,3); //Set Page Address
        //Set Column Address = 0
         //Colum from S1 -> S128 auto add
        com[0]+=1;
        for(j=0;j<128;j++)
        {
            LCDWrite(FillData);
					LCDBuffer[i*128+j]=FillData;
        }
    }
}
//LCD初始化
//参数：无
//返回：无
inline void LCDInit()
{
#if LCD_INTR_EN>0
    BufInit(LCD);
    LCDWorking=0;
    InterFace(SetTxCallBack)(__LCDTransCallBack);
#endif
    ResetLCD();
    LCDWriteMulti(_LCDInitCmdList,13);
    LCDClear(LCD_INIT_FILL_DATA);
    LCDWrite(_LCDInitCmdList1);
  //  LCDWriteMulti(_LCDInitCmdList,13);
    LCDWrite(_LCDInitCmdList1);
#if LCD_LED_EN>0
	GPIOWritePin(LCD_LED_PIN,1);
#endif
}

#if BT_EXT_CALLBACK>0
void LCDHotInit(INT8U ul)
#else
void LCDHotInit(void)
#endif
{
#if LCD_INTR_EN>0
    BufInit(LCD);
    LCDWorking=0;
    InterFace(SetTxCallBack)(__LCDTransCallBack);
#endif
    ResetLCD();
    LCDWriteMulti(_LCDInitCmdList,13);
   // LCDClear(LCD_INIT_FILL_DATA);
    LCDWrite(_LCDInitCmdList1);
  //  LCDWriteMulti(_LCDInitCmdList,13);
    LCDWrite(_LCDInitCmdList1);
}
const INT16U _LCDDeinitCmd[]={0x1ae,//DP off
								0x1a5,//all pixel on
								0x128//power off
	};
void LCDDeInit()
{
#if LCD_LED_EN>0
	GPIOWritePin(LCD_LED_PIN,0);
#endif
	LCDWriteMulti(_LCDDeinitCmd,3);
}
//LCD写入字符串
//参数：
//  INT8U Page：页
//  INT8U Column：列
//  INT8U fontwidth：字体宽度
//  INT16U fontsize：字体字符数据大小
//  const INT8U *fontdat：字体数据的指针
//  char *dat：字符串
//返回：无
void LCDWriteStringRaw(INT8U Page,INT8U Column,INT8U fontwidth,INT16U fontsize,const INT8U *fontdat,const char *dat)
{
    INT8U col=Column;
    while(*dat)
    {
        LCDWriteCharRaw(Page,col,fontwidth,fontsize,fontdat,*dat);
        dat++;
        col+=fontwidth;
        if(*dat=='\n')
        {
            dat++;
            col=Column;
            Page++;
        }
        if(col>=LCD_WIDTH)
        {
            col=Column;
            Page++;
        }
    }
}
//LCD写入字符
//参数：
//  INT8U Page：页
//  INT8U Column：列
//  INT8U fontwidth：字体宽度
//  INT16U fontsize：字体字符数据大小
//  const INT8U *fontdat：字体数据的指针
//  char dat：字节
//返回：无
void LCDWriteCharRaw(INT8U Page,INT8U Column,INT8U fontwidth,INT16U fontsize,const INT8U *fontdat,char dat)
{
    INT8U count;
    fontdat+=(dat-' ')*fontsize;
    while(fontsize>0)
    {
        LCDWrite((INT16U)0x1b0|Page++);
        LCDWrite(0x110|((Column)>>4));
        LCDWrite(0x100|((Column)&0x0F));
        for(count=0;count<fontwidth;count++)
        {
            LCDWrite(*(fontdat++));
        }
        fontsize-=fontwidth;
    }

}
//LCD写入图像
//参数：
//  INT8U Page：页
//  INT8U Column：列
//  INT8U width：宽度
//  INT16U size：数据大小
//  const INT8U *dat：数据的指针
//返回：无
void LCDWriteImageRaw(INT8U Page,INT8U Column,INT8U width,INT16U size,const INT8U *dat)
{
	#if LCD_DMA_EN>0
	DMAPage=Page;
	DMAColumn=Column;
	DMAWidth=width;
	DMASize=size;
	DMAData=dat;
	LCDWriteBlock_DMA();
	#else
    INT16U count;
    while(size>0)
    {
        LCDWrite((INT16U)0x1b0|Page++);
        LCDWrite(0x110|((Column)>>4));
        LCDWrite(0x100|((Column)&0x0F));
        for(count=0;count<width;count++)
        {
            LCDWrite(*(dat++));
        }
        size-=width;
    }
		#endif
}

#if LCD_BUFFER_EN
void LCDRefresh()
{
	#if LCD_DMA_EN==0
//	INT8U r,s;
//	INT16U count;
//	for(r=0;r<8;r++)
//	{
//			LCDWrite((INT16U)0x1b0|r);
//			LCDWrite(0x110);
//			LCDWrite(0x100);
//			for(s=0;s<128;s++)
//			{
//					LCDWrite(LCDBuffer[(r<<7)+s]);
//			}
//			size-=width;
//	}
    INT16U com[]={0x1B0,0x110,0x100};
    INT8U i,j;
    for(i=0;i<8;i++)
    {
        LCDWriteMulti(com,3); //Set Page Address
        //Set Column Address = 0
         //Colum from S1 -> S128 auto add
        com[0]+=1;
        for(j=0;j<128;j++)
        {
            LCDWrite(LCDBuffer[(i<<7)+j]);
        }
    }

	#else
	DMAPage=0;
	DMAColumn=0;
	DMAWidth=LCD_WIDTH;
	DMASize=LCD_WIDTH*LCD_HEIGHT/8;
	DMAData=LCDBuffer;
	LCDWriteBlock_DMA();
	#endif
	
}
#endif

#endif
