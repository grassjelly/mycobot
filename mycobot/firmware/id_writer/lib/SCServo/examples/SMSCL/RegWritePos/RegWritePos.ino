#include <SCServo.h>

SMSCL sm;

void setup()
{
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
}

void loop()
{
	sm.RegWritePos(1, 4095, 2000);
	sm.RegWritePos(2, 4095, 2000);
	sm.RegWriteAction();
	delay(2100);
  
	sm.RegWritePos(1, 0, 3000);
	sm.RegWritePos(2, 0, 3000);
	sm.RegWriteAction();
	delay(3100);
}
