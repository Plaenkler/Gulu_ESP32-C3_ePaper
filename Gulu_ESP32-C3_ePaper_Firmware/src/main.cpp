#include <GxEPD2_BW.h>
#include "800x480.h"

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(
  GxEPD2_750_T7(6, 7, 10, 3)
);

void setup() {
  pinMode(0, OUTPUT);
  display.init();
}

void loop() {
  display.drawImage(image, 0, 0, 800, 480);
  display.hibernate();
  digitalWrite(0, 1);
  delay(1e3);
  digitalWrite(0, 0);
  esp_sleep_enable_timer_wakeup(1e7);
  esp_deep_sleep_start();
}