#ifndef _CONF_APP_H
#define _CONF_APP_H
//----------------------------------------------
#define APP_MENU_EN 1
//-------------------Launcher-------------------
#define APP_LAUNCHER_EN 1
#if APP_LAUNCHER_EN>0
#define APP_COUNT 2
#define APP_MENU "Time sync","Set time"
#define APP_STRUCT &AETimeSync,&AESetTime//muse be address
#endif
//--------------------TimeSet------------------
#define TIMESET_EN 1
#define TIMESET_FINISH_OP TimeSyncProcess();
#endif
