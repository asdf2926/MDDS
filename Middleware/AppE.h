#ifndef _APPE_H
#define _APPE_H
//#if APPE_EN>0
//any app
#define EVENT_KEY 1
#define EVENT_INPUT_2D 4
//only on focus app
#define EVENT_CREATE 0x80
#define EVENT_DESTROY 0x81
#define EVENT_FOCUS 0x82
#define EVENT_LOSTFOCUS 0x83

#define EVENT_REPAINT 0xC0
#define EVENT_TIMER 0xC1
//not used
#define EVENT_POWERPOLICY 0xE0
/*
BL AE__Handler(struct s_AppE *app,const Event *e);
AppE App__={AE__Handler};
BL AE__Handler(struct s_AppE *app,const Event *e)
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
    return 1;
}

*/
typedef struct{
    INT8U Type;
    void *ExternData;
} Event;
typedef struct s_AppE{
  BL (*pEventHandler)(struct s_AppE *,const Event *);
  void *p;//define by user
#if BTIMER_COUNT>0
    INT8S Timer;
#endif
  LINKLIST_STRUCT(s_AppE)
} AppE;
typedef struct{
    AppE *application;
    void (*act)(AppE *,void *);
    void *externData;
}AppEPendAct;

void AppEInit(void);
void AppEAdd(AppE *app,void *extdata);
//注意：最底层应用不支持
void AppEReplace(AppE *app,void *extdata);
void AppERemove(AppE *app,void *extdata);
void AppEFocusSet(AppE *app);
void AppESetOnTop(void);

BL AppEEventSent(Event *e);
void AppEActionPend(AppE *app,void (*act)(AppE *,void *),void *extdata);
void AppEPendSolve(void);
void AppEAButtonCallBack(INT8U key,enum e_KeyStatus state);
#if BTIMER_COUNT>0
void AppTimerStart(AppE *app,INT32U TimeUS,BL SingleShot);
void AppTimerStop(AppE *app);
void AppBTimerCallBack(INT8U index);
#endif
//#endif

#endif
