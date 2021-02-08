通信层:SCS
----------------------------
硬件接口层:SCSerail
----------------------------
应用层:SMSBL SMSCL SCSCL分别对应飞特三个系列舵机



SMSBL smbl;//定义无SMBL系列舵机
SMSCL smcl;//定义无SM系列舵机
SCSCL sc;//定义无SC系列舵机
SM\SMBL\SC各自接口参考相应头文件



INST.h---指令定义头文件
SCS.h/SCS.cpp---通信层程序
SCSerail.h/SCSerail.cpp---硬件接口程序
SMSBL.h/SMSBL.cpp---SMBL应用层程序
SMSCL.h/SMSCL.cpp---SM应用层程序
SCSCL.h/SCSCL.cpp---SCSCL应用层程序
(内存表定义于应用层程序头文件SMSBL.h\SMSCL.h\SCSCL.h中不同系列舵内存表定义存在差异)


                       SMSBL类
SCS类<---SCSerail类<---SMSCL类
                       SCSCL类


