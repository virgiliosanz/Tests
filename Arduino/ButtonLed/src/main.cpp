#include <Arduino.h>
#include <OneButton.h>

#define LED  Lco  
#define BUTTON 8

void setup() {
  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  digitalWrite(LED, LOW);
}

byte status = LOW;
void loop() {
    status = digitalRead(BUTTON);
    digitalWrite(LED, !status);

    Serial.println(status);
}
