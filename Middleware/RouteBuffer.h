/*
 * RouteBuffer.h
 *
 *  Created on: 2019年1月30日
 *      Author: asdf2
 */

#ifndef MIDDLEWARE_ROUTEBUFFER_H_
#define MIDDLEWARE_ROUTEBUFFER_H_
//建立环形缓冲区及其配套函数
//调用方法：MAKE_BUFFER(缓冲区名，缓冲区数据类型，缓冲区指针类型，读阻塞操作，写阻塞操作)
//作用：建立名为缓冲区名的数组，以及名为pBuf缓冲区名W,pBuf缓冲区名R,Buf缓冲区名Len共3个指针
//  以及配套函数:Buf缓冲区名W,Buf缓冲区名R,Buf缓冲区名RB,Buf缓冲区名WB共4个
//Buf缓冲区名W：向缓冲区写入
//          参数：
//              const 缓冲区数据类型* Buf：写入数据
//              缓冲区指针类型 Len：长度
//          返回：无
//          注意：若写入数据超出缓冲区，数据后部会被自动截断
//Buf缓冲区名R：读取缓冲区
//          参数：
//              const 缓冲区数据类型* Buf：数据指针
//              缓冲区指针类型 Len：长度
//          返回：INT8U：错误代码（0：正常，1：数据量不足，无法读）
//Buf缓冲区名RB：读取缓冲区（阻塞式）
//          参数：无
//          返回：缓冲区数据类型：数据
//          注意：若阻塞，则不断调用读阻塞操作，读阻塞操作为去掉最后分号的语句
//Buf缓冲区名RB：写缓冲区（阻塞式）
//          参数：缓冲区数据类型：数据
//          返回：无
//          注意：若阻塞，则不断调用写阻塞操作，读阻塞操作为去掉最后分号的语句
#define MAKE_BUFFER(BufferName,BufferType,BufferSize,PointerType,BlockFuncR,BlockFuncW)         \
     BufferType BufferName[BufferSize];                                             \
     PointerType pBuf##BufferName##W,pBuf##BufferName##R;                           \
     PointerType volatile Buf##BufferName##Len;                                     \
     void Buf##BufferName##W(const BufferType* Buf, PointerType Len)                           \
     {                                                                              \
         if(Buf##BufferName##Len+Len>BufferSize)Len=BufferSize-Buf##BufferName##Len; \
         Buf##BufferName##Len+=Len;                                                 \
         while(Len-->0)                                                             \
        {                                                                           \
            BufferName[pBuf##BufferName##W++]=*Buf;                                 \
            Buf++;                                                      \
                                                                        \
            if(pBuf##BufferName##W>=BufferSize)pBuf##BufferName##W=0;   \
        }                                                               \
    }                                                                   \
    INT8U Buf##BufferName##R(BufferType* Buf, PointerType Len)               \
    {                                                                   \
        if(Len>Buf##BufferName##Len)return 1;                           \
        Buf##BufferName##Len-=Len;                                      \
        while(Len>0)                                                  \
        {                                                               \
            *Buf=BufferName[pBuf##BufferName##R++];                     \
            Buf++;                                                      \
            Len--;                                                      \
            if(pBuf##BufferName##R>=BufferSize)pBuf##BufferName##R=0;   \
        }                                                               \
        return 0;                                                       \
    }                                                                   \
    BufferType Buf##BufferName##RB(void)                                     \
    {                                                                   \
        BufferType dat;                                                      \
        while(Buf##BufferName##Len==0)BlockFuncR;                        \
        dat=BufferName[pBuf##BufferName##R++];                          \
        if(pBuf##BufferName##R>=BufferSize)pBuf##BufferName##R=0;       \
        Buf##BufferName##Len--;                                         \
        return dat;                                                     \
    }                                                                   \
    void Buf##BufferName##WB(BufferType dat)                             \
    {                                                                   \
        while(Buf##BufferName##Len>=BufferSize)BlockFuncW;                          \
        BufferName[pBuf##BufferName##W++]=dat;                          \
        if(pBuf##BufferName##W>=BufferSize)pBuf##BufferName##W=0;       \
        Buf##BufferName##Len++;                                         \
                                                                        \
    }                                                                   \
    INT8U Buf##BufferName##Push(BufferType dat)                          \
    {                                                                   \
        if(Buf##BufferName##Len+1>BufferSize)return 0;                 \
        Buf##BufferName##Len+=1;                                                 \
        if(pBuf##BufferName##R!=0)pBuf##BufferName##R--;\
        else pBuf##BufferName##R=BufferSize-1;\
        BufferName[pBuf##BufferName##R]=dat;                                 \
		return 1;									\
    }
//初始化环形缓冲区
//用法：BufInit(缓冲区名);
#define BufInit(BufferName) pBuf##BufferName##W=pBuf##BufferName##R=0

#endif /* MIDDLEWARE_ROUTEBUFFER_H_ */
