#ifndef _GUI_H


#define _GUI_H


#if GUI_EN>0


#define GUI_BLACK_V_S 0//黑白，字节竖排，b0在上，从左向右，从上到下


#define GUI_GRAY_8 1//unused


#define GUI_COLOR_8 2//unused


#define GUI_COLOR_32 3//unused









typedef struct s_Widget{


	INT8U X;


	INT8U Y;


  INT8U Width;


  INT8U Height;


  const INT8U *pBuf;


//    INT8U FocusIndex;


  BL (*pEventHandler)(const Event *);


  struct s_Widget *Parent;


  LINKLIST_STRUCT(s_Widget)


} Widget;








void GUIInit(void);


void GUIRefresh(void);


void GUIWidgetAdd(Widget *w);


void GUIWidgetRemove(Widget *w);


void GUIWidgetSetFocus(Widget *w);


BL GUIEventSent(Event *e);





void WidgetLineDraw(INT8U x,INT8U y,INT8U w,INT8U h);


void WidgetSringDraw(INT8U x,INT8U y,INT8U fontwidth,INT16U fontsize,const INT8U *fontdat,char *dat);


void WidgetRectangleDraw(INT8U x,INT8U y,INT8U w,INT8U h);





//void GUIRefreshHook(void);





#endif


#endif





