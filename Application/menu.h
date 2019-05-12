#ifndef _MENU_H
#define _MENU_H
#if APP_MENU_EN>0
typedef struct{
    const char**MenuStringList;
    INT8U MenuListCount,MenuCurItem,MenuDispIndex;
    enum{AppMenuIdle,AppMenuAbort,AppMenuOK}Status;
}MenuData;
extern AppE AppMenu;
//void AEMenuStart(const char*dat[],INT8U MenuCount,void (*CallBack)(INT8S chosen));
BL AEMenuEventHandler(struct s_AppE *app,const Event * e);

#endif
#endif
