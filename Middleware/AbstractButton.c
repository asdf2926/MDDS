/*
 * AbstractBottom.c
 *
 *  Created on: 2019Äê3ÔÂ3ÈÕ
 *      Author: asdf2
 */
#include "includes.h"
#if ABUTTON_EN>0

INT8U KeyTime[ABUTTON_COUNT];
KeyRawInputType AButtonRawInput[(ABUTTON_COUNT-1)/ABUTTON_RAWINPUT_WORDLENGTH+1];

MAKE_BUFFER(Key,AButton,ABUTTON_GET_FUNC_BUFFER_LEN,INT8U,,)
void (*CallBackFunc)(INT8U,enum e_KeyStatus);
void AButtonInit()
{
	INT8U i;
	for(i=0;i<ABUTTON_COUNT;i++)
	{
		KeyTime[i]=0;
	}
	BasicTimerAdd(10000,0,AButtonProcess_10ms);
}


#if BT_EXT_CALLBACK>0
void AButtonProcess_10ms(INT8U ul)
#else
void AButtonProcess_10ms()
#endif
{
	INT8U i;
	AButton r;
#if BT_EXT_CALLBACK>0
	ul=ul;
#endif
	#if ABUFFON_REFRESH_HOOK_EN>0
	AButtonRefreshHook();
	#endif
	for(i=0;i<ABUTTON_COUNT;i++)
	{
		if((AButtonRawInput[i/ABUTTON_RAWINPUT_WORDLENGTH]>>(i%ABUTTON_RAWINPUT_WORDLENGTH))&0x01)
		{
			if(KeyTime[i]<=254)KeyTime[i]++;
			else KeyTime[i]=246;
			if(KeyTime[i]==1)r.Status=KeyShort;
			else if(KeyTime[i]==100)r.Status=KeyLongStart;
			else if((KeyTime[i]>100)&&((KeyTime[i]&0x1)==0))r.Status=KeyLong200ms;
			else continue;
		}else
		{
			if(KeyTime[i]==0)continue;
			if(KeyTime[i]<100)r.Status=KeyShortRelease;
			else r.Status=KeyLongRelease;
			KeyTime[i]=0;
		}
		r.KeyCode=AButtonConventTab[i];
		BufKeyW(&r,1);
	}
	if(CallBackFunc)
	{
		while(BufKeyLen)
		{
			r=BufKeyRB();
			(*CallBackFunc)(r.KeyCode,r.Status);
		}
	}
}

AButton AButtonGet()
{
	const static AButton r={0,KeyNone};
	if(BufKeyLen)
	{
		return BufKeyRB();
	}
	return r;
}
INT8U AButtonTimeGet(INT8U Key)
{
	
	return KeyTime[Key];
}

void AButtonCallBackSet(void (*pCallBack)(INT8U,enum e_KeyStatus))
{
	CallBackFunc=pCallBack;
}
#endif
