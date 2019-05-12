#include "includes.h"
#if SCR_EN>0
INT16U ScrWidth,ScrHeight;
INT8U ScrFontWidth,ScrFontHeightPage;
INT16U ScrFontSize;
const INT8U *FontData;
Color ScrFrontColor=BLACK,ScrBackColor=WHITE;
void ScrClear()
{
#if TFT_EN>0
	INT32U index=0;      
	INT32U totalpoint=TFTdev.width;
	totalpoint*=TFTdev.height; 	//得到总点数		  
	TFT_SetCursor(0x00,0x0000);	//设置光标位置 
	TFT_WriteRAM_Prepare();     //开始写入GRAM	
	for(index=0;index<totalpoint;index++)
	{
		TFT->TFT_RAM=ScrBackColor;		   			  
	}

#elif LTDC_EN>0
    LTDC_Clear(ScrBackColor);
#elif TFT_ILI9341_EN>0
	INT32U index=0;      
	INT32U totalpoint=LCD_MAX_HEIGHT*LCD_MAX_WIDTH;
	Draw_Pos_Size(0, 0, LCD_MAX_HEIGHT, LCD_MAX_WIDTH);
	LCD_WriteCommand(0x2C);
	for(index=0;index<totalpoint;index++)
	{
		LCD_Write_Data(ScrBackColor);		   			  
	}
#endif
}
void ScrColorSet(Color Front,Color Back)
{
    ScrFrontColor=Front;
    ScrBackColor=Back;
}
void ScrFontSet(INT8U width,INT16U size,const INT8U *dat)
{
    ScrFontWidth=width;ScrFontSize=size;FontData=dat;
	ScrFontHeightPage=size/width;
}
//画矩形	  
//(x1,y1),(x2,y2):矩形的对角坐标

void ScrRectangleDraw(INT16U x1, INT16U y1, INT16U x2, INT16U y2)
{
	ScrLineDraw(x1,y1,x2,y1);
	ScrLineDraw(x1,y1,x1,y2);
	ScrLineDraw(x1,y2,x2,y2);
	ScrLineDraw(x2,y1,x2,y2);

}
//在指定位置画一个指定大小的圆
//(x,y):中心点
//r    :半径
void ScrCircleDraw(INT16U x0,INT16U y0,INT8U r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		TFT_DrawPoint(x0+a,y0-b,ScrFrontColor);             //5
 		TFT_DrawPoint(x0+b,y0-a,ScrFrontColor);             //0           
		TFT_DrawPoint(x0+b,y0+a,ScrFrontColor);             //4               
		TFT_DrawPoint(x0+a,y0+b,ScrFrontColor);             //6 
		TFT_DrawPoint(x0-a,y0+b,ScrFrontColor);             //1       
 		TFT_DrawPoint(x0-b,y0+a,ScrFrontColor);             
		TFT_DrawPoint(x0-a,y0-b,ScrFrontColor);             //2             
  		TFT_DrawPoint(x0-b,y0-a,ScrFrontColor);             //7     	         
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}

}
//画线
//x1,y1:起点坐标
//x2,y2:终点坐标  

void ScrLineDraw(INT16U x1, INT16U y1, INT16U x2, INT16U y2)
{
	INT16U t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		TFT_DrawPoint(uRow,uCol,ScrFrontColor);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  

}
//在指定区域内填充单个颜色
//INT16U x,INT16U y:起点坐标,INT16U w,INT16U h:大小
void ScrFill(INT16U x,INT16U y,INT16U w,INT16U h)
{
    #if TFT_EN>0
	INT16U i,j;
 	for(i=0;i<h;i++)
	{
 		TFT_SetCursor(x,y+i);   	//设置光标位置 
		TFT_WriteRAM_Prepare();     //开始写入GRAM
		for(j=0;j<w;j++)TFT->TFT_RAM=ScrFrontColor;//写入数据 
	}	  

    #elif LTDC_EN>0
    LTDC_Fill(x,y,w+x-1,h+y-1,ScrFrontColor);
	#elif TFT_ILI9341_EN>0	
	INT32U index=0;      
	INT32U totalpoint=w*h;
	Draw_Pos_Size(x,y, w, h);
	LCD_WriteCommand(0x2C);
	for(index=0;index<totalpoint;index++)
	{
		LCD_Write_Data(ScrFrontColor);		   			  
	}
	
    #endif
}

//在指定区域内填充图片			 
//INT16U x,INT16U y:起点坐标,INT16U w,INT16U h:大小
//color:图片从左到右，从上到下

