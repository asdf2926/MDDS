#include "includes.h"
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
LTDC_HandleTypeDef  LTDC_Handler;	    //LTDC句柄
DMA2D_HandleTypeDef DMA2D_Handler; 	    //DMA2D句柄

//根据不同的颜色格式,定义帧缓存数组
#if LCD_PIXFORMAT==LCD_PIXFORMAT_ARGB8888||LCD_PIXFORMAT==LCD_PIXFORMAT_RGB888
	INT32U ltdc_lcd_framebuf[1280][800] __attribute__((at(LCD_FRAME_BUF_ADDR)));	//定义最大屏分辨率时,LCD所需的帧缓存数组大小
#else
	INT16U ltdc_lcd_framebuf[1280][800] __attribute__((at(LCD_FRAME_BUF_ADDR)));	//定义最大屏分辨率时,LCD所需的帧缓存数组大小
#endif

INT32U *ltdc_framebuf[2];					//LTDC LCD帧缓存数组指针,必须指向对应大小的内存区域
_ltdc_dev lcdltdc;						//管理LCD LTDC的重要参数

//打开LCD开关
//lcd_switch:1 打开,0，关闭
void LTDC_Switch(INT8U sw)
{
	if(sw==1) __HAL_LTDC_ENABLE(&LTDC_Handler);
	else if(sw==0)__HAL_LTDC_DISABLE(&LTDC_Handler);
}

//开关指定层
//layerx:层号,0,第一层; 1,第二层
//sw:1 打开;0关闭
void LTDC_Layer_Switch(INT8U layerx,INT8U sw)
{
	if(sw==1) __HAL_LTDC_LAYER_ENABLE(&LTDC_Handler,layerx);
	else if(sw==0) __HAL_LTDC_LAYER_DISABLE(&LTDC_Handler,layerx);
	__HAL_LTDC_RELOAD_CONFIG(&LTDC_Handler);
}

//选择层
//layerx:层号;0,第一层;1,第二层;
void LTDC_Select_Layer(INT8U layerx)
{
	lcdltdc.activelayer=layerx;
}

//设置LCD显示方向
//dir:0,竖屏；1,横屏
void LTDC_Display_Dir(INT8U dir)
{
    lcdltdc.dir=dir; 	//显示方向
	if(dir==0)			//竖屏
	{
		lcdltdc.width=lcdltdc.pheight;
		lcdltdc.height=lcdltdc.pwidth;	
		ScrWidth=lcdltdc.width;
		ScrHeight=lcdltdc.height;
	}else if(dir==1)	//横屏
	{
		lcdltdc.width=lcdltdc.pwidth;
		lcdltdc.height=lcdltdc.pheight;
		ScrWidth=lcdltdc.width;
		ScrHeight=lcdltdc.height;
	}
}

//画点函数
//x,y:坐标
//color:颜色值
BL LTDC_Draw_Point(INT16U x,INT16U y,INT32U color)
{ 
	if((x>=lcdltdc.width )|| (y>=lcdltdc.height))return 0;
#if LCD_PIXFORMAT==LCD_PIXFORMAT_ARGB8888||LCD_PIXFORMAT==LCD_PIXFORMAT_RGB888
	if(lcdltdc.dir)	//横屏
	{
        *(INT32U*)((INT32U)ltdc_framebuf[lcdltdc.activelayer]+LCD_PIXELSIZE*(lcdltdc.pwidth*y+x))=color;
	}else 			//竖屏
	{
        *(INT32U*)((INT32U)ltdc_framebuf[lcdltdc.activelayer]+LCD_PIXELSIZE*(lcdltdc.pwidth*(lcdltdc.pheight-x-1)+y))=color; 
	}
#else
	if(lcdltdc.dir)	//横屏
	{
        *(INT16U*)((INT32U)ltdc_framebuf[lcdltdc.activelayer]+LCD_PIXELSIZE*(lcdltdc.pwidth*y+x))=color;
	}else 			//竖屏
	{
        *(INT16U*)((INT32U)ltdc_framebuf[lcdltdc.activelayer]+LCD_PIXELSIZE*(lcdltdc.pwidth*(lcdltdc.pheight-x-1)+y))=color; 
	}
#endif
	return 1;
}

