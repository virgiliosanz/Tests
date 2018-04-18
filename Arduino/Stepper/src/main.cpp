#include <Arduino.h>
#include <Stepper.h>

const int steps_per_revolution = 32;
const int revolutions = 1;
Stepper stepper(steps_per_revolution, A1, A2, A3, A4);

void setup()
{
    Serial.begin(9600);
    stepper.setSpeed(150);

}

void loop()
{
  Serial.println("Arrancando motor");
  stepper.step(steps_per_revolution * 64 * revolutions);
  Serial.println("Parando motor");

  delay(5000); // Milliseconds

}
