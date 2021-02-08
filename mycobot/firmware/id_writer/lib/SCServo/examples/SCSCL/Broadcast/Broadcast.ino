#include <SCServo.h>

SCSCL sc;

void setup()
{
  Serial1.begin(1000000);
  sc.pSerial = &Serial1;
  sc.WritePos(0xfe, 0, 1000);
  delay(1000);        
}

void loop()
{
  int i;
  for(i=0; i<1023; i+=20)
  {
    sc.WritePos(0xfe, i, 20);
    delay(20);
  }
  for(i=1023; i>0; i-=20)
  {
    sc.WritePos(0xfe, i, 20);
    delay(20);
  }
}
