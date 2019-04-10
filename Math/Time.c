/*


 * Time.c


 *


 *  Created on: 2019年2月2日


 *      Author: asdf2


 *      https://blog.csdn.net/mill_li/article/details/54599927


 */


#include "includes.h"
#if TIME_EN>0


#define UTC_BASE_YEAR 2000
#define MONTH_PER_YEAR 12
//#define DAY_PER_YEAR 365
#define SEC_PER_DAY 86400
#define SEC_PER_HOUR 3600
#define SEC_PER_MIN 60
#define DAY_ON_2000_01_01 6
//2000/01/01 0:0:0.0时刻的时间戳
#define UNIX_Timestamp_ON_2000_01_01 946684800
const unsigned char g_day_per_mon[MONTH_PER_YEAR+1] = {0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
//获取一年的天数
#define GET_DATE_OF_YEAR(a) (365+(a%4==0)-(a%100==0)+(a%400==0))
//闰月调整
#define LEAP_ADJUST(a,m) ((m==2)?((a%4==0)-(a%100==0)+(a%400==0)):0)


//转换时间戳为时间
//参数：
//  UTime Timestamp：时间戳
//返回：Time：时间
//注意：时间戳过大时运行时间可能非常长


Time ConventTimestampToTime(UTime Timestamp)
{
    Time t;
    UTime r,s;
    INT32S s32;
    t.MSec=Timestamp%1000;
    r=Timestamp/1000;
    if((s32=r%SEC_PER_DAY)<0)
    {
        r-=SEC_PER_DAY;
        s32+=SEC_PER_DAY;
    }
    r=r/SEC_PER_DAY;
    t.Sec=s32%60;
    s32/=60;
    //if((t.Sec&0x80)>0)t.Sec+=60;
    t.Min=s32%60;
    s32/=60;
    //if((t.Min&0x80)>0)t.Min+=60;
    t.Hour=s32;
    //r/=24;
    //if((t.Hour&0x80)>0)t.Hour+=24;
    if(r>=0)
    {
        t.Year=UTC_BASE_YEAR-1;
        for(s=-1;s<r;s+=GET_DATE_OF_YEAR(t.Year))t.Year++;
    }else{
        s=0;
        t.Year=UTC_BASE_YEAR;
        do{
           t.Year--;
           s-=GET_DATE_OF_YEAR(t.Year);
        }while(s>r);
        s=s+GET_DATE_OF_YEAR(t.Year)-1;
        /*for(s=-1;s>=r+GET_DATE_OF_YEAR(t.Year);t.Year--)
        {
            s-=GET_DATE_OF_YEAR(t.Year);
        }*/
    }
    //s落在此年的最后一天
    t.Month=12;
    while(s>=r)
    {
        s-=g_day_per_mon[t.Month];
        s-=LEAP_ADJUST(t.Year,t.Month);
        t.Month--;
    }
    //s落在前一月的最后一天
    t.Month++;
    t.Date=r-s;
    t.Day=(r+DAY_ON_2000_01_01)%7;
    if((t.Day&0x80)>0)t.Day+=7;
    return t;
}
UTime ConventTimeToTimestamp(Time t)
{
    UTime s;
    INT16U a;
    s=0;
    if(t.Year>=2000)for(a=2000;a<t.Year;a++)s+=GET_DATE_OF_YEAR(a);
    else for(a=1999;a>=t.Year;a--)s-=GET_DATE_OF_YEAR(a);
    for(a=1;a<t.Month;a++)s+=g_day_per_mon[a]+LEAP_ADJUST(t.Year,a);
    s+=t.Date-1;
    s*=SEC_PER_DAY;
    s+=t.Hour*SEC_PER_HOUR+t.Min*SEC_PER_MIN+t.Sec;
    s*=1000;
    s+=t.MSec;
    return s;
}









 //UTime ConventTimeToTimestamp(Time t);


//转换时间戳为UNIX时间戳


//  UTime Timestamp：时间戳


//返回：INT32S：UNIX时间戳


//注意：注意数据溢出





inline INT32S ConventTimestampToUnixTimestamp(UTime Timestamp)


{


    return Timestamp/1000-UNIX_Timestamp_ON_2000_01_01;


}


INT8U *ConventTimeToArray(Time t,INT8U *out)
{
	*(out++)=t.Year/100;
	*(out++)=t.Year%100;
	*(out++)=t.Month;
	*(out++)=t.Date;
	*(out++)=t.Day;
	*(out++)=t.Hour;
	*(out++)=t.Min;
	*(out++)=t.Sec;
	*(out++)=t.MSec/100;
	*(out++)=t.MSec%100;
	return out-10;
	
}
Time ConventArrayToTime(INT8U *in)
{
	Time t;
	t.Year=*in*100+*(in+1);
	in+=2;
	t.Month=*(in++);
	t.Date=*(in++);
	t.Day=*(in++);
	t.Hour=*(in++);
	t.Min=*(in++);
	t.Sec=*(in++);
	t.MSec=*in*100+*(in+1);
	return t;
}
#endif
