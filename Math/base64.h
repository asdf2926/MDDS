/**
 * `b64.h' - b64
 *
 * copyright (c) 2014 joseph werle
 */

#ifndef MATH_BASE64_H_
#define MATH_BASE64_H_

/**
 * Base64 index table.
 */
#if BASE64_EN>0
//hex转base64表
static const char b64_table[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
  'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
  'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
  'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
  'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
  'w', 'x', 'y', 'z', '0', '1', '2', '3',
  '4', '5', '6', '7', '8', '9', '+', '/'
};
//base64转hex表
static const char b64_table_inv[] = {
  52,53,54,55,56,57,58,59,60,61,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,//starts with '0'
  0x7f,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,
  15,16,17,18,19,20,21,22,23,24,25,0x7f,0x7f,0x7f,0x7f,0x7f,
  0x7f,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
  41,42,43,44,45,46,47,48,49,50,51,0x7f,0x7f,0x7f,0x7f,0x7f
};

/**
 * 数据转Base64字符串。
 * 参数：
 *  const unsigned char *src:源
 *  size_t len：长度
 *  char *dsc：目标
 * 返回：size_t 目标长度
 * 注意：不可用于带MMU系统，产生的base64自带'\000'，目标内存计算方法：（向上对齐到4（len*4/3））+1
 *
 */

size_t Base64Encode (const unsigned char *src, size_t len,char *dsc);

/**
 * 数据转Base64字符串。
 * 参数：
 *  const  char *src:源
 *  size_t len：长度
 *  unsigned char *dsc：目标
 * 返回：size_t 目标长度
 * 注意：产生的数据无'\000'，目标内存计算方法：（len*3/4）-最后‘=’个数
 *
 */

size_t Base64Decode (const char *src, size_t len,unsigned char *dsc);
#endif
#endif /* MATH_BASE64_H_ */