void ScrImageWrite(INT16U x,INT16U y,INT16U w,INT16U h,Color *d)
{
   #if TFT_EN>0
	INT16U i,j;
 	for(i=0;i<h;i++)
	{
 		TFT_SetCursor(x,y+i);   	//设置光标位置 
		TFT_WriteRAM_Prepare();     //开始写入GRAM
		for(j=0;j<w;j++)TFT->TFT_RAM=d[i*w+j];//写入数据 
	}	  
    #elif LTDC_EN>0
    LTDC_Color_Fill(x,y,w+x-1,h+y-1,d);
	#elif TFT_ILI9341_EN>0
	INT32U index=0;      
	INT32U totalpoint=w*h;
	Draw_Pos_Size(x,y, w, h);
	LCD_WriteCommand(0x2C);
	for(index=0;index<totalpoint;index++)
	{
		LCD_Write_Data(*d++);		   			  
	}
	

   #endif
}
//显示字符
//INT16U x,INT16U y:起点坐标
//  char dat：字符
//  BL mode:叠加方式(1)还是非叠加方式(0)
//返回：无
//注意：字体信息部分可以直接用字体提供的信息三元组代替
void ScrCharWrite(INT16U x,INT16U y,const char dat,BL mode)
{
    INT8U temp,t1=y,t,t2;
	INT16U x1=0;    			     
    const INT8U *rd=FontData;
	//设置窗口		   
	if(dat<' ')return;
	//dat=dat-' ';//得到偏移后的值
	rd+=(dat-' ')*ScrFontSize;
	    for(t=0;t<ScrFontSize;t++)
	    {   
			temp=*(rd++);
	        for(t2=0;t2<8;t2++)
			{		
                if(mode&&((temp&0x01)==0)){temp>>=1;continue;}
//				if(y+t1>=TFTdev.width){return;}//超区域了
				if(!TFT_DrawPoint(x+x1,y++,(temp&0x01)?ScrFrontColor:ScrBackColor))return;	
				temp>>=1;
			}  	 
//			if(x>=TFTdev.width){return;}//超区域了
			x1++;
			if(x1>=ScrFontWidth)
			{
				x1=0;
				t1+=8;
			}
			y=t1;
			
	    }   
	return;
}
//显示字符串
//INT16U x,INT16U y:起点坐标
//INT16U w,INT16U h:区域大小  
//  char *dat：字符串
//  BL mode:叠加方式(1)还是非叠加方式(0)
//返回：无
//注意：字体信息部分可以直接用字体提供的信息三元组代替

void ScrStringWrite(INT16U x,INT16U y,INT16U w,INT16U h,const char *dat,BL mode)
{
	INT8U x0=x;
	if(w<0xffff)w+=x;
	if(h<0xffff)h+=y;
    while((*dat<='~')&&(*dat>'\000'))//判断是不是非法字符!
    {       
        if((x>=w)||(*dat=='\n')){x=x0;y+=ScrFontHeightPage;dat++;continue;}
        if(y>=h)break;//退出
        ScrCharWrite(x,y,*dat,mode);
        x+=ScrFontWidth;
        dat++;
    }  

}
//显示数字,高位为0,则不显示
//x,y :起点坐标	 
//len :数字的位数
//num:数值(0~4294967295);	 
INT32U ref_table[10]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
void ScrNumWrite(INT16U x,INT16U y,INT8U len,INT32U num)
{
	INT8U t,temp;
	BL enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/ref_table[len-t-1])%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				ScrCharWrite(x,y,' ',0);
				continue;
			}else enshow=1; 
		 	 
		}
		ScrCharWrite(x,y,temp+'0',0);
	}

}

//画水平线
//x0,y0:坐标
//len:线长度
//color:颜色
void ScrHLineDraw(INT16U x0,INT16U y0,INT16U len)
{
	if(len==0)return;
	ScrFill(x0,y0,len,1);	
}
//画实心圆
//x0,y0:坐标
//r:半径
//color:颜色
void ScrFillCircleDraw(INT16U x0,INT16U y0,INT16U r)
{											  
	INT32U i;
	INT32U imax = ((INT32U)r*707)/1000+1;
	INT32U sqmax = (INT32U)r*(INT32U)r+(INT32U)r/2;
	INT32U x=r;
	ScrHLineDraw(x0-r,y0,2*r);
	for (i=1;i<=imax;i++) 
	{
		if ((i*i+x*x)>sqmax)// draw lines from outside  
		{
 			if (x>imax) 
			{
				ScrHLineDraw (x0-i+1,y0+x,2*(i-1));
				ScrHLineDraw (x0-i+1,y0-x,2*(i-1));
			}
			x--;
		}
		// draw lines from inside (center)  
		ScrHLineDraw(x0-x,y0+i,2*x);
		ScrHLineDraw(x0-x,y0-i,2*x);
	}
}  
//两个数之差的绝对值 
//x1,x2：需取差值的两个数
//返回值：|x1-x2|
INT16U my_abs(INT16U x1,INT16U x2)
{			 
	if(x1>x2)return x1-x2;
	else return x2-x1;
}  
//画一条粗线
//(x1,y1),(x2,y2):线条的起始坐标
//size：线条的粗细程度
//color：线条的颜色
void ScrBLineDraw(INT16U x1, INT16U y1, INT16U x2, INT16U y2,INT8U size)
{
	INT16U t; 
	INT16S xerr=0,yerr=0,delta_x,delta_y,distance; 
	INT16S incx,incy,uRow,uCol; 
	//if(x1<size)x1=size;//|| x2<size||y1<size|| y2<size)return; 
	//if(y1<size)y1=size;	
	//if(x2<size)x2=size;	
	//if(y2<size)y2=size;	
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		ScrFillCircleDraw(uRow,uCol,size);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}   


#endif
