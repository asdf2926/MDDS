/*
 * timer.h
 *
 *  Created on: 2019年1月24日
 *      Author: asdf2
 */

#ifndef TIMER_H_
#define TIMER_H_

//定时器A时钟源
enum e_TimerBaseClockSource{
    T_TACLK,//TACLK
    T_ACLK,//ACLK
    T_SMCLK,//SMCLK
    T_INCLK//2553中为TACLK，其他不知道，可能是取反的TBCLK
};

enum e_TimerBaseMode{
    StopMode=0,//定时器暂停
    UpMode=1,//增计数  定时器增计数至等于比较寄存器 0 的值
    ContinuousMode=2,//连续  定时器连续增计数
    UpDownMode=3//增/减计数 定时器增计数到等于比较寄存器 0 的值又减计数到 0
};

enum e_TimerAModuleCaptureMode{  //捕获模式
    No,//捕获模式禁止
    RisingEdge,//上升沿捕获
    FallingEdge,//下降沿捕获
    BothEdges//在上升沿与下降沿都捕获
};
enum e_TimerAModuleInputSelect { //输入选择

    CCIxA,//
    CCIxB,//
    GND,//
    VCC//
};

enum e_TimerAModuleSynchronizeCaptureSource{//
    Asynchronous,//异步捕获
    Synchronous//同步捕获
};



enum e_TimerAModuleInputMode{//捕获/比较模块工作模式
    Compare,//比较模式
    Capture//捕获模式
};
enum e_TimerAModuleOutputMode{//   输出模式
    OutBitValue,//0：仅输出    OUTx 位的数字即 Outx
    Set,//1：置位   比较信号 EQUx 使 Outx 置位
    ToggleReset,//2：PWM 翻转/复位  比较信号 EQUx 使 Outx 翻转，EQU0 使 Outx 复位
    SetReset,//3：PWM 置位/复位  比较信号 EQUx 使 Outx 置位，EQU0 使 Outx 复位
    Toggle,//4：翻转  比较信号 EQUx 使 Outx 翻转
    Reset,//5：复位  比较信号 EQUx 使 Outx 复位
    ToggleSet,//6：PWM 翻转/置位  比较信号 EQUx 使 Outx 翻转，EQU0 使 Outx 置位
    ResetSet//7：PWM 复位/置位  比较信号 EQUx 使 Outx 复位，EQU0 使 Outx 置位
};
#if TIMER_0A_EN>0
/*时基初始化
参数：
    enum e_TimerBaseClockSource SourceClkSel：时钟源设置
    enum e_CLKDiv ClkDiv：时钟输入分配
    BL InterruptEnable：中断启动（如果使用位数拓展，则必须启用）
    enum e_TimerBaseMode TimerBaseMode：时基工作模式
返回：无
    */
void Timer0AInit(enum e_TimerBaseClockSource SourceClkSel,
                enum e_CLKDiv ClkDiv,
                BL InterruptEnable,
                enum e_TimerBaseMode TimerBaseMode);
/*额外模块初始化
参数：
    INT8U Channel,：通道
    enum e_TimerAModuleInputMode InputModeSet,：捕获/比较模块工作模式
    enum e_TimerAModuleCaptureMode    CaptureModeSet,：捕获模式
    enum e_TimerAModuleInputSelect  InputSelectSet,：输入选择
    enum e_TimerAModuleSynchronizeCaptureSource SynchronizeCaptureSourceSet,：异步/同步捕获
    enum e_TimerAModuleOutputMode   OutputModeSet,：输出模式设置
    BL  InterruptEnable：中断允许
返回：无
 */
void Timer0AModuleInit(INT8U Channel,
                      enum e_TimerAModuleInputMode InputModeSet,
                      enum e_TimerAModuleCaptureMode    CaptureModeSet,
                      enum e_TimerAModuleInputSelect  InputSelectSet,
                      enum e_TimerAModuleSynchronizeCaptureSource SynchronizeCaptureSourceSet,
                      enum e_TimerAModuleOutputMode   OutputModeSet,
                      BL  InterruptEnable);
/*时基频率设置
参数：
    INT32U Freq：频率
    INT32U ClkFreq：时钟频率（如果使用内部时钟，可以填0自动计算）
返回：无
 */
void Timer0ABaseFreqSet(INT32U Freq,INT32U ClkFreq);
/*时基频率设置
参数：
    INT16U count：计数次数
返回：无
 */
inline void Timer0ABaseMaxCountSet(INT16U count);
/*定时器启动
参数：无
返回：无
 */
void Timer0AStart();
/*定时器停止
参数：无
返回：无
 */
void Timer0AStop();
/*PWM模式设置占空比
参数：
    INT8U Channel,：通道
    INT16U Value：值（0xffff对于100%）
返回：无
 */
void Timer0AModulePWMSet(INT8U Channel,INT16U Value);
/*捕获模式初始化
参数：
    INT8U Channel,：通道
    BL ExternModeEN：拓展模式，可以捕获32位值
    void (*pCallBackFunc)(INT32U time)：指向回调函数的指针
返回：无
注意：TimerAModuleInit仍然要调用
 */
