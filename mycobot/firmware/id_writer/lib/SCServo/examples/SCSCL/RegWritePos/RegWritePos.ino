#include <SCServo.h>

SCSCL sm;

void setup()
{
  Serial1.begin(1000000);
  sm.pSerial = &Serial1;
}

void loop()
{
	sm.RegWritePos(1, 1023, 2000);
	sm.RegWritePos(2, 1023, 2000);
	sm.RegWriteAction();
	delay(2100);
  
	sm.RegWritePos(1, 0, 3000);
	sm.RegWritePos(2, 0, 3000);
	sm.RegWriteAction();
	delay(3100);
}
