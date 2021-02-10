#define SERVO_PIN 3
#define SENSOR_PIN 2
#define LED_PIN 1
long pulse = 0;

void setup() {
    OCR0A = 0xAF;            
    TIMSK |= _BV(OCIE0A);

    pinMode(LED_PIN, OUTPUT);
    pinMode(SERVO_PIN, OUTPUT);
    pinMode(SENSOR_PIN, INPUT);
}

void loop() {
    unsigned long pwm_val = pulseIn(SENSOR_PIN, HIGH, 20000);
    pulse = map(pwm_val, 0, 500, 2450, 550);
    delay(15); 
}

volatile uint8_t counter = 0;
SIGNAL(TIMER0_COMPA_vect) 
{
  counter += 2;
  if (counter >= 20) {
    counter = 0;
    digitalWrite(SERVO_PIN, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(SERVO_PIN, LOW);
  }
}