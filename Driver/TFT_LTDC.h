#ifndef _TFT_LTDC_H
#define _TFT_LTDC_H
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//LTDC驱动	   	    
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2016/7/13
//版本：V1.2
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved	 
//********************************************************************************
//修改说明  
//V1.1  20161026 
//在LTDC_PanelID_Read函数加入delay，解决-O2优化读ID可能出错的BUG
//V1.2  20170606 
//新增10.1寸RGB屏的支持
//////////////////////////////////////////////////////////////////////////////////	 
//LCD LTDC重要参数集
#if LTDC_EN>0
typedef struct  
{							 
	INT32U pwidth;			//LCD面板的宽度,固定参数,不随显示方向改变,如果为0,说明没有任何RGB屏接入
	INT32U pheight;		//LCD面板的高度,固定参数,不随显示方向改变
	INT16U hsw;			//水平同步宽度
	INT16U vsw;			//垂直同步宽度
	INT16U hbp;			//水平后廊
	INT16U vbp;			//垂直后廊
	INT16U hfp;			//水平前廊
	INT16U vfp;			//垂直前廊 
	INT8U activelayer;		//当前层编号:0/1	
	INT8U dir;				//0,竖屏;1,横屏;
	INT16U width;			//LCD宽度
	INT16U height;			//LCD高度
//	INT32U pixsize;		//每个像素所占字节数
}_ltdc_dev; 

extern _ltdc_dev lcdltdc;		            //管理LCD LTDC参数
extern LTDC_HandleTypeDef LTDC_Handler;	    //LTDC句柄
extern DMA2D_HandleTypeDef DMA2D_Handler;   //DMA2D句柄

#define LCD_PIXEL_FORMAT_ARGB8888       0X00    
#define LCD_PIXEL_FORMAT_RGB888         0X01    
#define LCD_PIXEL_FORMAT_RGB565         0X02       
#define LCD_PIXEL_FORMAT_ARGB1555       0X03      
#define LCD_PIXEL_FORMAT_ARGB4444       0X04     
#define LCD_PIXEL_FORMAT_L8             0X05     
#define LCD_PIXEL_FORMAT_AL44           0X06     
#define LCD_PIXEL_FORMAT_AL88           0X07      

#if LCD_PIXFORMAT==LCD_PIXFORMAT_ARGB8888||LCD_PIXFORMAT==LCD_PIXFORMAT_RGB888
#define LCD_PIXELSIZE 4
#else
#define LCD_PIXELSIZE 2

#endif
///////////////////////////////////////////////////////////////////////
void LTDC_Switch(INT8U sw);					//TFT开关
void LTDC_Layer_Switch(INT8U layerx,INT8U sw);	//层开关
void LTDC_Select_Layer(INT8U layerx);			//层选择
void LTDC_Display_Dir(INT8U dir);				//显示方向控制
BL LTDC_Draw_Point(INT16U x,INT16U y,INT32U color);//画点函数
INT32U LTDC_Read_Point(INT16U x,INT16U y);			//读点函数
void LTDC_Fill(INT16U sx,INT16U sy,INT16U ex,INT16U ey,INT32U color);			//矩形单色填充函数
void LTDC_Color_Fill(INT16U sx,INT16U sy,INT16U ex,INT16U ey,Color *color);	//矩形彩色填充函数
void LTDC_Clear(INT32U color);					//清屏函数
void LTDC_Layer_Window_Config(INT8U layerx,INT16U sx,INT16U sy,INT16U width,INT16U height);//TFT层窗口设置
void LTDC_Init(void);						//TFT初始化函数

#define TFT_DrawPoint(x,y,c) LTDC_Draw_Point(x,y,c)

#define LCD_DisplayOff() TFT_Switch(0)
#define LCD_DisplayOn()  TFT_Switch(1)
#endif
#endif 
