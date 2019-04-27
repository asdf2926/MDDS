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
//--------------------AppendLayer--------------
#define APPENDLAYER_EN 1
#if APPENDLAYER_EN>0
#define APPENDLAYER_BUFFERSIZE 40
#define APPENDLAYER_FORMAT "Temp:%.2f"
#define APPENDLAYER_VARIABLES AVariableFloat[0]
#define APPENDLAYER_X ScrWidth-APPENDLAYER_W
#define APPENDLAYER_Y 0
#define APPENDLAYER_W 8*10
#define APPENDLAYER_H 40
#endif
//--------------------CanvasBasic--------------
#define CANVASBASIC_EN 1
#endif
