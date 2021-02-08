/*
 * SCS.h
 * ���ش��ж��ͨ�Ų�Э�����
 * ����: 2017.8.22
 * ����: ̷����
 */

#ifndef _SCS_H
#define _SCS_H

#include "INST.h"

class SCS{
public:
	SCS();
	SCS(u8 End);
	SCS(u8 End, u8 Level);
	int genWrite(u8 ID, u8 MemAddr, u8 *nDat, u8 nLen);//��ͨдָ��
	int regWrite(u8 ID, u8 MemAddr,u8 *nDat, u8 nLen);//�첽дָ��
	void snycWrite(u8 ID[], u8 IDN, u8 MemAddr, u8 *nDat, u8 nLen);//ͬ��дָ��
	int writeByte(u8 ID, u8 MemAddr, u8 bDat);//д1���ֽ�
	int writeWord(u8 ID, u8 MemAddr, u16 wDat);//д2���ֽ�
	int Read(u8 ID, u8 MemAddr, u8 *nData, u8 nLen);//��ָ��
	int readByte(u8 ID, u8 MemAddr);//��1���ֽ�
	int readWord(u8 ID, u8 MemAddr);//��2���ֽ�
public:
	u8	Level;//������صȼ�
	u8	End;//��������С�˽ṹ
protected:
	virtual int writeSCS(unsigned char *nDat, int nLen) = 0;
	virtual int readSCS(unsigned char *nDat, int nLen) = 0;
	virtual int writeSCS(unsigned char bDat) = 0;
	virtual void flushSCS() = 0;
protected:
	void writeBuf(u8 ID, u8 MemAddr, u8 *nDat, u8 nLen, u8 Fun);
	void Host2SCS(u8 *DataL, u8* DataH, u16 Data);//1��16λ�����Ϊ2��8λ��
	u16	SCS2Host(u8 DataL, u8 DataH);//2��8λ�����Ϊ1��16λ��
	int	Ack(u8 ID);//����Ӧ��
};
#endif
