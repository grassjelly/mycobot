#include <M5Stack.h>

void setup() 
{
    Serial.begin(115200);
    Serial2.begin(1000000);
}

void loop() 
{
    while (Serial2.available() > 0) 
        Serial.println(Serial2.read());
    }
}