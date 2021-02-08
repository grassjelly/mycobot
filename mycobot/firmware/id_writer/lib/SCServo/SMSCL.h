/*
 * SMSCL.h
 * 飞特SMSCL系列串行舵机应用层程序
 * 日期: 2017.11.21
 * 作者: 谭雄乐
 */

#ifndef _SMSCL_H
#define _SMSCL_H


#define		SMSCL_1M			0
#define		SMSCL_0_5M			1
#define		SMSCL_250K			2
#define		SMSCL_128K			3
#define		SMSCL_115200		4
#define		SMSCL_76800			5
#define		SMSCL_57600			6
#define		SMSCL_38400			7

//内存表定义
//-------EPROM(只读)--------
#define SMSCL_VERSION_L 3
#define SMSCL_VERSION_H 4

//-------EPROM(读写)--------
#define SMSCL_ID 5
#define SMSCL_BAUD_RATE 6
#define SMSCL_RETURN_DELAY_TIME 7
#define SMSCL_RETURN_LEVEL 8
#define SMSCL_MIN_ANGLE_LIMIT_L 9
#define SMSCL_MIN_ANGLE_LIMIT_H 10
#define SMSCL_MAX_ANGLE_LIMIT_L 11
#define SMSCL_MAX_ANGLE_LIMIT_H 12
#define SMSCL_LIMIT_TEMPERATURE 13
#define SMSCL_MAX_LIMIT_VOLTAGE 14
#define SMSCL_MIN_LIMIT_VOLTAGE 15
#define SMSCL_MAX_TORQUE_L 16
#define SMSCL_MAX_TORQUE_H 17
#define SMSCL_ALARM_LED 19
#define SMSCL_ALARM_SHUTDOWN 20
#define SMSCL_COMPLIANCE_P 21
#define SMSCL_PUNCH_L 24
#define SMSCL_PUNCH_H 25
#define SMSCL_CW_DEAD 26
#define SMSCL_CCW_DEAD 27
#define SMSCL_OFS_L 33
#define SMSCL_OFS_H 34
#define SMSCL_MODE 35
#define SMSCL_MAX_CURRENT_L 36
#define SMSCL_MAX_CURRENT_H 37	

//-------SRAM(读写)--------
#define SMSCL_TORQUE_ENABLE 40
#define SMSCL_GOAL_POSITION_L 42
#define SMSCL_GOAL_POSITION_H 43
#define SMSCL_GOAL_TIME_L 44
#define SMSCL_GOAL_TIME_H 45
#define SMSCL_GOAL_SPEED_L 46
#define SMSCL_GOAL_SPEED_H 47
#define SMSCL_LOCK 48

//-------SRAM(只读)--------
#define SMSCL_PRESENT_POSITION_L 56
#define SMSCL_PRESENT_POSITION_H 57
#define SMSCL_PRESENT_SPEED_L 58
#define SMSCL_PRESENT_SPEED_H 59
#define SMSCL_PRESENT_LOAD_L 60
#define SMSCL_PRESENT_LOAD_H 61
#define SMSCL_PRESENT_VOLTAGE 62
#define SMSCL_PRESENT_TEMPERATURE 63
#define SMSCL_REGISTERED_INSTRUCTION 64
#define SMSCL_MOVING 66
#define SMSCL_PRESENT_GOALPOS_L 67
#define SMSCL_PRESENT_GOALPOS_H 68
#define SMSCL_PRESENT_CURRENT_L 69
#define SMSCL_PRESENT_CURRENT_H 70

#include "SCSerail.h"

class SMSCL : public SCSerail
{
public:
	SMSCL();
	SMSCL(u8 End);
	SMSCL(u8 End, u8 Level);
	int EnableTorque(u8 ID, u8 Enable);//扭力控制指令
	int WritePos(u8 ID, s16 Position, u16 Time, u16 Speed = 0);//普通写位置指令
	int RegWritePos(u8 ID, s16 Position, u16 Time, u16 Speed = 0);//异步写位置指令
	void RegWriteAction();//执行异步写指令
	void SyncWritePos(u8 ID[], u8 IDN, s16 Position, u16 Time, u16 Speed = 0);//同步写位置指令
	int WriteSpe(u8 ID, s16 Speed);//恒速模式控制指令
	s16 ReadPos(u8 ID, u8 *Err = NULL);//读位置
	int ReadLoad(u8 ID);//读当负载
	int ReadVoltage(u8 ID);//读电压
	int ReadTemper(u8 ID);//读温度
	int Ping(u8 ID);//Ping指令
	int wheelMode(u8 ID);//恒速模式
	int joinMode(u8 ID);//普通伺服模式
	int Reset(u8 ID);//复位舵机参数为默认值
	int WriteOfs(u8 ID, s16 Ofs);//中位校准
	int unLockEprom(u8 ID);//eprom解锁
	int LockEprom(u8 ID);//eprom加锁
	int pwmMode(u8 ID);//PWM输出模式
	int WritePWM(u8 ID, s16 pwmOut);//PWM输出模式指令
private:
	int writePos(u8 ID, s16 Position, u16 Time, u16 Speed, u8 Fun);
};

#endif