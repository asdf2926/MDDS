#include "includes.h"
//
void ClearButtonPress(UIData *ui);
void CloseButtonPress(UIData *ui);
BL CanvasBasicEventHandler(struct s_AppE *app,const Event *e);


UICanvasData AECBCanvas1={7,WHITE,BLACK};
UIButtonData AECBButtonClear={"Clear",BLACK,LGRAYBLUE,LBBLUE,ClearButtonPress};
UIButtonData AECBButtonClose={"Close",BLACK,LGRAYBLUE,LBBLUE,CloseButtonPress};


UIData AppCanvasBasicUI[]={
    {UIButtonEventHandler,0,0,65,24,&AECBButtonClear},
    {UICanvasEventHandler,0,24,272,480-24,&AECBCanvas1},
    {UIButtonEventHandler,65,0,65,24,&AECBButtonClose},
    {0}};

AppE AppCanvasBasic={CanvasBasicEventHandler};


void ClearButtonPress(UIData *ui)
{
    //const Event ee={EVENT_REPAINT,0};
    ScrFrontColor=WHITE;
    ScrFill(0,24,272,480-24);
   // AppEActionPend(&AppCanvasBasic,AppEEventSent,&ee);
}
void CloseButtonPress(UIData *ui)
{
    AppEActionPend(&AppCanvasBasic,AppERemove,0);
}

BL CanvasBasicEventHandler(struct s_AppE *app,const Event *e)
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
        break;
        case EVENT_TIMER:
        break;
        case EVENT_FOCUS:
        break;
        case EVENT_LOSTFOCUS:
        break;
        default:
        return 0;
    }
    return UIEventHandler(AppCanvasBasicUI,e);
}


