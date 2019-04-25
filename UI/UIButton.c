#include "includes.h"
#if UIBUTTON_EN>0


#ifdef PLATFORM_VSCODE
int strlen(const char *StrDest)
{
	int i;
	i=0;
	while((*StrDest++)!='\0')
	{ 
		i++;
	}//这个循环体意思是从字符串第一个字符起计数，只遇到字符串结束标志'\0’才停止计数
	return i;
}
#endif
void UIButtonPaint(UIData* ui,BL Press)
{
    ScrFrontColor=Press?((UIButtonData *)(ui->ExtData))->PressColor:((UIButtonData *)(ui->ExtData))->BackColor;
    ScrFill(ui->x,ui->y,ui->w,ui->h);
	ScrBackColor=ScrFrontColor;
    ScrFrontColor=((UIButtonData *)(ui->ExtData))->FontColor;
    ScrRectangleDraw(ui->x,ui->y,ui->x+ui->w-1,ui->y+ui->h-1);
	if(strlen(((UIButtonData *)(ui->ExtData))->Label)*ScrFontWidth<ui->w)
		ScrStringWrite(ui->x+ui->w/2-(ScrFontWidth/2*strlen(((UIButtonData *)(ui->ExtData))->Label)),
						ui->y+ui->h/2-ScrFontHeightPage*4,ui->w,ui->h,((UIButtonData *)(ui->ExtData))->Label,0);
	else 
		ScrStringWrite(ui->x,ui->y,ui->w,ui->h,((UIButtonData *)(ui->ExtData))->Label,0);
}
void UIButtonEventHandler(UIData* ui,const Event *e)
{
    switch(e->Type)
    {
        case EVENT_CREATE:
        break;
        case EVENT_DESTROY:
        break;
        case EVENT_POWERPOLICY:
        break;
        case EVENT_KEY:
        break;
        case EVENT_INPUT_2D:
            switch(((AInput2D *)(e->ExternData))->Status)
            {
                case  Input2DDown:
                    UIButtonPaint(ui,1);
                break;
                case Input2DUp:
                    UIButtonPaint(ui,0);
                    if( (0<=     ((AInput2D *)e->ExternData)->x)&&
                        (0<=     ((AInput2D *)e->ExternData)->y)&&
                        (ui->w> ((AInput2D *)e->ExternData)->x)&&
                        (ui->h> ((AInput2D *)e->ExternData)->y))
                        (*(((UIButtonData *)(ui->ExtData))->CallBack))(ui);
                break;
                default:
                break;
            }
        break;
        case EVENT_REPAINT:
            UIButtonPaint(ui,0);
        break;
        case EVENT_TIMER:
        break;
        default:
		break;
    }


}

#endif