//读点函数
//返回值:颜色值
INT32U LTDC_Read_Point(INT16U x,INT16U y)
{ 
#if LCD_PIXFORMAT==LCD_PIXFORMAT_ARGB8888||LCD_PIXFORMAT==LCD_PIXFORMAT_RGB888
	if(lcdltdc.dir)	//横屏
	{
		return *(INT32U*)((INT32U)ltdc_framebuf[lcdltdc.activelayer]+LCD_PIXELSIZE*(lcdltdc.pwidth*y+x));
	}else 			//竖屏
	{
		return *(INT32U*)((INT32U)ltdc_framebuf[lcdltdc.activelayer]+LCD_PIXELSIZE*(lcdltdc.pwidth*(lcdltdc.pheight-x-1)+y)); 
	}
#else
	if(lcdltdc.dir)	//横屏
	{
		return *(INT16U*)((INT32U)ltdc_framebuf[lcdltdc.activelayer]+LCD_PIXELSIZE*(lcdltdc.pwidth*y+x));
	}else 			//竖屏
	{
		return *(INT16U*)((INT32U)ltdc_framebuf[lcdltdc.activelayer]+LCD_PIXELSIZE*(lcdltdc.pwidth*(lcdltdc.pheight-x-1)+y)); 
	}
#endif 
}

//TFT填充矩形,DMA2D填充
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   
//注意:sx,ex,不能大于lcddev.width-1;sy,ey,不能大于lcddev.height-1!!!
//color:要填充的颜色
void LTDC_Fill(INT16U sx,INT16U sy,INT16U ex,INT16U ey,INT32U color)
{ 
	INT16S psx,psy,pex,pey;	//以LCD面板为基准的坐标系,不随横竖屏变化而变化
	INT32U timeout=0; 
	INT16U offline;
	INT32U addr; 
	//坐标系转换
	if(lcdltdc.dir)	//横屏
	{
		psx=sx;psy=sy;
		pex=ex;pey=ey;
	}else			//竖屏
	{
		psx=sy;psy=lcdltdc.pheight-ex-1;
		pex=ey;pey=lcdltdc.pheight-sx-1;
	} 
	if(psx<0)psx=0;if(psy<0)psy=0;if(psx>lcdltdc.pwidth-1)psx=lcdltdc.pwidth-1;if(psy>lcdltdc.pheight-1)psy=lcdltdc.pheight-1;
	if(pex<0)pex=0;if(pey<0)pey=0;if(pex>lcdltdc.pwidth-1)pex=lcdltdc.pwidth-1;if(pey>lcdltdc.pheight-1)pey=lcdltdc.pheight-1;
	offline=lcdltdc.pwidth-(pex-psx+1);
	addr=((INT32U)ltdc_framebuf[lcdltdc.activelayer]+LCD_PIXELSIZE*(lcdltdc.pwidth*psy+psx));
	RCC->AHB1ENR|=1<<23;			//使能DM2D时钟
	DMA2D->CR=3<<16;				//寄存器到存储器模式
	DMA2D->OPFCCR=LCD_PIXFORMAT;	//设置颜色格式
	DMA2D->OOR=offline;				//设置行偏移 
	DMA2D->CR&=~(1<<0);				//先停止DMA2D
	DMA2D->OMAR=addr;				//输出存储器地址
	DMA2D->NLR=(pey-psy+1)|((pex-psx+1)<<16);	//设定行数寄存器
	DMA2D->OCOLR=color;				//设定输出颜色寄存器 
	DMA2D->CR|=1<<0;				//启动DMA2D
	while((DMA2D->ISR&(1<<1))==0)	//等待传输完成
	{
		timeout++;
		if(timeout>0X1FFFFF)break;	//超时退出
	}  
	DMA2D->IFCR|=1<<1;				//清除传输完成标志 	
}
//在指定区域内填充单个颜色
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   
//color:要填充的颜色
//void TFT_Fill(INT16U sx,INT16U sy,INT16U ex,INT16U ey,INT32U color)
//{
//	INT32U psx,psy,pex,pey;	//以LCD面板为基准的坐标系,不随横竖屏变化而变化
//	INT32U timeout=0; 
//	INT16U offline;
//	INT32U addr;  
//    if(ex>=lcdltdc.width)ex=lcdltdc.width-1;
//	if(ey>=lcdltdc.height)ey=lcdltdc.height-1;
//	//坐标系转换
//	if(lcdltdc.dir)	//横屏
//	{
//		psx=sx;psy=sy;
//		pex=ex;pey=ey;
//	}else			//竖屏
//	{
//		psx=sy;psy=lcdltdc.pheight-ex-1;
//		pex=ey;pey=lcdltdc.pheight-sx-1;
//	}
//	offline=lcdltdc.pwidth-(pex-psx+1);
//	addr=((INT32U)ltdc_framebuf[lcdltdc.activelayer]+LCD_PIXELSIZE*(lcdltdc.pwidth*psy+psx));
//    if(LCD_PIXFORMAT==LCD_PIXEL_FORMAT_RGB565)  //如果是RGB565格式的话需要进行颜色转换，将16bit转换为32bit的
//    {
//        color=((color&0X0000F800)<<8)|((color&0X000007E0)<<5)|((color&0X0000001F)<<3);
//    }
//	//配置DMA2D的模式
//	DMA2D_Handler.Instance=DMA2D;
//	DMA2D_Handler.Init.Mode=DMA2D_R2M;			//内存到存储器模式
//	DMA2D_Handler.Init.ColorMode=LCD_PIXFORMAT;	//设置颜色格式
//	DMA2D_Handler.Init.OutputOffset=offline;		//输出偏移 
//	HAL_DMA2D_Init(&DMA2D_Handler);              //初始化DMA2D
//    HAL_DMA2D_ConfigLayer(&DMA2D_Handler,lcdltdc.activelayer); //层配置
//    HAL_DMA2D_Start(&DMA2D_Handler,color,(INT32U)addr,pex-psx+1,pey-psy+1);//开启传输
//    HAL_DMA2D_PollForTransfer(&DMA2D_Handler,1000);//传输数据
//    while((__HAL_DMA2D_GET_FLAG(&DMA2D_Handler,DMA2D_FLAG_TC)==0)&&(timeout<0X5000))//等待DMA2D完成
//    {
//        timeout++;
//    }
//    __HAL_DMA2D_CLEAR_FLAG(&DMA2D_Handler,DMA2D_FLAG_TC);       //清除传输完成标志
//}

