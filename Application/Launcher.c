#include "includes.h"
BL AELauncherEventHandler(struct s_AppE *app,const Event *e);
AppE AppLauncher={AELauncherEventHandler};

const char *AppString[APP_COUNT]={APP_MENU};
AppE *AppList[APP_COUNT]={APP_STRUCT};
void menuchosen(INT8S chosen);
MenuData LauncherData={AppString,APP_COUNT};
AppE launMenu={AEMenuEventHandler};
BL en;INT8U index;
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
//			AppERemove(app);
            if(LauncherData.Status==Abort)AppERemove(&AppLauncher);
            else if(LauncherData.Status==OK)AppEReplace(AppList[LauncherData.MenuCurItem],0);
        break;
        case EVENT_TIMER:
        break;
        default:
        return 0;
    }
    return 1;

}


