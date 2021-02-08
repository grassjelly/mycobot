#include <SCServo.h>

SCSCL sc;

byte ID[2];
void setup()
{
  Serial1.begin(1000000);
  sc.pSerial = &Serial1;
  ID[0] = 1;
  ID[1] = 2;
}

void loop()
{
	sc.SyncWritePos(ID, 2, 1023, 2000);
	delay(2100);
	sc.SyncWritePos(ID, 2, 0, 2000);
	delay(2100);
}
