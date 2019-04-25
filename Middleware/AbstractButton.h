/*
 * AbstractBottom.h
 *
 *  Created on: 2019年3月3日
 *      Author: asdf2
 */

#ifndef MIDDLEWARE_ABSTRACTBUTTON_H_
#define MIDDLEWARE_ABSTRACTBUTTON_H_
#if ABUTTON_EN>0
enum e_KeyStatus{
    KeyNone=0,//没有按键（仅用于读模式）
    KeyShort,//短按
    KeyHold,//按键按住（仅用于读模式）
    KeyLongStart,//进入长按状态
    KeyLong200ms,//长按每200ms
    KeyLongRelease=0x80,//按键释放

	KeyShortRelease=0x81
};
typedef struct{
    INT8U KeyCode;
    enum e_KeyStatus Status;
} AButton;

#define KeyRawInputType _COMB_AB(INT,_COMB_AB(ABUTTON_RAWINPUT_WORDLENGTH,U))

extern INT8U AButtonInput[(ABUTTON_COUNT+7)/8];
extern KeyRawInputType AButtonRawInput[(ABUTTON_COUNT-1)/ABUTTON_RAWINPUT_WORDLENGTH+1];
//初始化
//参数：无
//返回：无
void AButtonInit(void);
AButton AButtonGet(void);
INT8U AButtonTimeGet(INT8U Key);
void AButtonCallBackSet(void (*pCallBack)(INT8U,enum e_KeyStatus));
#if BT_EXT_CALLBACK>0
void AButtonProcess_10ms(INT8U ul);
#else
void AButtonProcess_10ms(void);
#endif
#if ABUFFON_REFRESH_HOOK_EN>0
void AButtonRefreshHook(void);
#endif
#endif
#endif /* MIDDLEWARE_ABSTRACTBUTTON_H_ */
