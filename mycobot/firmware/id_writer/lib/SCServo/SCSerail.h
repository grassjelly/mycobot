/*
 * SCServo.h
 * 飞特串行舵机硬件接口层程序
 * 日期: 2017.8.22
 * 作者: 谭雄乐
 */

#ifndef _SCSERIAL_H
#define _SCSERIAL_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "SCS.h"

class SCSerail : public SCS
{
public:
	SCSerail();
	SCSerail(u8 End);
	SCSerail(u8 End, u8 Level);
	virtual int writeSCS(unsigned char *nDat, int nLen);//输出nLen字节
	virtual int readSCS(unsigned char *nDat, int nLen);//输入nLen字节
	virtual int writeSCS(unsigned char bDat);//输出1字节
	virtual void flushSCS();//刷新接口缓冲区
public:
	unsigned long int IOTimeOut;//输入输出超时
	HardwareSerial *pSerial;//串口指针
};

#endif