void Timer0AModuleCaptureInit(INT8U Channel,BL ExternModeEN,void (*pCallBackFunc)(INT32U time));
/*比较模式初始化
参数：
    INT8U Channel,：通道
    INT32U Cycles：时间
    void (*pCallBackFunc)(INT32U time)：指向回调函数的指针
返回：无
注意：TimerAModuleInit仍然要调用
 */
void Timer0AModuleCompareInit(INT8U Channel,INT16U Cycles,void (*pCallBackFunc)(),BL isSingleShot);
//获取时基溢出频率
//返回：INT32U：频率（Hz）

inline INT32U Timer0ABaseFreqGet(){return TIMER_0A_BASE_FREQ;}
#endif
#if TIMER_1A_EN>0
/*时基初始化
参数：
    enum e_TimerBaseClockSource SourceClkSel：时钟源设置
    enum e_CLKDiv ClkDiv：时钟输入分配
    BL InterruptEnable：中断启动（如果使用位数拓展，则必须启用）
    enum e_TimerBaseMode TimerBaseMode：时基工作模式
返回：无
    */
void Timer1AInit(enum e_TimerBaseClockSource SourceClkSel,
                enum e_CLKDiv ClkDiv,
                BL InterruptEnable,
                enum e_TimerBaseMode TimerBaseMode);
/*额外模块初始化
参数：
    INT8U Channel,：通道
    enum e_TimerAModuleInputMode InputModeSet,：捕获/比较模块工作模式
    enum e_TimerAModuleCaptureMode    CaptureModeSet,：捕获模式
    enum e_TimerAModuleInputSelect  InputSelectSet,：输入选择
    enum e_TimerAModuleSynchronizeCaptureSource SynchronizeCaptureSourceSet,：异步/同步捕获
    enum e_TimerAModuleOutputMode   OutputModeSet,：输出模式设置
    BL  InterruptEnable：中断允许
返回：无
 */
void Timer1AModuleInit(INT8U Channel,
                      enum e_TimerAModuleInputMode InputModeSet,
                      enum e_TimerAModuleCaptureMode    CaptureModeSet,
                      enum e_TimerAModuleInputSelect  InputSelectSet,
                      enum e_TimerAModuleSynchronizeCaptureSource SynchronizeCaptureSourceSet,
                      enum e_TimerAModuleOutputMode   OutputModeSet,
                      BL  InterruptEnable);
/*时基频率设置
参数：
    INT32U Freq：频率
    INT32U ClkFreq：时钟频率（如果使用内部时钟，可以填0自动计算）
返回：无
 */
void Timer1ABaseFreqSet(INT32U Freq,INT32U ClkFreq);
/*时基频率设置
参数：
    INT16U count：计数次数
返回：无
 */
inline void Timer1ABaseMaxCountSet(INT16U count);
/*定时器启动
参数：无
返回：无
 */
void Timer1AStart();
/*定时器停止
参数：无
返回：无
 */
void Timer1AStop();
/*PWM模式设置占空比
参数：
    INT8U Channel,：通道
    INT16U Value：值（0xffff对于100%）
返回：无
 */
void Timer1AModulePWMSet(INT8U Channel,INT16U Value);
/*捕获模式初始化
参数：
    INT8U Channel,：通道
    BL ExternModeEN：拓展模式，可以捕获32位值
    void (*pCallBackFunc)(INT32U time)：指向回调函数的指针
返回：无
注意：TimerAModuleInit仍然要调用
 */
void Timer1AModuleCaptureInit(INT8U Channel,BL ExternModeEN,void (*pCallBackFunc)());
/*比较模式初始化
参数：
    INT8U Channel,：通道
    INT32U Cycles：时间
    void (*pCallBackFunc)(INT32U time)：指向回调函数的指针
返回：无
注意：TimerAModuleInit仍然要调用
 */
void Timer1AModuleCompareInit(INT8U Channel,INT16U Cycles,void (*pCallBackFunc)(INT32U time),BL isSingleShot);
//获取时基溢出频率
//返回：INT32U：频率（Hz）

inline INT32U Timer1ABaseFreqGet(){return TIMER_1A_BASE_FREQ;}
#define Timer1ABaseSourceFreq (TIMER_1A_BASE_FREQ*TIMER_1A_BASE_MAX_COUNT)
#define Timer1ABaseSourceFreqKHz (TIMER_1A_BASE_CLK_FREQ_KHZ)
#endif
/*时基中断处理函数
参数：无
返回：无
注意：由用户定义
 */

#if TIMER_0A_BASE_INTR_CALLBACK>0
void Timer0ABaseInterruptHook();
#endif
#if TIMER_1A_BASE_INTR_CALLBACK>0
void Timer1ABaseInterruptHook();
#endif

#endif /* TIMER_H_ */

