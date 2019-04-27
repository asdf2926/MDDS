#include "includes.h"
#if APPENDLAYER_EN>0

void MyButtonPress(UIData *ui);
BL MyAppEventHandler(struct s_AppE *app,const Event *e);

char AEALBuf[APPENDLAYER_BUFFERSIZE+1];
UILabelData AEALLabel={AEALBuf,BLACK,1};
UIData AEAppendLayerUI[]={
    {UILabelEventHandler,0,0,50,50,&AEALLabel},
    {0}};

AppE AppAppendLayer={AEAppendLayerEventHandler};

BL AEAppendLayerEventHandler(struct s_AppE *app,const Event *e)
{
	switch(e->Type)
    {
        case EVENT_CREATE:
            AppTimerStart(app,100000,0);
            AEAppendLayerUI[0].x=APPENDLAYER_X;
            AEAppendLayerUI[0].y=APPENDLAYER_Y;
            AEAppendLayerUI[0].w=APPENDLAYER_W;
            AEAppendLayerUI[0].h=APPENDLAYER_H;
			AppESetOnTop();
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
            snprintf(AEALBuf,APPENDLAYER_BUFFERSIZE,APPENDLAYER_FORMAT,APPENDLAYER_VARIABLES);
        break;
        default:
        break;
    }
    UIEventHandler(AEAppendLayerUI,e);
    return 0;
}


#endif