//在指定区域内填充指定颜色块,DMA2D填充	
//此函数仅支持u16,RGB565格式的颜色数组填充.
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)  
//注意:sx,ex,不能大于lcddev.width-1;sy,ey,不能大于lcddev.height-1!!!
//color:要填充的颜色数组首地址
void LTDC_Color_Fill(INT16U sx,INT16U sy,INT16U ex,INT16U ey,Color *color)
{
	INT32U psx,psy,pex,pey;	//以LCD面板为基准的坐标系,不随横竖屏变化而变化
	INT32U timeout=0; 
	INT16U offline;
	INT32U addr; 
	//坐标系转换
	if(lcdltdc.dir)	//横屏
	{
		psx=sx;psy=sy;
		pex=ex;pey=ey;
	}else			//竖屏
	{
		psx=sy;psy=lcdltdc.pheight-ex-1;
		pex=ey;pey=lcdltdc.pheight-sx-1;
	}
	offline=lcdltdc.pwidth-(pex-psx+1);
	addr=((INT32U)ltdc_framebuf[lcdltdc.activelayer]+LCD_PIXELSIZE*(lcdltdc.pwidth*psy+psx));
	RCC->AHB1ENR|=1<<23;			//使能DM2D时钟
	DMA2D->CR=0<<16;				//存储器到存储器模式
	DMA2D->FGPFCCR=LCD_PIXFORMAT;	//设置颜色格式
	DMA2D->FGOR=0;					//前景层行偏移为0
	DMA2D->OOR=offline;				//设置行偏移 
	DMA2D->CR&=~(1<<0);				//先停止DMA2D
	DMA2D->FGMAR=(INT32U)color;		//源地址
	DMA2D->OMAR=addr;				//输出存储器地址
	DMA2D->NLR=(pey-psy+1)|((pex-psx+1)<<16);	//设定行数寄存器 
	DMA2D->CR|=1<<0;				//启动DMA2D
	while((DMA2D->ISR&(1<<1))==0)	//等待传输完成
	{
		timeout++;
		if(timeout>0X1FFFFF)break;	//超时退出
	} 
	DMA2D->IFCR|=1<<1;				//清除传输完成标志  	
} 

//LCD清屏
//color:颜色值
void LTDC_Clear(INT32U color)
{
	LTDC_Fill(0,0,lcdltdc.width-1,lcdltdc.height-1,color);
}


