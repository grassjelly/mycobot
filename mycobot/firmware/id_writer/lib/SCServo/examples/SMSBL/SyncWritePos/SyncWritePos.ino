#include <SCServo.h>

SMSBL sm;

byte ID[2];
void setup()
{
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
  ID[0] = 1;
  ID[1] = 2;
  sm.SyncWritePos(ID, 2, 0, 50);
  delay(2000);
}

void loop()
{
	sm.SyncWritePos(ID, 2, 4095, 50, 5);
	delay(6000);
	sm.SyncWritePos(ID, 2, 0, 50, 5);
	delay(6000);
}
