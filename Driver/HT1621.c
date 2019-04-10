/*
 * HT1621.c
 *
 *  Created on: 2019年3月2日
 *      Author: asdf2
 */
#include "includes.h"
#if HT1621_EN>0
INT8U HT1621Buffer[16];
#define GETIF(a) _COMB_AB(HT1621_INTERFACE,a)
#define SENDBIT(a)              \
	GETIF(WritePin)(HT1621_WR_PIN,0);              \
	if ((a)==0)                   \
	{                           \
		GETIF(WritePin)(HT1621_DATA_PIN,0);        \
	}                           \
	else                        \
	{                           \
		GETIF(WritePin)(HT1621_DATA_PIN,1);       \
	}                           \
	GETIF(WritePin)(HT1621_WR_PIN,1);


void HT1621ModeSet(INT8U Mode)
{
    INT8U i;
   for(i=0;i<3;i++)
   {
     SENDBIT(Mode&0x04);
	 Mode=Mode<<1;
   }

}

void HT1621CommandSent(INT8U dat)
{
    INT8U i;
   for(i=0;i<8;i++)
   {
     SENDBIT(dat&0x80);
     dat=dat<<1;
   }
   	GETIF(WritePin)(HT1621_WR_PIN,0);	//-----空发1位X-----
	GETIF(WritePin)(HT1621_WR_PIN,1);
}
void HT1621Init()
{
   GETIF(WritePin)(HT1621_CS_PIN,1);
   GETIF(WritePin)(HT1621_WR_PIN,1);
    #ifdef HT1621_RD_PIN
   GETIF(WritePin)(HT1621_RD_PIN,1);
    #endif
    GETIF(WritePin)(HT1621_DATA_PIN,1);
   GETIF(WritePin)(HT1621_CS_PIN,0);
   HT1621ModeSet(HT1621_COMMAND);
   HT1621CommandSent(HT1621_ON);
   HT1621CommandSent(HT1621_INIT);
   HT1621CommandSent(HT1621_OSC);
    GETIF(WritePin)(HT1621_CS_PIN,1);	//----CS置高，片选禁止
}

void HT1621Refresh()
{
    INT8U i,j,Temp;
   GETIF(WritePin)(HT1621_CS_PIN,0);
    HT1621ModeSet(HT1621_WRITEDISBUF);
   //-----发送显存首地址000000----
   for(i=0;i<=5;i++)
   {
       SENDBIT(0);
   }
   for(i=0;i<16;i++)
   {
	   Temp=HT1621Buffer[i];
	   for(j=0;j<8;j++)
	   {
	       SENDBIT(Temp&0x01);
	  	   Temp=Temp>>1;
	   }
   }
    GETIF(WritePin)(HT1621_CS_PIN,1);	//----CS置高，片选禁止


}
void HT1621SegmentListAppend(const INT8U *List,INT8U Lendth)
{
    while(Lendth-->0)
    {
        if(*List>0x7f)//1
        {
            HT1621Buffer[(*List&0x7f)>>3]|=1<<(*List%8);
        }else{
            HT1621Buffer[*List>>3]&=~(1<<(*List%8));

        }
        List++;
    }
}
#endif
