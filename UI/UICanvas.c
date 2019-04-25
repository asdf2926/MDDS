#include "includes.h"
#if UICANVAS_EN>0
void UICanvasEventHandler(UIData* ui,const Event *e)
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
                    ((UICanvasData *)(ui->ExtData))->lx=((AInput2D *)e->ExternData)->x;
                    ((UICanvasData *)(ui->ExtData))->ly=((AInput2D *)e->ExternData)->y;
                break;
                case  Input2DHold:
                case  Input2DMove:
					if(((AInput2D *)e->ExternData)->x<((UICanvasData *)(ui->ExtData))->PenSize)((AInput2D *)e->ExternData)->x=((UICanvasData *)(ui->ExtData))->PenSize;
 					if(((AInput2D *)e->ExternData)->y<((UICanvasData *)(ui->ExtData))->PenSize)((AInput2D *)e->ExternData)->y=((UICanvasData *)(ui->ExtData))->PenSize;
					if(((AInput2D *)e->ExternData)->x>=ui->w-((UICanvasData *)(ui->ExtData))->PenSize)((AInput2D *)e->ExternData)->x=ui->w-((UICanvasData *)(ui->ExtData))->PenSize-1;
					if(((AInput2D *)e->ExternData)->y>=ui->h-((UICanvasData *)(ui->ExtData))->PenSize)((AInput2D *)e->ExternData)->y=ui->h-((UICanvasData *)(ui->ExtData))->PenSize-1;
                   ScrFrontColor=((UICanvasData *)(ui->ExtData))->PenColor;
                    ScrBLineDraw(ui->x+((UICanvasData *)(ui->ExtData))->lx,
									ui->y+((UICanvasData *)(ui->ExtData))->ly,
									ui->x+((AInput2D *)e->ExternData)->x,
									ui->y+((AInput2D *)e->ExternData)->y,
									((UICanvasData *)(ui->ExtData))->PenSize);
                    ((UICanvasData *)(ui->ExtData))->lx=((AInput2D *)e->ExternData)->x;
                    ((UICanvasData *)(ui->ExtData))->ly=((AInput2D *)e->ExternData)->y;
                break;
                case Input2DUp:
                break;
                default:
                break;
            }
        break;
        case EVENT_REPAINT:
            //ScrImageWrite(ui->x,ui->y,ui->w,ui->h,((UICanvasData *)(ui->ExtData))->paintdata);
            ScrFrontColor=((UICanvasData *)(ui->ExtData))->BackColor;
            ScrFill(ui->x,ui->y,ui->w,ui->h);
        break;
        case EVENT_TIMER:
        break;
        default:
		break;
    }

}

#endif
