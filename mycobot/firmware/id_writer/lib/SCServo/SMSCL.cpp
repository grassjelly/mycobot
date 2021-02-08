/*
 * SMSCL.cpp
 * ����SMSCLϵ�д��ж��Ӧ�ò����
 * ����: 2017.11.21
 * ����: ̷����
 */



#include "SCServo.h"

SMSCL::SMSCL()
{
	End = 0;
}

SMSCL::SMSCL(u8 End):SCSerail(End)
{
}

SMSCL::SMSCL(u8 End, u8 Level):SCSerail(End, Level)
{
}

int SMSCL::EnableTorque(u8 ID, u8 Enable)
{
	return writeByte(ID, SMSCL_TORQUE_ENABLE, Enable);
}

int SMSCL::writePos(u8 ID, s16 Position, u16 Time, u16 Speed, u8 Fun)
{
	if(Position<0){
		Position = -Position;
		Position |= (1<<15);
	}
	flushSCS();
	u8 buf[6];
	Host2SCS(buf+0, buf+1, Position);
	Host2SCS(buf+2, buf+3, Time);
	Host2SCS(buf+4, buf+5, Speed);
	writeBuf(ID, SMSCL_GOAL_POSITION_L, buf, 6, Fun);
	return Ack(ID);
}

//дλ��ָ��
//���ID��Positionλ�ã�ִ��ʱ��Time��ִ���ٶ�Speed
int SMSCL::WritePos(u8 ID, s16 Position, u16 Time, u16 Speed)
{
	return writePos(ID, Position, Time, Speed, INST_WRITE);
}

//�첽дλ��ָ��
//���ID��Positionλ�ã�ִ��ʱ��Time��ִ���ٶ�Speed
int SMSCL::RegWritePos(u8 ID, s16 Position, u16 Time, u16 Speed)
{
	return writePos(ID, Position, Time, Speed, INST_REG_WRITE);
}

void SMSCL::RegWriteAction()
{
	writeBuf(0xfe, 0, NULL, 0, INST_ACTION);
}

//дλ��ָ��
//���ID[]���飬IDN���鳤�ȣ�Positionλ�ã�ִ��ʱ��Time��ִ���ٶ�Speed
void SMSCL::SyncWritePos(u8 ID[], u8 IDN, s16 Position, u16 Time, u16 Speed)
{
	if(Position<0){
		Position = -Position;
		Position |= (1<<15);
	}
	u8 buf[6];
	Host2SCS(buf+0, buf+1, Position);
	Host2SCS(buf+2, buf+3, Time);
	Host2SCS(buf+4, buf+5, Speed);
	snycWrite(ID, IDN, SMSCL_GOAL_POSITION_L, buf, 6);
}

//��λ�ã���ʱ����Err=1
s16 SMSCL::ReadPos(u8 ID, u8 *Err)
{
	s16 curPos = readWord(ID, SMSCL_PRESENT_POSITION_L);
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

//���ٿ���ָ��
int SMSCL::WriteSpe(u8 ID, s16 Speed)
{
	if(Speed<0){
		Speed = -Speed;
		Speed |= (1<<15);
	}
	return writeWord(ID,SMSCL_GOAL_SPEED_L , Speed);
}

//PWM���ģʽ
int SMSCL::WritePWM(u8 ID, s16 pwmOut)
{
	if(pwmOut<0){
		pwmOut = -pwmOut;
		pwmOut |= (1<<15);
	}
	return writeWord(ID, SMSCL_GOAL_TIME_L, pwmOut);
}

//�����أ���ʱ����-1
int SMSCL::ReadLoad(u8 ID)
{	
	return readWord(ID, SMSCL_PRESENT_LOAD_L);
}

//����ѹ����ʱ����-1
int SMSCL::ReadVoltage(u8 ID)
{	
	return readByte(ID, SMSCL_PRESENT_VOLTAGE);
}

//���¶ȣ���ʱ����-1
int SMSCL::ReadTemper(u8 ID)
{	
	return readByte(ID, SMSCL_PRESENT_TEMPERATURE);
}

//Pingָ����ض��ID����ʱ����-1
int SMSCL::Ping(u8 ID)
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

int SMSCL::wheelMode(u8 ID)
{
	return writeByte(ID, SMSCL_MODE, 1);
}

int SMSCL::pwmMode(u8 ID)
{
	return writeByte(ID, SMSCL_MODE, 2);		
}

int SMSCL::joinMode(u8 ID)
{
	return writeByte(ID, SMSCL_MODE, 0);
}

//��λ�������ΪĬ��ֵ
int SMSCL::Reset(u8 ID)
{
	flushSCS();
	writeBuf(ID, 0, NULL, 0, INST_RESET);
	return Ack(ID);
}

int SMSCL::WriteOfs(u8 ID, s16 Ofs)
{
	if(Ofs<0){
		Ofs = -Ofs;
		Ofs |= (1<<11);
	}
	return writeWord(ID, SMSCL_OFS_L, Ofs);	
}

int SMSCL::unLockEprom(u8 ID)
{
	return writeByte(ID, SMSCL_LOCK, 0);//��EPROM���湦��
}

int SMSCL::LockEprom(u8 ID)
{
	return writeByte(ID, SMSCL_LOCK, 1);//�ر�EPROM���湦��
}