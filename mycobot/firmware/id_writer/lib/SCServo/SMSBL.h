/*
 * SMSBL.h
 * 特SMSBL系列串行舵机应用层程序
 * 日期: 2017.11.21
 * 作者: 谭雄乐
 */

#ifndef _SMSBL_H
#define _SMSBL_H

//波特率定义
#define		SMSBL_1M		0
#define		SMSBL_0_5M		1
#define		SMSBL_250K		2
#define		SMSBL_128K		3
#define		SMSBL_115200	4
#define		SMSBL_76800		5
#define		SMSBL_57600		6
#define		SMSBL_38400		7

//内存表定义
//-------EPROM(只读)--------
#define SMSBL_VERSION_L 0
#define SMSBL_VERSION_H 1
#define SMSBL_MODEL_L 3
#define SMSBL_MODEL_H 4

//-------EPROM(读写)--------
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

//-------SRAM(读写)--------
#define SMSBL_TORQUE_ENABLE 40
#define SMSBL_ACC 41
#define SMSBL_GOAL_POSITION_L 42
#define SMSBL_GOAL_POSITION_H 43
#define SMSBL_GOAL_TIME_L 44
#define SMSBL_GOAL_TIME_H 45
#define SMSBL_GOAL_SPEED_L 78   //46 SM30BL
#define SMSBL_GOAL_SPEED_H 79   //47 SM30BL
#define SMSBL_LOCK 55

//-------SRAM(只读)--------
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
	int EnableTorque(u8 ID, u8 Enable);//扭力控制指令
	int WritePos(u8 ID, s16 Position, u16 Speed, u8 ACC = 0);//普通写位置指令
	int RegWritePos(u8 ID, s16 Position, u16 Speed, u8 ACC = 0);//异步写位置指令
	void RegWriteAction();//执行异步写指令
	void SyncWritePos(u8 ID[], u8 IDN, s16 Position, u16 Speed, u8 ACC = 0);//同步写位置指令
	int WriteSpe(u8 ID, s16 Speed, u8 ACC = 0);//恒速模式控制指令
	s16 ReadPos(u8 ID, u8 *Err = NULL);//读位置
	s16 ReadSpe(u8 ID, u8 *Err = NULL);//读速度
	int ReadLoad(u8 ID);//读当负载
	int ReadCurrent(u8 ID);//读当电流
	int ReadVoltage(u8 ID);//读电压
	int ReadTemper(u8 ID);//读温度
	int Ping(u8 ID);//Ping指令
	int wheelMode(u8 ID);//恒速模式
	int joinMode(u8 ID);//普通伺服模式
	int Reset(u8 ID);//复位舵机参数为默认值
	int WriteOfs(u8 ID, s16 Ofs);//中位校准
	int unLockEprom(u8 ID);//eprom解锁
	int LockEprom(u8 ID);//eprom加锁
	int	pwmMode(u8 ID);//pwm输出模式
	int WritePWM(u8 ID, s16 pwmOut);//PWM输出模式指令
private:
	int writePos(u8 ID, s16 Position, u16 Speed, u8 ACC, u8 Fun);
};

#endif