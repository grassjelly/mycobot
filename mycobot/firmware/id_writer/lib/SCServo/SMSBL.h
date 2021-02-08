/*
 * SMSBL.h
 * ��SMSBLϵ�д��ж��Ӧ�ò����
 * ����: 2017.11.21
 * ����: ̷����
 */

#ifndef _SMSBL_H
#define _SMSBL_H

//�����ʶ���
#define		SMSBL_1M		0
#define		SMSBL_0_5M		1
#define		SMSBL_250K		2
#define		SMSBL_128K		3
#define		SMSBL_115200	4
#define		SMSBL_76800		5
#define		SMSBL_57600		6
#define		SMSBL_38400		7

//�ڴ����
//-------EPROM(ֻ��)--------
#define SMSBL_VERSION_L 0
#define SMSBL_VERSION_H 1
#define SMSBL_MODEL_L 3
#define SMSBL_MODEL_H 4

//-------EPROM(��д)--------
#define SMSBL_ID 5
#define SMSBL_BAUD_RATE 6
#define SMSBL_RETURN_DELAY_TIME 7
#define SMSBL_RETURN_LEVEL 8
#define SMSBL_MIN_ANGLE_LIMIT_L 9
#define SMSBL_MIN_ANGLE_LIMIT_H 10
#define SMSBL_MAX_ANGLE_LIMIT_L 11
#define SMSBL_MAX_ANGLE_LIMIT_H 12
#define SMSBL_LIMIT_TEMPERATURE 13
#define SMSBL_MAX_LIMIT_VOLTAGE 14
#define SMSBL_MIN_LIMIT_VOLTAGE 15
#define SMSBL_MAX_TORQUE_L 16
#define SMSBL_MAX_TORQUE_H 17
#define SMSBL_ALARM_LED 19
#define SMSBL_ALARM_SHUTDOWN 20
#define SMSBL_COMPLIANCE_P 21
#define SMSBL_COMPLIANCE_D 22
#define SMSBL_COMPLIANCE_I 23
#define SMSBL_PUNCH_L 24
#define SMSBL_PUNCH_H 25
#define SMSBL_CW_DEAD 26
#define SMSBL_CCW_DEAD 27
#define SMSBL_MAX_CURRENT_L 28
#define SMSBL_MAX_CURRENT_H 29
#define SMSBL_ANGLE_RESOLVING 30
#define SMSBL_OFS_L 31
#define SMSBL_OFS_H 32
#define SMSBL_MODE 31            // 33 SM30BL
#define SMSBL_PROTECT_TORQUE 34
#define SMSBL_PROTECT_TIME 35
#define SMSBL_OVLOAD_TORQUE 36

//-------SRAM(��д)--------
#define SMSBL_TORQUE_ENABLE 40
#define SMSBL_ACC 41
#define SMSBL_GOAL_POSITION_L 42
#define SMSBL_GOAL_POSITION_H 43
#define SMSBL_GOAL_TIME_L 44
#define SMSBL_GOAL_TIME_H 45
#define SMSBL_GOAL_SPEED_L 78   //46 SM30BL
#define SMSBL_GOAL_SPEED_H 79   //47 SM30BL
#define SMSBL_LOCK 55

//-------SRAM(ֻ��)--------
#define SMSBL_PRESENT_POSITION_L 56
#define SMSBL_PRESENT_POSITION_H 57
#define SMSBL_PRESENT_SPEED_L 58
#define SMSBL_PRESENT_SPEED_H 59
#define SMSBL_PRESENT_LOAD_L 60
#define SMSBL_PRESENT_LOAD_H 61
#define SMSBL_PRESENT_VOLTAGE 62
#define SMSBL_PRESENT_TEMPERATURE 63
#define SMSBL_REGISTERED_INSTRUCTION 64
#define SMSBL_MOVING 66
#define SMSBL_PRESENT_GOALPOS_L 67
#define SMSBL_PRESENT_GOALPOS_H 68
#define SMSBL_PRESENT_CURRENT_L 69
#define SMSBL_PRESENT_CURRENT_H 70

#include "SCSerail.h"

class SMSBL : public SCSerail
{
public:
	SMSBL();
	SMSBL(u8 End);
	SMSBL(u8 End, u8 Level);
	int EnableTorque(u8 ID, u8 Enable);//Ť������ָ��
	int WritePos(u8 ID, s16 Position, u16 Speed, u8 ACC = 0);//��ͨдλ��ָ��
	int RegWritePos(u8 ID, s16 Position, u16 Speed, u8 ACC = 0);//�첽дλ��ָ��
	void RegWriteAction();//ִ���첽дָ��
	void SyncWritePos(u8 ID[], u8 IDN, s16 Position, u16 Speed, u8 ACC = 0);//ͬ��дλ��ָ��
	int WriteSpe(u8 ID, s16 Speed, u8 ACC = 0);//����ģʽ����ָ��
	s16 ReadPos(u8 ID, u8 *Err = NULL);//��λ��
	s16 ReadSpe(u8 ID, u8 *Err = NULL);//���ٶ�
	int ReadLoad(u8 ID);//��������
	int ReadCurrent(u8 ID);//��������
	int ReadVoltage(u8 ID);//����ѹ
	int ReadTemper(u8 ID);//���¶�
	int Ping(u8 ID);//Pingָ��
	int wheelMode(u8 ID);//����ģʽ
	int joinMode(u8 ID);//��ͨ�ŷ�ģʽ
	int Reset(u8 ID);//��λ�������ΪĬ��ֵ
	int WriteOfs(u8 ID, s16 Ofs);//��λУ׼
	int unLockEprom(u8 ID);//eprom����
	int LockEprom(u8 ID);//eprom����
	int	pwmMode(u8 ID);//pwm���ģʽ
	int WritePWM(u8 ID, s16 pwmOut);//PWM���ģʽָ��
private:
	int writePos(u8 ID, s16 Position, u16 Speed, u8 ACC, u8 Fun);
};

#endif