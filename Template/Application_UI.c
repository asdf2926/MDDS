#include "includes.h"
//
void MyButtonPress(UIData *ui);
BL MyAppEventHandler(struct s_AppE *app,const Event *e);

UIButtonData Button1={"Button",BLACK,LGRAYBLUE,LBBLUE,MyButtonPress};
UIData MyAppUI[]={
    {UIButtonEventHandler,20,20,80,80,&Button1},
    {0}};

AppE MyApp={MyAppEventHandler};


void MyButtonPress(UIData *ui)
{

}
BL MyAppEventHandler(struct s_AppE *app,const Event *e)
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
        default:
        return 0;
    }
    return UIEventHandler(MyAppUI,e);
}


