#include "includes.h"
#if APP_MENU_EN>0
BL AEMenuEventHandler(AppE *app,const Event * e);
AppE AppMenu={AEMenuEventHandler};
//BL Lock=0;
/*void AEMenuStart(const char*dat[],INT8U MenuCount,void (*CallBack)(INT8S chosen))
{
    if(Lock)return;
    Lock=1;
    MenuStringList=dat;
    MenuListCount=MenuCount;
    MenuCurItem=0;
    MenuDispIndex=0;
    CB=CallBack;
    AppEAdd(&AppMenu);
}
INT8U MenuListCount,MenuCurItem,MenuDispIndex;

*/
void Repaint(const char**MenuStringList,INT8U MenuListCount,INT8U *MenuCurItem,INT8U *MenuDispIndex)
{
    LCDClear(0);
    LCDWriteCharRaw((*MenuCurItem<*MenuDispIndex?MenuListCount+*MenuCurItem-*MenuDispIndex:*MenuCurItem-*MenuDispIndex)<<1,120,FONT_ASCII0816,'<');
    LCDWriteStringRaw(0,0,FONT_ASCII0816,MenuStringList[*MenuDispIndex]);
	if(MenuListCount<=1)return;
    LCDWriteStringRaw(2,0,FONT_ASCII0816,MenuStringList[(*MenuDispIndex+1)%MenuListCount]);
	if(MenuListCount<=2)return;
    LCDWriteStringRaw(4,0,FONT_ASCII0816,MenuStringList[(*MenuDispIndex+2)%MenuListCount]);
	if(MenuListCount<=3)return;
    LCDWriteStringRaw(6,0,FONT_ASCII0816,MenuStringList[(*MenuDispIndex+3)%MenuListCount]);
	if(MenuListCount<=4)return;
}
void IncCursor(const char**MenuStringList,INT8U MenuListCount,INT8U *MenuCurItem,INT8U *MenuDispIndex)
{
    if((*MenuCurItem<*MenuDispIndex?MenuListCount+*MenuCurItem-*MenuDispIndex:*MenuCurItem-*MenuDispIndex)>=3)//||(*MenuDispIndex-*MenuCurItem))
    {
        (*MenuDispIndex)++;
        (*MenuCurItem)++;
		*MenuDispIndex%=MenuListCount;
        *MenuCurItem%=MenuListCount;
		Repaint(MenuStringList,MenuListCount,MenuCurItem,MenuDispIndex);
        return;
    }else{
        LCDWriteCharRaw((*MenuCurItem<*MenuDispIndex?MenuListCount+*MenuCurItem-*MenuDispIndex:*MenuCurItem-*MenuDispIndex)<<1,120,FONT_ASCII0816,' ');
        (*MenuCurItem)++;
        *MenuCurItem%=MenuListCount;
        LCDWriteCharRaw((*MenuCurItem<*MenuDispIndex?MenuListCount+*MenuCurItem-*MenuDispIndex:*MenuCurItem-*MenuDispIndex)<<1,120,FONT_ASCII0816,'<');
    }
}
BL AEMenuEventHandler(struct s_AppE *app,const Event * e)
{
    MenuData *curmenu=app->p;
    switch(e->Type)
    {
        case EVENT_CREATE:
            curmenu=app->p=e->ExternData;
			curmenu->Status=Idle;
            LCDClear(0);
        break;
        case EVENT_DESTROY:
//            Lock=0;
        break;
        case EVENT_POWERPOLICY:
        break;
        case EVENT_KEY:
            switch(((AButton *)(e->ExternData))->Status)
            {
                case KeyShortRelease:
                    switch(((AButton *)(e->ExternData))->KeyCode)
                    {
                        case VK_F1:
                            IncCursor(curmenu->MenuStringList,curmenu->MenuListCount,&(curmenu->MenuCurItem),&(curmenu->MenuDispIndex));
                        break;
                        case VK_F2:
                            curmenu->Status=OK;
                            //AppERemove(app);
                            AppEActionPend(app,AppERemove,0);
                        return 1;
                        default:break;
                    }
                break;
                case KeyLongStart:
                    switch(((AButton *)(e->ExternData))->KeyCode)
                    {
                        case VK_F1:
                            //IncCursor(curmenu->MenuStringList,curmenu->MenuListCount,curmenu->MenuCurItem,curmenu->MenuDispIndex);
                            LCDClear(0);
                        break;
                        case VK_F2:
                        return 1;
                        default:break;
                    }
                case KeyLongRelease:
                    switch(((AButton *)(e->ExternData))->KeyCode)
                    {
                        case VK_F1:
                            //IncCursor(curmenu->MenuStringList,curmenu->MenuListCount,curmenu->MenuCurItem,curmenu->MenuDispIndex);
                            curmenu->Status=Abort;
//                            AppERemove(app);
                            AppEActionPend(app,AppERemove,0);
                        return 1;
                        case VK_F2:
                            curmenu->Status=OK;
//                            AppERemove(app);
                            AppEActionPend(app,AppERemove,0);
                        return 1;
                        default:break;
                    }
					Repaint(curmenu->MenuStringList,curmenu->MenuListCount,&(curmenu->MenuCurItem),&(curmenu->MenuDispIndex));
                break;
                default:

                break;
            }
        break;
        case EVENT_REPAINT:
            Repaint(curmenu->MenuStringList,curmenu->MenuListCount,&(curmenu->MenuCurItem),&(curmenu->MenuDispIndex));
        break;
        case EVENT_FOCUS:
        break;
        case EVENT_LOSTFOCUS:
        break;
        case EVENT_TIMER:
        break;
        default:
        return 0;
    }
    return 1;
}
#endif

