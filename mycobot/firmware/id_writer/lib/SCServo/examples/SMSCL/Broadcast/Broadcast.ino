#include <SCServo.h>

SMSCL sm;

void setup()
{
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
  sm.WritePos(0xfe, 0, 1000);
  delay(1000);        
}

void loop()
{
  int i;
  for(i=0; i<4095; i+=20)
  {
    sm.WritePos(0xfe, i, 20);
    delay(20);
  }
  for(i=4095; i>0; i-=20)
  {
    sm.WritePos(0xfe, i, 20);
    delay(20);
  }
}
