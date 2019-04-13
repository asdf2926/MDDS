#ifndef _APPE_H
#define _APPE_H
//#if APPE_EN>0

#define EVENT_KEY 1
#define EVENT_REPAINT 2
#define EVENT_TIMER 3
#define EVENT_CREATE 0x80
#define EVENT_DESTROY 0x81
#define EVENT_POWERPOLICY 0xC0
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
        case EVENT_REPAINT:
        break;
        case EVENT_TIMER:
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

void AppEInit(void);
void AppEAdd(AppE *app,void *extdata);
void AppEReplace(AppE *app,void *extdata);
void AppERemove(AppE *app);
void AppEFocusSet(AppE *app);
BL AppEEventSent(Event *e);
void AppEAButtonCallBack(INT8U key,enum e_KeyStatus state);
#if BTIMER_COUNT>0
void AppTimerStart(AppE *app,INT32U TimeUS,BL SingleShot);
void AppTimerStop(AppE *app);
void AppBTimerCallBack(INT8U index);
#endif
//#endif

#endif
