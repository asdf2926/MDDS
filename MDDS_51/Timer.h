#define Timer0 0
#define Timer1 1
#define Timer2 2


void TimerInit();
void TimerStart(INT8U num,INT16U TimeUs,void (*CallBack)());
void TimerStop(INT8U num);