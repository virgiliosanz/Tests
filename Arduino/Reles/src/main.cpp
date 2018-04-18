#include <Arduino.h>


const int rele2 = 2;
const int rele3 = 3;

/***   Setup  ***/
void setup() {
    pinMode(rele2, OUTPUT);
    pinMode(rele3, OUTPUT);
}

void loop() {

  digitalWrite(rele2, HIGH);
  digitalWrite(rele3, LOW);
  delay(1000);

  digitalWrite(rele2, LOW);
  digitalWrite(rele3, HIGH);
  delay(1000);
  
}
