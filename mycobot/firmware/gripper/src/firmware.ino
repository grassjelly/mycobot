#include <M5Servo.h>
#include <M5Atom.h>
// python esptool.py --port /dev/ttyUSB0 write_flash --flash_freq 80m 0x000000
//protocol constants
#define	header				        0xfe
#define footer				        0xfa
#define SET_LED               0x6A
#define SET_LED_LEN           5
#define SET_TINY_GRIPPER      0x66
#define SET_TINY_GRIPPER_LEN  3
#define IOTimeOut			        30
#define IORecWrong			      -1

#define SERIAL_PIN            25
#define SERVO_PIN             22
#define CURRENT_SENSOR_PIN    33

M5Servo gripperServo;

uint8_t * setBuff(uint8_t Rdata, uint8_t Gdata, uint8_t Bdata)
{
    static uint8_t DisBuff[2 + 5 * 5 * 3];

    DisBuff[0] = 0x05;
    DisBuff[1] = 0x05;
    
    for (int i = 0; i < 25; i++)
    {
        DisBuff[2 + i * 3 + 0] = Rdata;
        DisBuff[2 + i * 3 + 1] = Gdata;
        DisBuff[2 + i * 3 + 2] = Bdata;
    }

    return DisBuff;
}

void rFlushSerial()
{
    while( Serial1.read() !=-1);
}

int readSerial(unsigned char *nDat, int nLen)
{
  int Size = 0;
  int rec_data;
  unsigned long t_begin = millis();
  unsigned long t_use;

  while(1){
    rec_data = Serial1.read();
    // check data validation
    if (rec_data != IORecWrong)
    { 
      if(nDat)
      {
        nDat[Size] = rec_data;
      }
      Size ++;
      t_begin = millis();
    }
    // check len
    if(Size>=nLen)
    { 
      break;
    }
    // check time out
    t_use = millis() - t_begin;
    if (t_use > IOTimeOut)
    { 
      break;
    }
  }
  return Size;
}

bool checkHeader()
{
  byte bDat;
  byte bBuf[2] = {0,0};
  byte Cnt = 0;

  while(1){
    if(!readSerial(&bDat, 1))
    {
      return 0;      
    }
    bBuf[1] = bBuf[0];
    bBuf[0] = bDat;

    if(bBuf[0]==header && bBuf[1]==header)
    {
      break;
    }
    Cnt++;
    if(Cnt>30)
    {
      return 0;
    }
  }
   return 1;
}

void setup() 
{
    M5.begin(true, false, true);
    M5.dis.displaybuff(setBuff(0x00, 0x00, 0xFF));

    Serial1.begin(1000000, SERIAL_8N1, SERIAL_PIN,-1); //RX: PIN G21
    Serial.begin(9600);

    gripperServo.attach(SERVO_PIN);
    gripperServo.write(60);

    pinMode(CURRENT_SENSOR_PIN, INPUT);
}

void loop() {
	rFlushSerial();
	if (!checkHeader())
		return;

	byte data_len[1];
	byte r_data_5[5];
    byte r_data_3[5];

	if (readSerial(data_len, 1) != 1)
		return;

	switch (static_cast<int>(data_len[0]))
	{
        case 5:
            readSerial(r_data_5, 5);
            switch (int(r_data_5[0]))
            {
                case SET_LED:
                {
                    M5.dis.displaybuff(setBuff(r_data_5[1], r_data_5[2], r_data_5[3]));
                    // Serial.printf("R: %d G: %d B: %d", r, g, b);
                }
            }

        case 3:
            readSerial(r_data_3, 3);
            switch (int(r_data_3[0]))
            {
                case SET_TINY_GRIPPER:
                {
                    bool close = r_data_3[1];

                    if(close)
                    {
                        M5.dis.displaybuff(setBuff(0xFF, 0x00, 0x00));
                        // closeGripper();
                    }
                    else
                    {
                        M5.dis.displaybuff(setBuff(0x00, 0xFF, 0x00));
                        //gripperServo.write(pos);
                    }
                }
            }
    }
}

void closeGripper()
{

}
