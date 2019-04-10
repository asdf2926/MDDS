/*
 * rcc.h
 *
 *  Created on: 2019年1月14日
 *      Author: Lucas S
 */

#ifndef RCC_H_
#define RCC_H_

enum e_ClockSource{//时钟源选择 注意：部分选项不可用，并需要同时调整e_LFXT1Freq，具体参照时钟树。
    LFXT1CLK,//外部晶体振荡器,32768~16M
    XT2CLK,//G2系列不可用
    DTOCLK,//内部高速振荡器
    VLOCLK//内部12KHz振荡器
};

enum e_DCOFreq{//DCO频率选择
    F16000K=-4,//16M已校准
    F12000K=-3,//12M已校准
    F8000K=-2,//8M已校准
    F1000K=-1,//1M已校准
    F100K=0,//100k未校准，以下类推
    F150K=1,
    F210K=2,
    F300K=3,
    F410K=4,
    F580K=5,
    F750K=6,
    F1200K=7,
    F1600K=8,
    F2300K=9,
    F3400K=10,
    F4250K=11,
    F6000K=12,
    F7800K=13,
    F11250K=14,
    F15250K=15
};

enum e_LFXT1Freq{//外部晶体振荡器工作频率选择
    F32768,//32768Hz晶体振荡器
    _reserve,//保留，未使用
    FVLOCLK,//内部振荡器12K
    EXTCLK,//外部时钟输入
    F400K_1M,//晶体振荡器，400K~1M
    F1M_3M,//晶体振荡器，1M~3M
    F3M_16M,//晶体振荡器，3M~16M
    F400K_16M//晶体振荡器，400K~16M

};

enum e_LFXT1Cap{//外部振荡器可配置电容选择
    C1P,//1pF
    C6P,//6pF
    C10P,//10pF
    C12P//12pF（评估板使用）
};

enum e_CLKDiv{//时钟分频
    DIV1=0,//不分频
    DIV2=1,//2分频
    DIV4=2,//4分频
    DIV8=3//8分频
};

enum e_PowerPolicy{//电源策略
    Off,//关闭，所有部件停止，可用外部中断唤醒
    Stop,//停止，RTC模块运行，内存数据保持，端口保持，其余停止，可用外部中断唤醒
    Idle,//空闲，CPU停止
    LowPower,//低功耗（未实现）
    Normal,//正常（未实现）
    HighPerformance//高性能（未实现）
};

enum e_ClockType//时钟类型，获取时钟频率时用
{
    MCLK=0,//
    ACLK=1,//
    SMCLK=2//
};
/*
初始化时钟
参数：
enum e_DCOFreq DCOSel,//DCO频率选择
enum e_LFXT1Freq LFXT1FreqSel,// 外部晶体振荡器工作频率选择
enum e_LFXT1Cap LFXT1CapSel,// 外部振荡器可配置电容选择
enum e_ClockSource MCLKSel,//主时钟时钟源选择
enum e_CLKDiv MCLKDivSel,// 主时钟分频
enum e_ClockSource ACLKSel,//辅助时钟时钟源选择
enum e_CLKDiv ACLKDivSel,// 辅助时钟分频
enum e_ClockSource SMCLKSel,//第二时钟时钟源选择
enum e_CLKDiv SMCLKDivSel//第二时钟分频
返回：无
注意：如果外部晶振初始化失败，所有使用外部时钟的时钟将以VLOCLK为时钟。
*/
void SysClockInit(enum e_DCOFreq DCOSel,enum e_LFXT1Freq LFXT1FreqSel,enum e_LFXT1Cap LFXT1CapSel,
                  enum e_ClockSource MCLKSel,enum e_CLKDiv MCLKDivSel,
                  enum e_ClockSource ACLKSel,enum e_CLKDiv ACLKDivSel,
                  enum e_ClockSource SMCLKSel,enum e_CLKDiv SMCLKDivSel);
/*设置电源策略
参数:
e_PowerPolicy：电源策略
返回：无

 */
void PowerPolicySet(enum e_PowerPolicy PowerPolicy);
/*获取时钟频率
参数：
enum e_ClockType Clk：时钟类型
返回：
INT32U：时钟频率（HZ）
 */
INT32U getClockFreq(enum e_ClockType Clk);

#endif /* RCC_H_ */
