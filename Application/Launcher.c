#include "includes.h"
BL AELauncherEventHandler(struct s_AppE *app,const Event *e);
AppE AppLauncher={AELauncherEventHandler};

const char *AppString[APP_COUNT]={APP_MENU};
AppE *AppList[APP_COUNT]={APP_STRUCT};
void menuchosen(INT8S chosen);
MenuData LauncherData={AppString,menuchosen,APP_COUNT};
AppE launMenu={AEMenuEventHandler};
BL en;INT8U index;
void menuchosen(INT8S chosen)
{
    if(chosen>=0)en=1;
    index=(INT8U)chosen;
    AppERemove(&AppLauncher);
    if(en)
    {
        AppEAdd(AppList[index],0);
    }
}
BL AELauncherEventHandler(struct s_AppE *app,const Event *e)
{
    switch(e->Type)
    {
        case EVENT_CREATE:
            en=0;
            AppEAdd(&launMenu,&LauncherData);
        break;
        case EVENT_DESTROY:
            if(en==0)AppERemove(&launMenu);
        break;
        case EVENT_POWERPOLICY:
        break;
        case EVENT_KEY:
        break;
        case EVENT_REPAINT:
        break;
        case EVENT_TIMER:
        break;
        default:
        return 0;
    }
    return 1;

}


