#include <Arduino.h>
#include "OneButton.h"

void btn_up_clicked() {Serial.println("UP");}
void btn_down_clicked() {Serial.println("DOWN");}
void btn_right_clicked() {Serial.println("RIGHT");}
void btn_left_clicked() {Serial.println("LEFT");}
void btn_ok_clicked() {Serial.println("OK");}
void btn_esc_clicked() {Serial.println("ESC");}

OneButton btn_up(A7, true);
OneButton btn_down(A9, true);
OneButton btn_right(A11, true);
OneButton btn_left(A8, true);
OneButton btn_ok(A6, true);
OneButton btn_esc(A10, true);

void setup() {
  Serial.begin(9600);
  Serial.println("Prueba de botones");

  btn_up.attachClick(btn_up_clicked);
  btn_down.attachClick(btn_down_clicked);
  btn_right.attachClick(btn_right_clicked);
  btn_left.attachClick(btn_left_clicked);
  btn_ok.attachClick(btn_ok_clicked);
  btn_esc.attachClick(btn_esc_clicked);
}

void loop() {
  btn_up.tick();
  btn_down.tick();
  btn_right.tick();
  btn_left.tick();
  btn_ok.tick();
  btn_esc.tick();
}
