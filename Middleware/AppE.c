#include "includes.h"
#if APPE_EN>0
LINKLIST_MAKE(s_AppE)
MAKE_BUFFER(AppEPend,AppEPendAct,APPE_PEND_BUF_MAX,INT8U,,)
AppE *AppEFocusOn;
void AppEInit()
{
	LINKLIST_INIT(s_AppE);
	AppEFocusOn=NULL;
}
BL AppCheck(AppE *app)
{
	AppE *j;
	LINKLIST_FOREACH(j,s_AppE)
		if(j==app)return 0;
	return 1;
}
void AppEAdd(AppE *app,void *extdata)
{
	Event e={EVENT_CREATE,extdata};
#if BTIMER_COUNT>0
    app->Timer=-1;
#endif
    //LINKLIST_ADD_FIRST(s_AppE,app)
	if(AppEFocusOn)
	{
		LINKLIST_INSERT_FRONT(s_AppE,app,AppEFocusOn)
		AppEFocusOn=app;
	}else{
		LINKLIST_ADD_FIRST(s_AppE,app)
		AppEFocusOn=ps_AppEFirst;
	}
	if(app->pEventHandler)
    {
        (*(app->pEventHandler))(app,&e);
        e.Type=EVENT_REPAINT;
		e.ExternData=0;
        (*(app->pEventHandler))(app,&e);
    }
}
void AppERemove(AppE *app,void *extdata)
{
	Event e={EVENT_DESTROY,extdata};
	if(AppCheck(app))return;
	AppTimerStop(app);
 	if(app->pEventHandler)
        (*(app->pEventHandler))(app,&e);
	if(AppEFocusOn==app)AppEFocusOn=AppEFocusOn->Next;
	LINKLIST_REMOVE(s_AppE,app);
	if(ps_AppEFirst==NULL){AppEFocusOn=NULL;return;}
	e.Type=EVENT_REPAINT;
 	if(AppEFocusOn->pEventHandler)
		(*(AppEFocusOn->pEventHandler))(ps_AppEFirst,&e);
}
void AppEReplace(AppE *app,void *extdata)
{
	AppE *i;
	Event e={EVENT_DESTROY,0};
	//AppTimerStop(ps_AppEFirst);
 	if(AppEFocusOn->pEventHandler)
        (*(AppEFocusOn->pEventHandler))(app,&e);
	//i=ps_AppEFirst;
	i=AppEFocusOn;
	LINKLIST_REMOVE(s_AppE,i);
	//e.Type=EVENT_REPAINT;
	AppEFocusOn=AppEFocusOn->Next;
	AppEAdd(app,extdata);
}
void AppEFocusSet(AppE *app)
{
	Event e={EVENT_LOSTFOCUS,0};
	if(AppCheck(app))return;
 	if(app->pEventHandler)
        (*(app->pEventHandler))(app,&e);
	LINKLIST_REMOVE(s_AppE,app);
    LINKLIST_INSERT_FRONT(s_AppE,app,AppEFocusOn)
 	if(app->pEventHandler)
	{
		e.Type=EVENT_FOCUS;
        (*(app->pEventHandler))(app,&e);
		e.Type=EVENT_REPAINT;
        (*(app->pEventHandler))(app,&e);

	}
}

void AppESetOnTop()
{
	Event e={EVENT_LOSTFOCUS,0};
 	if(AppEFocusOn->pEventHandler)
        (*(AppEFocusOn->pEventHandler))(AppEFocusOn,&e);
	AppEFocusOn=AppEFocusOn->Next;
	if(AppEFocusOn==ps_AppELast)return;
	e.Type=EVENT_FOCUS;
 	if(AppEFocusOn->pEventHandler)
        (*(AppEFocusOn->pEventHandler))(AppEFocusOn,&e);
	
}


BL AppEEventSent(Event *e)
{
	AppE *j;
	if(ps_AppEFirst==NULL)return 0;
	if(e->Type&0x80)if((AppEFocusOn->pEventHandler)&&((*(AppEFocusOn->pEventHandler))(AppEFocusOn,e)))return 1;
	LINKLIST_FOREACH(j,s_AppE)
	{
		if(j->pEventHandler==NULL)continue;
		if((*(j->pEventHandler))(j,e))
		{
			return 1;
		}
	}
	return 0;
}
void AppEAButtonCallBack(INT8U key,enum e_KeyStatus state)
{
	AButton a={key,state};
	Event e={EVENT_KEY,&a};
	AppEEventSent(&e);
}
void AppEActionPend(AppE *app,void (*act)(AppE *,void *),void *extdata)
{
	AppEPendAct a={app,act,extdata};
	BufAppEPendPush(a);
}
void AppEPendSolve(void)
{
	AppEPendAct a;
	if(BufAppEPendR(&a,1))return;
	(*(a.act))(a.application,a.externData);
}

#if BTIMER_COUNT>0
void AppTimerStart(AppE *app,INT32U TimeUS,BL SingleShot)
{
    if(app->Timer!=-1)return;
    app->Timer=BasicTimerAdd(TimeUS,SingleShot,AppBTimerCallBack);
}
void AppTimerStop(AppE *app)
{
    if(app->Timer==-1)return;
    BasicTimerDel(app->Timer);
    app->Timer=-1;
}
void AppBTimerCallBack(INT8U index)
{
	const Event e={EVENT_TIMER,0};
	AppE *j;
	LINKLIST_FOREACH(j,s_AppE)
	{
		if(j->pEventHandler==NULL)return;
		if(j->Timer==index)(*(j->pEventHandler))(j,&e);
		if(j==AppEFocusOn)return;
	}
}
void AInput2DCallBack(AInput2D d)
{
	Event e={EVENT_INPUT_2D,&d};
	AppEEventSent(&e);

}	
#endif

#endif
