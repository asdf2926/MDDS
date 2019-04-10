/*


 * Time.h


 *


 *  Created on: 2019年2月2日


 *      Author: asdf2


 */





#ifndef MATH_TIME_H_


#define MATH_TIME_H_





//时间戳和时间工具


//用多少加多少


//现在使用时间戳单位为ms，以2000/01/01 00：00：00.000为0，时间戳类型为64为有符号数


//注意：64位数似乎在MSP430上没有正常工作








//转换时间戳为时间
//参数：
//  UTime Timestamp：时间戳
//返回：Time：时间
//注意：只支持正数时间戳，且时间戳过大时运行时间可能非常长

Time ConventTimestampToTime(UTime Timestamp);

UTime ConventTimeToTimestamp(Time t);


//转换时间戳为UNIX时间戳


//  UTime Timestamp：时间戳


//返回：INT32S：UNIX时间戳


//注意：注意数据溢出


inline INT32S ConventTimestampToUnixTimestamp(UTime Timestamp);


//size:10
INT8U *ConventTimeToArray(Time t,INT8U *out);
Time ConventArrayToTime(INT8U *in);



#endif /* MATH_TIME_H_ */


