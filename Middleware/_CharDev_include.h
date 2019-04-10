/*
 * _CharDev_include.h
 *
 *  Created on: 2019Äê2ÔÂ28ÈÕ
 *      Author: asdf2
 */

#ifndef MIDDLEWARE__CHARDEV_INCLUDE_H_
#define MIDDLEWARE__CHARDEV_INCLUDE_H_

#ifndef _DEVICE_NAME
#error "_DEVICE_NAME must be declared."
#endif

#define GETDEV(a) _COMB_AB(_DEVICE_NAME,a)
//
INT8U GETDEV(PackTrensfer)(INT8U *dat,size_t Len,void (*CallBack)());
INT8U GETDEV(PackReceive)(INT8U *dat,size_t Len,void (*CallBack)());



#endif /* MIDDLEWARE__CHARDEV_INCLUDE_H_ */
