#include "includes.h"
#if GUI_EN>0
LINKLIST_MAKE(s_Widget)

//INT8U CurFocus;
void GUIMixture()
{
	Widget *i;
	INT16U index;
	INT16U r,pbuf1;
	INT8U x,ypage;
	#define LR_NUM (i->Y&0x7)
	#define MASK_H (0xff>>(8-(i->Height&0x7)))
	LINKLIST_FOREACH_BACK(i,s_Widget)
	{
		index=0;
		for(ypage=0;ypage<(i->Height>>3);ypage++)
		{
		if(ypage+(i->Y>>3)>7)return;
		for(x=0;x<i->Width;x++)
		{
			if(i->X+x>127)break;
		//get buffer(2 bytes)
		pbuf1=(((INT16U)(i->Y>>3)+ypage)<<7)|(i->X+x);
		r=GUI_BUF_NAME[pbuf1]|
			(LCDBuffer[pbuf1+128]<<8);
		//clear
		r&=~((INT16U)0xff<<LR_NUM);
		//append
		r|=(INT16U)(i->pBuf[index++])<<LR_NUM;
		//write back
		LCDBuffer[pbuf1]=r&0xFF;
		if(pbuf1+128<1024)LCDBuffer[pbuf1+128]=r>>8;
		}
		}
		if(i->Height&0x3)
		{
			for(x=0;x<i->Width;x++)
			{
				if(i->X+x>127)break;
			//get buffer(2 bytes)
			pbuf1=(((INT16U)(i->Y>>3)+ypage)<<7)|(i->X+x);
			r=GUI_BUF_NAME[pbuf1]|
				(LCDBuffer[pbuf1+128]<<8);
			//clear
			r&=~(MASK_H<<LR_NUM);
			//append
			r|=(i->pBuf[index++]&MASK_H)<<LR_NUM;
			//write back
			LCDBuffer[pbuf1]=r&0xFF;
			if(pbuf1+128<1024)LCDBuffer[pbuf1+128]=r>>8;
			}
				
		}
	}
}

void GUIInit(void)
{
    LINKLIST_INIT(s_Widget)
//    CurFocus=0;
}
void GUIRefresh(void)
{
    GUIMixture();
    GUI_REFRESH_HOOK();
}
void GUIWidgetAdd(Widget *w)
{
//    w->FocusIndex=++CurFocus;
	const Event e={EVENT_REPAINT,0};
    LINKLIST_ADD_FIRST(s_Widget,w)
		if(w->pEventHandler)(*(w->pEventHandler))(&e);


	
}
void GUIWidgetRemove(Widget *w)
{
    LINKLIST_REMOVE(s_Widget,w);
}
void GUIWidgetSetFocus(Widget *w)
{
//	Widget *i,*j;
//	INT8U x,y;
/*	if(CurFocus>=254)
	{
		for(x=0;x<255;x++)
		{	
			y=255;
			LINKLIST_FOREACH(i,s_Widget)
			{
				if((i->FocusIndex<=y)&&(i->FocusIndex>=x))
				{
					y=i->FocusIndex;
					j=i;
				}
			}
			j->FocusIndex=x;
			if(y<255)CurFocus=x;
		}
		
	}
	w->FocusIndex=++CurFocus;
	*/
    LINKLIST_REMOVE(s_Widget,w);
    LINKLIST_ADD_FIRST(s_Widget,w)
}
BL GUIEventSent(Event *e)
{
//	INT8U i;
	Widget *j;
/*	for(i=CurFocus;i>0;i--)
	{
			LINKLIST_FOREACH(j,s_Widget)
			{
				if(j->FocusIndex==i)
				{
					if((*(j->pEventHandler))(e))
					{
						return 1;
					}
					break;
				}
			}		
	}
	return 0;
	*/
	LINKLIST_FOREACH(j,s_Widget)
	{
		if(j->pEventHandler==NULL)continue;
		if((*(j->pEventHandler))(e))
		{
			return 1;
		}
	}		
	return 0;
}

void WidgetLineDraw(INT8U x,INT8U y,INT8U w,INT8U h)
{
	
}
void WidgetSringDraw(INT8U x,INT8U y,INT8U fontwidth,INT16U fontsize,const INT8U *fontdat,char *dat)
{
	
}
void WidgetRectangleDraw(INT8U x,INT8U y,INT8U w,INT8U h)
{
	
}

#endif
