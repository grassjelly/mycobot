/*
 * SCSCL.cpp
 * ����SCSCLϵ�д��ж��Ӧ�ò����
 * ����: 2017.11.21
 * ����: ̷����
 */



#include "SCServo.h"

SCSCL::SCSCL()
{
	End = 1;
}

SCSCL::SCSCL(u8 End):SCSerail(End)
{
}

SCSCL::SCSCL(u8 End, u8 Level):SCSerail(End, Level)
{
}

int SCSCL::EnableTorque(u8 ID, u8 Enable)
{
	return writeByte(ID, SCSCL_TORQUE_ENABLE, Enable);
}

int SCSCL::writePos(u8 ID, u16 Position, u16 Time, u16 Speed, u8 Fun)
{
	flushSCS();
	u8 buf[6];
	Host2SCS(buf+0, buf+1, Position);
	Host2SCS(buf+2, buf+3, Time);
	Host2SCS(buf+4, buf+5, Speed);
	writeBuf(ID, SCSCL_GOAL_POSITION_L, buf, 6, Fun);
	return Ack(ID);
}

//дλ��ָ��
//���ID��Positionλ�ã�ִ��ʱ��Time��ִ���ٶ�Speed
int SCSCL::WritePos(u8 ID, u16 Position, u16 Time, u16 Speed)
{
	return writePos(ID, Position, Time, Speed, INST_WRITE);
}

//�첽дλ��ָ��
//���ID��Positionλ�ã�ִ��ʱ��Time��ִ���ٶ�Speed
int SCSCL::RegWritePos(u8 ID, u16 Position, u16 Time, u16 Speed)
{
	return writePos(ID, Position, Time, Speed, INST_REG_WRITE);
}

void SCSCL::RegWriteAction()
{
	writeBuf(0xfe, 0, NULL, 0, INST_ACTION);
}

//дλ��ָ��
//���ID[]���飬IDN���鳤�ȣ�Positionλ�ã�ִ��ʱ��Time��ִ���ٶ�Speed
void SCSCL::SyncWritePos(u8 ID[], u8 IDN, u16 Position, u16 Time, u16 Speed)
{
	u8 buf[6];
	Host2SCS(buf+0, buf+1, Position);
	Host2SCS(buf+2, buf+3, Time);
	Host2SCS(buf+4, buf+5, Speed);
	snycWrite(ID, IDN, SCSCL_GOAL_POSITION_L, buf, 6);
}

//��λ�ã���ʱ����-1
s16 SCSCL::ReadPos(u8 ID)
{
	return readWord(ID, SCSCL_PRESENT_POSITION_L);
}

//PWM���ģʽ
int SCSCL::WritePWM(u8 ID, s16 pwmOut)
{
	if(pwmOut<0){
		pwmOut = -pwmOut;
		pwmOut |= (1<<10);
	}
	return writeWord(ID, SCSCL_GOAL_TIME_L, pwmOut);
}

//�����أ���ʱ����-1
int SCSCL::ReadLoad(u8 ID)
{	
	return readWord(ID, SCSCL_PRESENT_LOAD_L);
}

//����ѹ����ʱ����-1
int SCSCL::ReadVoltage(u8 ID)
{	
	return readByte(ID, SCSCL_PRESENT_VOLTAGE);
}

//���¶ȣ���ʱ����-1
int SCSCL::ReadTemper(u8 ID)
{	
	return readByte(ID, SCSCL_PRESENT_TEMPERATURE);
}

//Pingָ����ض��ID����ʱ����-1
int SCSCL::Ping(u8 ID)
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

int SCSCL::pwmMode(u8 ID)
{
	u8 bBuf[4];
	bBuf[0] = 0;
	bBuf[1] = 0;
	bBuf[2] = 0;
	bBuf[3] = 0;
	return genWrite(ID, SCSCL_MIN_ANGLE_LIMIT_L, bBuf, 4);	
}

int SCSCL::joinMode(u8 ID, u16 minAngle, u16 maxAngle)
{
	u8 bBuf[4];
	Host2SCS(bBuf, bBuf+1, minAngle);
	Host2SCS(bBuf+2, bBuf+3, maxAngle);
	return genWrite(ID, SCSCL_MIN_ANGLE_LIMIT_L, bBuf, 4);
}

//��λ�������ΪĬ��ֵ
int SCSCL::Reset(u8 ID)
{
	flushSCS();
	writeBuf(ID, 0, NULL, 0, INST_RESET);
	return Ack(ID);
}

int SCSCL::unLockEprom(u8 ID)
{
	return writeByte(ID, SCSCL_LOCK, 0);//��EPROM���湦��
}

int SCSCL::LockEprom(u8 ID)
{
	return writeByte(ID, SCSCL_LOCK, 1);//�ر�EPROM���湦��
}