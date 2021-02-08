#include <SCServo.h>

SCSCL sc;

void setup()
{
    Serial.begin(9600);
    Serial3.begin(1000000);
    sc.pSerial = &Serial3;
    // sc.Reset(0xfe);
    sc.writeByte(0xfe, SCSCL_LOCK, 0);
    sc.writeByte(0xfe, SCSCL_ID, 7);
    sc.writeWord(7, SCSCL_MAX_TORQUE_L, 500);
    sc.writeByte(7, SCSCL_LOCK, 1);
}

void loop()
{
    sc.WritePos(7,248, 20);
    delay(3000);
    sc.WritePos(7,76, 20);
    delay(3000);
}