//TFT,层颜窗口设置,窗口以LCD面板坐标系为基准
//注意:此函数必须在TFT_Layer_Parameter_Config之后再设置.
//layerx:层值,0/1.
//sx,sy:起始坐标
//width,height:宽度和高度
void LTDC_Layer_Window_Config(INT8U layerx,INT16U sx,INT16U sy,INT16U width,INT16U height)
{
    HAL_LTDC_SetWindowPosition(&LTDC_Handler,sx,sy,layerx);  //设置窗口的位置
    HAL_LTDC_SetWindowSize(&LTDC_Handler,width,height,layerx);//设置窗口大小    
}


//LCD初始化函数
void LTDC_Init(void)
{   
	if(LTDC_TYPE==0X4342)
	{
		lcdltdc.pwidth=480;			    //面板宽度,单位:像素
		lcdltdc.pheight=272;		    //面板高度,单位:像素
		lcdltdc.hsw=1;				    //水平同步宽度
		lcdltdc.vsw=1;				    //垂直同步宽度
		lcdltdc.hbp=40;				    //水平后廊
		lcdltdc.vbp=8;				    //垂直后廊
		lcdltdc.hfp=5;				    //水平前廊
		lcdltdc.vfp=8;				    //垂直前廊
		//CLK:9M
		//其他参数待定.
	}else if(LTDC_TYPE==0X7084)
	{
		lcdltdc.pwidth=800;			    //面板宽度,单位:像素
		lcdltdc.pheight=480;		    //面板高度,单位:像素
		lcdltdc.hsw=1;				    //水平同步宽度
		lcdltdc.vsw=1;				    //垂直同步宽度
		lcdltdc.hbp=46;				    //水平后廊
		lcdltdc.vbp=23;				    //垂直后廊
		lcdltdc.hfp=210;			    //水平前廊
		lcdltdc.vfp=22;				    //垂直前廊
        //设置像素时钟 33M(如果开双显,需要降低DCLK到:18.75Mhz  300/4/4,才会比较好)
	}else if(LTDC_TYPE==0X7016)		
	{
		lcdltdc.pwidth=1024;			//面板宽度,单位:像素
		lcdltdc.pheight=600;			//面板高度,单位:像素
        lcdltdc.hsw=20;				    //水平同步宽度
		lcdltdc.vsw=3;				    //垂直同步宽度
		lcdltdc.hbp=140;			    //水平后廊
		lcdltdc.vbp=20;				    //垂直后廊
		lcdltdc.hfp=160;			    //水平前廊
		lcdltdc.vfp=12;				    //垂直前廊
		//设置像素时钟  45Mhz 
		//其他参数待定.
	}else if(LTDC_TYPE==0X7018)		
	{
		lcdltdc.pwidth=1280;			//面板宽度,单位:像素
		lcdltdc.pheight=800;			//面板高度,单位:像素
		//其他参数待定.
	}else if(LTDC_TYPE==0X8016)		
	{
		lcdltdc.pwidth=1024;			//面板宽度,单位:像素
		lcdltdc.pheight=768;			//面板高度,单位:像素
		//其他参数待定.
    }else if(LTDC_TYPE==0X1018)			//10.1寸1280*800 RGB屏	
	{
		lcdltdc.pwidth=1280;		//面板宽度,单位:像素
		lcdltdc.pheight=800;		//面板高度,单位:像素
		lcdltdc.hbp=140;			//水平后廊
		lcdltdc.hfp=10;			    //水平前廊
		lcdltdc.hsw=10;				//水平同步宽度
		lcdltdc.vbp=10;				//垂直后廊
		lcdltdc.vfp=10;				//垂直前廊
		lcdltdc.vsw=3;				//垂直同步宽度
		//设置像素时钟  45Mhz 
	}  
    
#if LCD_PIXFORMAT==LCD_PIXFORMAT_ARGB8888||LCD_PIXFORMAT==LCD_PIXFORMAT_RGB888 
	ltdc_framebuf[0]=(INT32U*)&ltdc_lcd_framebuf;
//	LCD_PIXELSIZE=4;				//每个像素占4个字节
#else 
//   LCD_PIXELSIZE=2;				//每个像素占2个字节
	ltdc_framebuf[0]=(INT32U*)&ltdc_lcd_framebuf;
#endif 	
	LTDC_Layer_Window_Config(0,0,0,lcdltdc.pwidth,lcdltdc.pheight);	//层窗口配置,以LCD面板坐标系为基准,不要随便修改!	
	 	
 	LTDC_Display_Dir(0);			//默认竖屏
	LTDC_Select_Layer(0); 			//选择第1层
//    LCD_LED(1);         		    //点亮背光
    LTDC_Clear(LCD_BG_COLOR);			//清屏
}

