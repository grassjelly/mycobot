/*
 * SCSCL.h
 * ����SCSCLϵ�д��ж��Ӧ�ò����
 * ����: 2017.11.21
 * ����: ̷����
 */

#ifndef _SCSCL_H
#define _SCSCL_H


#define		SCSCL_1M			0
#define		SCSCL_0_5M			1
#define		SCSCL_250K			2
#define		SCSCL_128K			3
#define		SCSCL_115200		4
#define		SCSCL_76800			5
#define		SCSCL_57600			6
#define		SCSCL_38400			7

//�ڴ������
//-------EPROM(ֻ��)--------
#define SCSCL_VERSION_L 3
#define SCSCL_VERSION_H 4

//-------EPROM(��д)--------
#define SCSCL_ID 5
#define SCSCL_BAUD_RATE 6
#define SCSCL_RETURN_DELAY_TIME 7
#define SCSCL_RETURN_LEVEL 8
#define SCSCL_MIN_ANGLE_LIMIT_L 9
#define SCSCL_MIN_ANGLE_LIMIT_H 10
#define SCSCL_MAX_ANGLE_LIMIT_L 11
#define SCSCL_MAX_ANGLE_LIMIT_H 12
#define SCSCL_LIMIT_TEMPERATURE 13
#define SCSCL_MAX_LIMIT_VOLTAGE 14
#define SCSCL_MIN_LIMIT_VOLTAGE 15
#define SCSCL_MAX_TORQUE_L 16
#define SCSCL_MAX_TORQUE_H 17
#define SCSCL_ALARM_LED 19
#define SCSCL_ALARM_SHUTDOWN 20
#define SCSCL_COMPLIANCE_P 21
#define SCSCL_PUNCH_L 24
#define SCSCL_PUNCH_H 25
#define SCSCL_CW_DEAD 26
#define SCSCL_CCW_DEAD 27
#define SCSCL_OFS_L 33
#define SCSCL_OFS_H 34
#define SCSCL_MODE 35
#define SCSCL_MAX_CURRENT_L 36
#define SCSCL_MAX_CURRENT_H 37	

//-------SRAM(��д)--------
#define SCSCL_TORQUE_ENABLE 40
#define SCSCL_GOAL_POSITION_L 42
#define SCSCL_GOAL_POSITION_H 43
#define SCSCL_GOAL_TIME_L 44
#define SCSCL_GOAL_TIME_H 45
#define SCSCL_GOAL_SPEED_L 46
#define SCSCL_GOAL_SPEED_H 47
#define SCSCL_LOCK 48

//-------SRAM(ֻ��)--------
#define SCSCL_PRESENT_POSITION_L 56
#define SCSCL_PRESENT_POSITION_H 57
#define SCSCL_PRESENT_SPEED_L 58
#define SCSCL_PRESENT_SPEED_H 59
#define SCSCL_PRESENT_LOAD_L 60
#define SCSCL_PRESENT_LOAD_H 61
#define SCSCL_PRESENT_VOLTAGE 62
#define SCSCL_PRESENT_TEMPERATURE 63
#define SCSCL_REGISTERED_INSTRUCTION 64
#define SCSCL_MOVING 66
#define SCSCL_PRESENT_GOALPOS_L 67
#define SCSCL_PRESENT_GOALPOS_H 68
#define SCSCL_PRESENT_CURRENT_L 69
#define SCSCL_PRESENT_CURRENT_H 70

#include "SCSerail.h"

class SCSCL : public SCSerail
{
public:
	SCSCL();
	SCSCL(u8 End);
	SCSCL(u8 End, u8 Level);
	int EnableTorque(u8 ID, u8 Enable);//Ť������ָ��
	int WritePos(u8 ID, u16 Position, u16 Time, u16 Speed = 0);//��ͨдλ��ָ��
	int RegWritePos(u8 ID, u16 Position, u16 Time, u16 Speed = 0);//�첽дλ��ָ��
	void RegWriteAction();//ִ���첽дָ��
	void SyncWritePos(u8 ID[], u8 IDN, u16 Position, u16 Time, u16 Speed = 0);//ͬ��дλ��ָ��
	s16 ReadPos(u8 ID);//��λ��
	int ReadLoad(u8 ID);//��������
	int ReadVoltage(u8 ID);//����ѹ
	int ReadTemper(u8 ID);//���¶�
	int Ping(u8 ID);//Pingָ��
	int joinMode(u8 ID, u16 minAngle = 0, u16 maxAngle = 1023);//��ͨ�ŷ�ģʽ
	int Reset(u8 ID);//��λ�������ΪĬ��ֵ
	int unLockEprom(u8 ID);//eprom����
	int LockEprom(u8 ID);//eprom����
	int pwmMode(u8 ID);//PWM���ģʽ
	int WritePWM(u8 ID, s16 pwmOut);//PWM���ģʽָ��
private:
	int writePos(u8 ID, u16 Position, u16 Time, u16 Speed, u8 Fun);
};

#endif