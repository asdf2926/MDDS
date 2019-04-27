#include "includes.h"
BL AETimeSetEventHandler(struct s_AppE *app,const Event *e);
AppE AppTimeSet={AETimeSetEventHandler};

INT8U Cursor;//0~13
const INT8U PoiTable[]={0,1,2,3,5,6,8,9,0x0b,0xc,0,1,3,4,6,7},
MaxTable[]={9,9,9,9,1,9,3,9,0,6,2,9,5,9,5,9};
INT8U dat[16];
/*
 0123456789abcdef
+----------------+
|2019/01/01 00   |0
|^               |2
|00:00:00        |4
|                |6
+----------------+


*/
char pp[17];
void MoveCursor(INT8U n)
{
    LCDWriteCharRaw(Cursor>9?6:2,PoiTable[Cursor]*8,FONT_ASCII0816,' ');
    LCDWriteCharRaw(n>9?6:2,PoiTable[n]*8,FONT_ASCII0816,'^');
    Cursor=n;
}
void IncDat()
{
    dat[Cursor]++;
    if(dat[Cursor]>MaxTable[Cursor])dat[Cursor]=0;
    LCDWriteCharRaw(Cursor>9?4:0,PoiTable[Cursor]*8,FONT_ASCII0816,'0'+dat[Cursor]);
    
}

BL AETimeSetEventHandler(struct s_AppE *app,const Event *e)
{
    INT8U i,j;
    switch(e->Type)
    {
        case EVENT_CREATE:
            ConventTimeToArray(RTCTimeRGet(),dat);
            j=15;
            for(i=7;i<0x80;i--)
            {
                dat[j--]=dat[i]%10;
                dat[j--]=dat[i]/10;
            }
            Cursor=0;
        break;
        case EVENT_DESTROY:
			TIMESET_FINISH_OP
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
                            IncDat();
                        break;
                        case VK_F2:
                            MoveCursor((Cursor+1)%16);
                        break;
                        default:break;
                    }
                break;
                case KeyLongStart:
                    LCDClear(0);
                case KeyLongRelease:
                    switch(((AButton *)(e->ExternData))->KeyCode)
                    {
                        case VK_F1:
                            AppEActionPend(app,AppERemove,0);//AppERemove(&AppTimeSet);
                        return 1;
                        case VK_F2:
                            j=0;
                            for(i=0;i<8;i++)
                            {
                                dat[i]=dat[j]*10+dat[j+1];
                                j+=2;
                            }
                            dat[8]=dat[9]=0;
                            RTCTimeRSet(ConventArrayToTime(dat));
                            AppEActionPend(app,AppERemove,0);//AppERemove(&AppTimeSet);
                        return 1;
                        default:break;
                    }
                break;
                default:
                break;
            }
        break;
        case EVENT_REPAINT:
			LCDClear(0);
			pp[16]=0;
            for(i=0;i<16;i++)pp[i]=' ';
            for(i=0;i<10;i++)pp[PoiTable[i]]='0'+dat[i];
            pp[4]=pp[7]='/';
            LCDWriteStringRaw(0,0,FONT_ASCII0816,pp);
            for(i=0;i<0xd;i++)pp[i]=' ';
            for(i=10;i<16;i++)pp[PoiTable[i]]='0'+dat[i];
            pp[2]=pp[5]=':';
            LCDWriteStringRaw(4,0,FONT_ASCII0816,pp);
            MoveCursor(0);
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
