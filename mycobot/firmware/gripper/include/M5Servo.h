#ifndef _M5_SERVO_
#define _M5_SERVO_

// http://ogimotokin.hatenablog.com/entry/2018/07/22/182140
//SOURCE: https://botalab.tech/m5stack_drive_rcservo/
class M5Servo{
protected:
  constexpr static const float MIN_WIDTH_MS = 1;
  constexpr static const float MAX_WIDTH_MS = 2;

  // サーボ信号の１サイクル　50Hz:20ms
  constexpr static const int LEDC_CHANNEL = 1;
  constexpr static const int LEDC_SERVO_FREQ = 50;
  constexpr static const int LEDC_TIMER_BIT = 16;
  int pin_;
  int angle_;

public:
  // M5Servo();

  void attach(int pin){
    pin_ = pin;
    ledcSetup(LEDC_CHANNEL, LEDC_SERVO_FREQ, LEDC_TIMER_BIT) ; // 16ビット精度で制御
    ledcAttachPin(pin_, LEDC_CHANNEL) ;
    ledcSetup(1, 50, 16); // channel 1, 50 Hz, 16-bit width
  }



  /**
   * send reference angle to servo
   * @param angle reference angle which is -90--+90 [deg]
   */
  void write(int angle){
    angle_ = angle;
    int servo_out = map(angle, 0, 180, 100, 9000);
    ledcWrite(LEDC_CHANNEL, servo_out);
  }

  int read(){
    return angle_;
  }

};

#endif