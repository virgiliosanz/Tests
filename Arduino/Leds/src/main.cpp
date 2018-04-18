#include <Arduino.h>

#define WHITE 9

unsigned long last;
const unsigned long step = 500;
byte pwm = 0;

void setup() {
  Serial.begin(115200);
  pinMode(WHITE, OUTPUT);
  digitalWrite(WHITE, HIGH);
  last = millis();

  // analogWrite(WHITE, 255);
}


void loop() {
  if ((millis() - last) > step) {
    last = millis();

    analogWrite(WHITE, pwm);

    pwm += 5;
    if (pwm > 255) pwm = 0;

    Serial.print("PWM: "); Serial.println(pwm);

  }
}
