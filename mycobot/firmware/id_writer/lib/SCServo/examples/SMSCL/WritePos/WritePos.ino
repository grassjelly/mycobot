#include <SCServo.h>

SMSCL sm;

void setup()
{
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
}

void loop()
{
  sm.WritePos(1, 4095, 0, 50);//舵机(ID1)以36rmp(50*0.737)速度运行至4095
  delay(2000); //T=20*S/V=20*4095/50=1638<2000
  sm.WritePos(1, 0, 0, 50);//舵机(ID1)以36rmp(50*0.737)0
  delay(2000); //T=20*S/V=20*4095/50=1638<2000
}
