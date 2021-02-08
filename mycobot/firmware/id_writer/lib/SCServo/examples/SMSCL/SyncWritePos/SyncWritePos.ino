#include <SCServo.h>

SMSCL sm;

byte ID[2];
void setup()
{
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
  ID[0] = 1;
  ID[1] = 2;
}

void loop()
{
	sm.SyncWritePos(ID, 2, 4095, 2000);
	delay(2100);
	sm.SyncWritePos(ID, 2, 0, 2000);
	delay(2100);
}
