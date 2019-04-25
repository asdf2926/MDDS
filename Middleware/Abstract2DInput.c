#include "includes.h"
#if AINPUT2D_EN>0
INT16U AInput2DInput[AINPUT2D_POINT_COUNT][2];
BL AInput2DAvailable[AINPUT2D_POINT_COUNT];

//void (*CallBack)(AInput2D);
INT16U    AI2DLastPoint   [AINPUT2D_POINT_COUNT][2];
AInput2D  AI2DStatus      [AINPUT2D_POINT_COUNT];
INT16U    AI2DV           [AINPUT2D_POINT_COUNT][2];

MAKE_BUFFER(AI2D,AInput2D,AINPUT2D_BUFFER_LEN,INT8U,,)
void AInput2DInit(void)
{
    INT8U i;
//    CallBack=0;
    for(i=0;i<AINPUT2D_POINT_COUNT;i++)
    {
        AI2DStatus[i].Status=Input2DNone;
        AI2DStatus[i].index=i;
    }
	BasicTimerAdd(10000,0,AInput2DProcess_10ms);
}
/*AInput2D AInput2DGet(void )
{
    
}void AInput2DCallBackSet(void (*pCallBack)(AInput2D))
{
    CallBack=pCallBack;
}
*/


void AInput2DProcess_10ms(INT8U num)
{
	num=num;
    INT8U i,count=AINPUT2D_POINT_COUNT;
    AInput2D t1;
    AInput2DRefreshHook();
    for(i=0;i<AINPUT2D_POINT_COUNT;i++)
    {
        switch(AI2DStatus[i].Status)
        {
            case Input2DNone:
                if(AInput2DAvailable[i])
                {
                    AI2DStatus[i].Status=Input2DDown;
                    AI2DStatus[i].x=AInput2DInput[i][0];
                    AI2DStatus[i].y=AInput2DInput[i][1];
                    AI2DStatus[i].TimeMs=0;
                    AI2DStatus[i].vx=0;
                    AI2DStatus[i].vy=0;
                    AI2DStatus[i].zoom=1;
                }
            break;
            case Input2DDown:
                if(AInput2DAvailable[i])
                {
                    AI2DStatus[i].Status=Input2DHold;
                    AI2DLastPoint[i][0]=AInput2DInput[i][0];
                    AI2DLastPoint[i][1]=AInput2DInput[i][1];
                } else AI2DStatus[i].Status=Input2DNone;
            break;
            case Input2DUp:
                if(AInput2DAvailable[i])
                {
                    AI2DStatus[i].Status=Input2DHold;
                } else AI2DStatus[i].Status=Input2DNone;
            break;
            case Input2DMoveStart:
                if(AInput2DAvailable[i])
                {
                    AI2DStatus[i].Status=Input2DMove;
                    AI2DStatus[i].TimeMs+=10;
                } else AI2DStatus[i].Status=Input2DUp;
            break;
            case Input2DMove:
                if(AInput2DAvailable[i])
                {
                AI2DStatus[i].x=AInput2DInput[i][0];
                AI2DStatus[i].y=AInput2DInput[i][1];
                AI2DStatus[i].TimeMs+=10;
                AI2DStatus[i].vx=(AI2DStatus[i].vx*15+((INT16S)AInput2DInput[i][0]-AI2DStatus[i].x)*100)>>4;
                AI2DStatus[i].vy=(AI2DStatus[i].vy*15+((INT16S)AInput2DInput[i][1]-AI2DStatus[i].y)*100)>>4;
                AInput2DInput[i][0]=AI2DStatus[i].x;
                AInput2DInput[i][1]=AI2DStatus[i].y;

                }else AI2DStatus[i].Status=Input2DUp;
            break;
            case Input2DHold:
                    AI2DStatus[i].y=AInput2DInput[i][1];
                if(AInput2DAvailable[i])
                {
                    AI2DStatus[i].x=AInput2DInput[i][0];
                    AI2DStatus[i].TimeMs+=10;
                    if(AINPUT2D_DPI_X/5<CalcDistance(AI2DStatus[i].x,AI2DStatus[i].y,AI2DLastPoint[i][0],AI2DLastPoint[i][1]))
                    {
                        AI2DStatus[i].Status=Input2DMoveStart;
                        
                    }
                }else AI2DStatus[i].Status=Input2DUp;
            break;
        }
        if(AI2DStatus[i].Status==Input2DNone)count--;
    }
    if(count==1)
    {
        for(i=0;i<AINPUT2D_POINT_COUNT;i++)
        {
            if(AI2DStatus[i].Status!=Input2DNone)BufAI2DW(&AI2DStatus[i],1);
        }
    }else{
		for(i=0;i<AINPUT2D_POINT_COUNT;i++)
		{
			t1=AI2DStatus[i];
			if(t1.Status==Input2DNone)continue;
			if(t1.Status==Input2DHold||t1.Status==Input2DMove)t1.Status=Input2DMulti;
			BufAI2DW(&t1,1);
		}

    }
    while(BufAI2DLen)
    {
        t1=BufAI2DRB();
        //(*CallBack)(t1);
		AInput2DCallBack(t1);
    }

}

#endif

