#include <SCServo.h>

SMSBL sm;

void setup()
{
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
  sm.RegWritePos(1, 0, 50);
  sm.RegWritePos(2, 0, 50);
  sm.RegWriteAction();
  delay(2000);
}

void loop()
{
	sm.RegWritePos(1, 4095, 50, 5);
	sm.RegWritePos(2, 4095, 50, 5);
	sm.RegWriteAction();
	delay(6000);
	sm.RegWritePos(1, 0, 20, 5);
	sm.RegWritePos(2, 0, 20, 5);
	sm.RegWriteAction();
	delay(6000);
}
