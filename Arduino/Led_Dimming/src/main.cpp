#include <Arduino.h>

uint8_t pines[] = {6, 2, 3, 4, 5};
uint8_t pwm;
uint8_t npin;

void setup() {
    Serial.begin(115200);
    while (!Serial) { }
    Serial.println("System ready");

    pwm = 0; npin = 0;
    for (uint8_t i = 0; i < 5; i++) {
      Serial.println(pines[i]);
    }
}

void loop() {
  if (npin < 5) {
    pwm ++;
    if (256 == pwm) {
      pwm = 0;
      analogWrite(pines[npin], pwm);
    }
    if (pwm == 255) {
      npin ++;
      Serial.print("Nuevo pin: "); Serial.println(npin);
    }
    if (pwm % 10 == 0) {
      Serial.print(pwm); Serial.print(" - "); Serial.println(pines[npin]);
      analogWrite(pines[npin], pwm);
    }
    delay(12);
  }
}
