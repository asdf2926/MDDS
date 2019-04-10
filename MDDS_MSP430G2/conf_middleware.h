/*
 * conf_middleware.h
 *
 *  Created on: 2019年3月3日
 *      Author: asdf2
 */

#ifndef MIDDLEWARE_CONF_MIDDLEWARE_H_
#define MIDDLEWARE_CONF_MIDDLEWARE_H_

//-----------------AbstractButton----------------
#define ABUTTON_EN 1//使能
#if ABUTTON_EN>0
#define ABUTTON_COUNT 4//按键数量，必须<=255
#define ABUTTON_GET_FUNC_BUFFER_LEN 10//按键缓冲区大小，必须<256
#define ABUFFON_REFRESH_HOOK_EN 1//使能勾函数进行按键前处理
#define ABUTTON_RAWINPUT_WORDLENGTH 8//按键输入数组的类型：无符号整型长度。取值有8、16、32、64

#endif
//-----------------GUI--------------------------
#define GUI_EN 0
#if GUI_EN>0
#define GUI_WIDTH 128//<256
#define GUI_HEIGHT 64//<256
#define GUI_BUF_TYPE GUI_BLACK_V
#define GUI_BUF_NAME LCDBuffer
#define GUI_REFRESH_HOOK() LCDRefresh()
#endif

#endif /* MIDDLEWARE_CONF_MIDDLEWARE_H_ */
