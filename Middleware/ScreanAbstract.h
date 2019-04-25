#ifndef _SCREANBASTRACT_H
#define _SCREANBASTRACT_H
#if SCR_EN>0

//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
//#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

extern INT16U ScrWidth,ScrHeight;

extern INT8U ScrFontWidth,ScrFontHeightPage;
extern INT16U ScrFontSize;
extern Color ScrFrontColor,ScrBackColor;


void ScrClear(void);
INT16U ScrGetFontWidth(void);
void ScrColorSet(Color Front,Color Back);
void ScrFontSet(INT8U fontwidth,INT16U fontsize,const INT8U *fontdat);

void ScrRectangleDraw(INT16U x1, INT16U y1, INT16U x2, INT16U y2);
void ScrCircleDraw(INT16U x0,INT16U y0,INT8U r);
void ScrLineDraw(INT16U x1, INT16U y1, INT16U x2, INT16U y2);
void ScrFill(INT16U x,INT16U y,INT16U w,INT16U h);
void ScrBLineDraw(INT16U x1, INT16U y1, INT16U x2, INT16U y2,INT8U size );
void ScrFillCircleDraw(INT16U x0,INT16U y0,INT16U r );


void ScrImageWrite(INT16U x,INT16U y,INT16U w,INT16U h,Color *d);
void ScrCharWrite(INT16U x,INT16U y,const char dat,BL mode);
void ScrStringWrite(INT16U x,INT16U y,INT16U w,INT16U h,const char *dat,BL mode);
void ScrNumWrite(INT16U x,INT16U y,INT8U len,INT32U num);

#define LCDClear(a) ScrColorSet(ScrFrontColor,ScrBackColor);ScrClear()
#define LCDWriteStringRaw(page,x,f,d)	ScrFontSet(f);ScrStringWrite((x),(page)<<3,0xffff,0xffff,d,0)
#define LCDWriteCharRaw(page,x,f,d)	ScrFontSet(f);ScrCharWrite((x),(page)<<3,d,0)

#endif
#endif

