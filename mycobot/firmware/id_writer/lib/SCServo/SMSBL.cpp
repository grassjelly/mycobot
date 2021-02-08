/*
 * SMSBL.cpp
 * ����SMSBLϵ�д��ж��Ӧ�ò����
 * ����: 2017.11.21
 * ����: ̷����
 */


#include "SMSBL.h"

SMSBL::SMSBL()
{
	End = 0;
}

SMSBL::SMSBL(u8 End):SCSerail(End)
{

}

SMSBL::SMSBL(u8 End, u8 Level):SCSerail(End, Level)
{
}

int SMSBL::EnableTorque(u8 ID, u8 Enable)
{
	return writeByte(ID, SMSBL_TORQUE_ENABLE, Enable);
}

int SMSBL::writePos(u8 ID, s16 Position, u16 Speed, u8 ACC, u8 Fun)
{
	if(Position<0){
		Position = -Position;
		Position |= (1<<15);
	}
	flushSCS();
	u8 buf[7];
	buf[0] = ACC;
	Host2SCS(buf+1, buf+2, Position);
	Host2SCS(buf+3, buf+4, 0);
	Host2SCS(buf+5, buf+6, Speed);
	writeBuf(ID, SMSBL_ACC, buf, 7, Fun);
	return Ack(ID);
}

//дλ��ָ��
//���ID��Positionλ�ã����ٶ�ACC���ٶ�Speed
int SMSBL::WritePos(u8 ID, s16 Position, u16 Speed, u8 ACC)
{
	return writePos(ID, Position, Speed, ACC, INST_WRITE);
}

//�첽дλ��ָ��
//���ID��Positionλ�ã����ٶ�ACC���ٶ�Speed
int SMSBL::RegWritePos(u8 ID, s16 Position, u16 Speed, u8 ACC)
{
	return writePos(ID, Position, Speed, ACC, INST_REG_WRITE);
}

void SMSBL::RegWriteAction()
{
	writeBuf(0xfe, 0, NULL, 0, INST_ACTION);
}

//дλ��ָ��
//���ID[]���飬IDN���鳤�ȣ�Positionλ�ã�ACC���ٶȣ��ٶ�Speed
void SMSBL::SyncWritePos(u8 ID[], u8 IDN, s16 Position, u16 Speed, u8 ACC)
{
	if(Position<0){
		Position = -Position;
		Position |= (1<<15);
	}
	u8 buf[7];
	buf[0] = ACC;
	Host2SCS(buf+1, buf+2, Position);
	Host2SCS(buf+3, buf+4, 0);
	Host2SCS(buf+5, buf+6, Speed);
	snycWrite(ID, IDN, SMSBL_ACC, buf, 7);
}

//��λ�ã���ʱErr=1
s16 SMSBL::ReadPos(u8 ID, u8 *Err)
{
	s16 curPos = readWord(ID, SMSBL_PRESENT_POSITION_L);
	if(curPos==-1){
		if(Err){
			*Err = 1;
		}
		return -1;
	}
	if(curPos&(1<<15)){
		curPos = -(curPos&~(1<<15));
	}
	if(Err){
		*Err = 0;
	}
	
	return curPos;
}
//���ٶȣ���ʱErr=1
s16 SMSBL::ReadSpe(u8 ID, u8 *Err)
{
	s16 curSpe = readWord(ID, SMSBL_PRESENT_SPEED_L);
	if(curSpe==-1){
		if(Err){
			*Err = 1;
		}
		return -1;
	}
	if(curSpe&(1<<15)){
		curSpe = -(curSpe&~(1<<15));
	}
	if(Err){
		*Err = 0;
	}
	
	return curSpe;
}

//�ٶȿ���ģʽ
int SMSBL::WriteSpe(u8 ID, s16 Speed, u8 ACC)
{
	if(Speed<0){
		Speed = -Speed;
		Speed |= (1<<15);
	}
	int res = writeByte(ID, SMSBL_ACC, ACC);
	if(res==-1){
		return -1;
	}
	return writeWord(ID, SMSBL_GOAL_SPEED_L, Speed);
}

//PWM���ģʽ
int SMSBL::WritePWM(u8 ID, s16 pwmOut)
{
	if(pwmOut<0){
		pwmOut = -pwmOut;
		pwmOut |= (1<<15);
	}
	return writeWord(ID, SMSBL_GOAL_SPEED_L, pwmOut);
}

//�����أ���ʱ����-1
int SMSBL::ReadLoad(u8 ID)
{	
	return readWord(ID, SMSBL_PRESENT_LOAD_L);
}
//����ǰ����
int SMSBL::ReadCurrent(u8 ID)
{	
	return readWord(ID, SMSBL_PRESENT_CURRENT_L);
}

//����ѹ����ʱ����-1
int SMSBL::ReadVoltage(u8 ID)
{	
	return readByte(ID, SMSBL_PRESENT_VOLTAGE);
}

//���¶ȣ���ʱ����-1
int SMSBL::ReadTemper(u8 ID)
{	
	return readByte(ID, SMSBL_PRESENT_TEMPERATURE);
}

//Pingָ����ض��ID����ʱ����-1
int SMSBL::Ping(u8 ID)
{
	flushSCS();
	u8 bBuf[6];
	writeBuf(ID, 0, NULL, 0, INST_PING);
	int Size = readSCS(bBuf, 6);
	if(Size==6){
		return bBuf[2];
	}else{
		return -1;
	}
}

int SMSBL::wheelMode(u8 ID)
{
	return writeByte(ID, SMSBL_MODE, 1);		
}

int SMSBL::pwmMode(u8 ID)
{
	return writeByte(ID, SMSBL_MODE, 2);		
}

int SMSBL::joinMode(u8 ID)
{
	return writeByte(ID, SMSBL_MODE, 0);		
}

//��λ�������ΪĬ��ֵ
int SMSBL::Reset(u8 ID)
{
	flushSCS();
	writeBuf(ID, 0, NULL, 0, INST_RESET);
	return Ack(ID);
}

int SMSBL::WriteOfs(u8 ID, s16 Ofs)
{
	if(Ofs<0){
		Ofs = -Ofs;
		Ofs |= (1<<15);
	}
	return writeWord(ID, SMSBL_OFS_L, Ofs);	
}

int SMSBL::unLockEprom(u8 ID)
{
	return writeByte(ID, SMSBL_LOCK, 0);//��EPROM���湦��
}

int SMSBL::LockEprom(u8 ID)
{
	return writeByte(ID, SMSBL_LOCK, 1);//�ر�EPROM���湦��
}