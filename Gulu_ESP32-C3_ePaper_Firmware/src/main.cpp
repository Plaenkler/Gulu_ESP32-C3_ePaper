#include <Arduino.h>
#include <GxEPD2_BW.h>

#include "800x480.h"

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT>
    display(GxEPD2_750_T7(6, 7, 10, 3));

void setup() {
  pinMode(0, OUTPUT);
  display.init();
}

void loop() {
  display.drawImage(image, 0, 0, 800, 480);
  digitalWrite(0, HIGH);
  delay(1000);
  digitalWrite(0, LOW);
  delay(1000);
  esp_sleep_enable_timer_wakeup(10e6);
  esp_deep_sleep_start();
}