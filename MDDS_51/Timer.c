void (*pCallBack[3])();

void TimerInit()
{


}


void TimerStart(INT8U num,INT16U TimeUs,void (*CallBack)())
{
    if(num==Timer0)
    {
        TMOD&=0xf0;
        TMOD|=0x01;
        TH1=（65536-TimeUS*(XTAL_FREQ/10000)/1200）/256;
        TH0=（65536-TimeUS*(XTAL_FREQ/10000)/1200）%256;
        TCON|=0x12;
    }else if(num==Timer1)
    {
        TMOD&=0x0f;
        TMOD|=0x10;
        TH1=（65536-TimeUS*(XTAL_FREQ/10000)/1200）/256;
        TH0=（65536-TimeUS*(XTAL_FREQ/10000)/1200）%256;
        TCON|=0x48;
    }

    pCallBack[num]=CallBack;
}


void TimerStop(INT8U num)
{
    if(num==Timer0)
    {
        TR0=0;
    }else if(num==Timer1)
    {
        TR1=0;
    }

void Timer0Interrupt() interrupt 1
{
    if(pCallBack[0])(*pCallBack[0])();
}

void Timer1Interrupt() interrupt 3

