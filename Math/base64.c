/**
 * `dscode.c' - b64
 *https://github.com/littlstar/b64.c
 * copyright (c) 2014 joseph werle
 */

//#include <stdio.h>
//#include <stdlib.h>
#include "includes.h"
#include <ctype.h>
#include "base64.h"
#if BASE64_EN>0
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

size_t Base64Encode (const unsigned char *src, size_t len,char *dsc) {
  int i = 0;
  int j = 0;
  size_t size = 0;
  while (len--) {
    i++;
    if (3 == i) {
      dsc[size++] = b64_table[(src[0] & 0xfc) >> 2];
      dsc[size++] = b64_table[((src[0] & 0x03) << 4) + ((src[1] & 0xf0) >> 4)];
      dsc[size++] = b64_table[((src[1] & 0x0f) << 2) + ((src[2] & 0xc0) >> 6)];
      dsc[size++] = b64_table[src[2] & 0x3f];
      // reset index
      i = 0;
      src+=3;
    }
  }
  // remainder
  j=i;
  if (i > 0) {
    // fill `tmp' with `\0' at most 3 times

    // perform same codsc as above
    dsc[size++] = b64_table[(src[0] & 0xfc) >> 2];
    dsc[size++] = b64_table[((src[0] & 0x03) << 4) + ((src[1] & 0xf0) >> 4)];
    dsc[size++] = b64_table[((src[1] & 0x0f) << 2) + ((src[2] & 0xc0) >> 6)];
    dsc[size++] = b64_table[src[2] & 0x3f];
     while ((i++ < 3)) {
      dsc[--size] = '=';
    }
  }
  size+=3-j;
  // Make sure we have enough space to add '\0' character at end.
  dsc[size++] = '\0';

  return size;
}

/**
 * `dscode.c' - b64
 *
 * copyright (c) 2014 joseph werle
 */
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

size_t Base64Decode (const char *src, size_t len,unsigned char *dsc) {
  int i = 0;
  int j = 0;
  size_t size = 0;
  unsigned char tmp[4];

  // parse until end of source
  while (len--) {
    i++;
    // if 4 bytes read then dscode into `buf'
    if (4 == i) {
      if((b64_table_inv[src[0]]==0x7f)||(src[0]<'0'))break;
      if((b64_table_inv[src[1]]==0x7f)||(src[0]<'0'))break;
      if((b64_table_inv[src[2]]==0x7f)||(src[0]<'0'))break;
      if((b64_table_inv[src[3]]==0x7f)||(src[0]<'0'))break;
     // dscode
      dsc[size++] = (b64_table_inv[src[0]] << 2) + ((b64_table_inv[src[1]] & 0x30) >> 4);
      dsc[size++] = ((b64_table_inv[src[1]] & 0xf) << 4) + ((b64_table_inv[src[2]] & 0x3c) >> 2);
      dsc[size++] = ((b64_table_inv[src[2]] & 0x3) << 6) + b64_table_inv[src[3]];
      // reset
      i = 0;
      src+=4;
    }
  }
  // remainder
  if (i > 0) {
    for(j=0;j<i;j++)tmp[j] =src[j];
    // fill `tmp' with `\0' at most 4 times
    for (j = i; j < 4; ++j) {
      tmp[j] = 'A';
    }

    // translate remainder
    for (j = 0; j < 4; ++j) {
        tmp[j] = b64_table_inv[tmp[j]];
    }
    i--;//i==2-->one character
    // dscode remainder
    if(i-->0)dsc[size++] = (tmp[0] << 2) + ((tmp[1] & 0x30) >> 4);
    if(i-->0)dsc[size++] = ((tmp[1] & 0xf) << 4) + ((tmp[2] & 0x3c) >> 2);
    if(i-->0)dsc[size++] = ((tmp[2] & 0x3) << 6) + tmp[3];
  }

  return size;
}
#endif
