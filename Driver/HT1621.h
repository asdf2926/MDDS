/*
 * HT1621.h
 *
 *  Created on: 2019年3月2日
 *      Author: asdf2
 */

#ifndef DRIVER_HT1621_H_
#define DRIVER_HT1621_H_
#if HT1621_EN>0
//LCD初始化
//参数：无
//返回：无
void HT1621Init(void);
//屏幕刷新
//参数：无
//返回：无
void HT1621Refresh(void);
//改变点亮的段
//参数：const INT8U *List：指向数据的指针，数据最高位指示是否点亮，可用宏SEG_SET、SEG_RESET
//      INT8U Lendth：//长度
//返回：无
//
void HT1621SegmentListAppend(const INT8U *List,INT8U Lendth);
extern INT8U HT1621Buffer[];
//-----Ht1621命令宏定义-----
#define HT1621_COMMAND 		    4			//100
#define HT1621_WRITEDISBUF		5			//101
#define HT1621_INIT				0x29 	    //开启LCD驱动+1/3bias+4coms
#define HT1621_ON				0x03 	    //开启LCD驱动+1/3bias+4coms
#define HT1621_OSC				0x01		//开启内部振荡器

#define SEG_SET 0x80
#define SEG_RESET 0
#endif

#endif /* DRIVER_HT1621_H_ */
