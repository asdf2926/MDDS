#include <includes.h>

/**
 * main.c
 */
/*
#define LED2_ON() P1OUT|=0x40
#define LED2_OFF() P1OUT&=0xBF
#define LED2_TRIG() P1OUT^=0x40
#define LED1_ON() P1OUT|=0x01
#define LED1_OFF() P1OUT&=0xFE
#define LED1_TRIG() P1OUT^=0x01
*/
#if 1
void Show()
{
    static const INT8S ADCCmdTab[]={10,-1};//启动10号通道
    static INT32U r=0;//计时器
    INT32U s;//临时
    static INT16S adcdata;//adc转换结果
    r++;//计时/秒
    s=r/3600;//取小时
    LCDDigitDisplay(0,s/10);
    LCDDigitDisplay(1,s%10);
    //LCDWriteCharRaw(0, 0, FONT_ASCII0816, s/10+'0');
    //LCDWriteCharRaw(0, 8, FONT_ASCII0816, s%10+'0');
    s=r%3600/60;//取分钟
    LCDDigitDisplay(2,s/10);
    LCDDigitDisplay(3,s%10);
    //LCDWriteCharRaw(0, 16, FONT_ASCII0816, ':');
    //LCDWriteCharRaw(0, 24, FONT_ASCII0816, s/10+'0');
    //LCDWriteCharRaw(0, 32, FONT_ASCII0816, s%10+'0');
    s=r%60;//取秒
    LCDDigitDisplay(4,s/10);
    LCDDigitDisplay(5,s%10);
    //LCDWriteCharRaw(0, 40, FONT_ASCII0816, ':');
    //LCDWriteCharRaw(0, 48, FONT_ASCII0816, s/10+'0');
    //LCDWriteCharRaw(0, 56, FONT_ASCII0816, s%10+'0');
    if(ADCStart(ADCCmdTab,(INT16U *)&adcdata))//转换（第二次有效）
    {
        adcdata-=673;//按公式算，单位0.1℃
        adcdata*=4;//(i-673.10933333333333333333333333332)*0.41263204225352112676056338028169
        //VTEMP=0.00355(TEMPC)+0.986
        //VTEMP=1.5/1024*INPUT
        //LCDWriteCharRaw(2, 40, FONT_ASCII0816, adcdata/1000+'0');
        //adcdata%=1000;
        //LCDWriteCharRaw(2, 48, FONT_ASCII0816, adcdata/100+'0');
        //adcdata%=100;
        //LCDWriteCharRaw(2, 56, FONT_ASCII0816, adcdata/10+'0');
        //adcdata%=10;
        //LCDWriteCharRaw(2, 64, FONT_ASCII0816, '.');
        //LCDWriteCharRaw(2, 72, FONT_ASCII0816, adcdata+'0');
        LCDDigitDisplay(9,adcdata%10);
        adcdata/=10;
        LCDDigitDisplay(8,adcdata%10);
        adcdata/=10;
        LCDDigitDisplay(7,adcdata%10);
        adcdata/=10;
        LCDDigitDisplay(6,adcdata%10);
        ADCStart(ADCCmdTab,(INT16U *)&adcdata);//启动下一次转换
    }
    HT1621Refresh();
}
#endif
/*
const INT8U SegList[]={SEG_SET|_LCD_COLON1,SEG_SET|_LCD_COLON0,SEG_SET|_LCD_DOT5};
const INT16U WAVE[]={
                     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                     0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
                     0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,


};
*/

const INT8U AButtonConventTab[]=
{
    VK_F1,VK_F2,VK_F3,VK_F4
};

void AButtonRefreshHook()
{
    AButtonRawInput[0]=EXIORead(GPIOB);

}

int main(void)
{
    //INT8U count=0;
	SystemInit();//系统初始化

	BasicTimerAdd(1000000, 0, Show);//显示函数/1S
	BasicTimerAdd(10000,0,AButtonProcess_10ms);
	//BasicTimerAdd(23, 0, DAC8411AutoWrite);
	Timer1AStart();//启动计时器
	//HT1621SegmentListAppend(SegList, sizeof(SegList));
//    LCDDigitDisplay(0,8);
    LCDDigitDisplay(1,8);
    LCDDigitDisplay(2,3);
    LCDDigitDisplay(3,0);
    LCDDigitDisplay(4,1);
    LCDDigitDisplay(5,0);
    LCDDigitDisplay(6,2);
    LCDDigitDisplay(7,0);
    LCDDigitDisplay(8,1);
    LCDDigitDisplay(9,8);

	HT1621Refresh();
	//DAC8411AutoWriteInit(WAVE,44);
    while(1)
	{
//	    __delay_cycles(50000);
//	    TimerAModulePWMSet(1,count);//渐亮
//	    count+=0x800;
//	    EXIOWrite(GPIOA, count++);
	    IdleProcess();
//	    EXIOWrite(GPIOA, 0x5a);
//	    EXIOWrite(GPIOA, 0xa5);
	    PowerPolicySet(Idle);
	}
//	return 0;
}

void GPIOISR(enum e_GPIOGroup Group,INT8U Pin)
{
//    if(Group==GPIOA&Pin==3)
//       LED1_TRIG();
}
