#include "includes.h"
#if UILABEL_EN>0
void UILabelEventHandler(UIData* ui,const Event *e)
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
        break;
        case EVENT_REPAINT:
        case EVENT_TIMER:
            ScrFrontColor=((UILabelData *)(ui->ExtData))->FontColor;
			if(((UILabelData *)(ui->ExtData))->AppendMode==0)
				ScrBackColor=((UILabelData *)(ui->ExtData))->BackColor;
		    ScrStringWrite(ui->x,ui->y,ui->w,ui->h,((UILabelData *)(ui->ExtData))->Label,((UILabelData *)(ui->ExtData))->AppendMode);
        break;
        default:
		break;
    }


}
#endif
