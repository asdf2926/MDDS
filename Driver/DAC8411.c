/*
 * DAC8411.c
 *
 *  Created on: 2019年3月2日
 *      Author: asdf2
 */
#include "includes.h"
#if DAC8411_EN>0
const INT16U *DACData;size_t DACDataLen,curPos;
void DAC8411Init()
{
    P1DIR |=BIT0+BIT3;
    P2DIR |=BIT2;
    SCLK_HIGH;
    SYNC_HIGH;
}
void DAC8411Write(INT16U Data)
{
    unsigned int Temp;
    unsigned char i;
    Temp=Data;
    SYNC_LOW;
    //-----发送00-----
    SCLK_HIGH;
    DIN_LOW;
    SCLK_LOW;

    SCLK_HIGH;
    DIN_LOW;
    SCLK_LOW;
    //-----发送16位数据-----
    for(i=0;i<16;i++)
    {
        SCLK_HIGH;
        if(Temp&BITF)   DIN_HIGH;
        else        DIN_LOW;
        SCLK_LOW;
        Temp=Temp<<1;
    }
    SYNC_HIGH;
}
void DAC8411AutoWriteInit(const INT16U *dat,size_t len)
{
    DACData=dat;DACDataLen=len;curPos=0;
}
void DAC8411AutoWrite()
{
    DAC8411Write(DACData[curPos++]);
    if(curPos>=DACDataLen)curPos=0;
}
#endif
