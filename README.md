# Gulu ESP32-C3 ePaper Devboard

<table>
  <tr>
    <td><img src="https://github.com/Plaenkler/Gulu_ESP32-C3_ePaper/assets/60503970/1c677425-d5b5-43d3-83c9-e7d38f8b7d85" alt="Gulu ESP32-C3 ePaper Devboard Front"></td>
    <td><img src="https://github.com/Plaenkler/Gulu_ESP32-C3_ePaper/assets/60503970/6adeaed0-ecd0-44c0-b301-22731d2befba" alt="Gulu ESP32-C3 ePaper Devboard Back"></td>
  </tr>
</table>

## About Gulu ESP32-C3 ePaper

Introducing the **Gulu_ESP32-C3_ePaper** Devboard: a cutting-edge development board powered by the ESP32-C3.
This board features a modular power system, equipped with the [Egg_LDO_1000](https://github.com/Plaenkler/Egg_LDO_1000) by default for efficient performance.
Designed to support a wide range of ePaper displays from **WaveShare** and **Good Display** that require the 0.47 Ohm resistor.

## 📖 Specifications

 * MCU: ESP32-C3-WROOM-02-H4
 * Power supply: [Egg_LDO_1000](https://github.com/Plaenkler/Egg_LDO_1000)
 * Connectivity: SPI, UART/USB, 24-pin FPC ePaper connection

## ⚡ Circuit Diagram

![gulu_circuit diagram](https://github.com/Plaenkler/Gulu_ESP32-C3_ePaper/assets/60503970/1ba6de68-8dc7-44b1-94b2-039d5cceef62)

## Power consumption

The power consumption in deep sleep mode of the ESP32-C3 was measured using the [Power Profiler Kit II](https://www.nordicsemi.com/Products/Development-hardware/Power-Profiler-Kit-2) from Nordic Semiconductor.
The example firmware in this project was used as a benchmark.
A daughter board such as the [Egg_LDO_1000](https://github.com/Plaenkler/Egg_LDO_1000) was not used, and VOUT and GND of the kit were connected directly to the corresponding pads.
During the measurement, a 7.5 inch black and white display ([WFT0583CZ61](https://www.good-display.com/product/396.html)) from [Good Display](https://www.good-display.com) was connected to the FPC port.
The duration of the measurement in this case was one minute after the first cycle of the firmware, which resulted in an average current of **~35μA**.
When the display is not connected, the current is approximately **~10μA** in deep sleep mode.

![One_minute_deep_sleep](https://github.com/Plaenkler/Gulu_ESP32-C3_ePaper/assets/60503970/87c6e501-ffcb-41a7-be25-fa08fab55342)


## Arduino compatibility

During the design phase of the Gulu, a custom set of IO pins was used for the 4-wire SPI connection.
In order for firmware based on the Arduino framework to work on the Gulu, adjustments must be made to the pin definitions.

```cpp
// Default esp32c3>pins_arduino.h
static const uint8_t SS    = 7;
static const uint8_t MOSI  = 6;
static const uint8_t MISO  = 5;
static const uint8_t SCK   = 4;

// Modified esp32c3>pins_arduino.h
static const uint8_t SS    = 7; // EPD_DC
static const uint8_t MOSI  = 4; // EPD_DIN
static const uint8_t MISO  = 6; // EPD_CS
static const uint8_t SCK   = 5; // EPD_SCK
```

## Firmware example

### Display Definition and Image

This section contains a header file with a definition for the display and a sample image.
The display is initialized with the required pins specified for the GxEPD2 library.
Additionally, a sample image is defined as an array of byte data stored in PROGMEM (program memory) of the microcontroller.

```cpp
#ifndef _750_T7_H_
#define _750_T7_H_

#include <GxEPD2_BW.h>

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(
  GxEPD2_750_T7(6, 7, 10, 3)
);

const unsigned char image[] PROGMEM = {
    0x55, 0x55, 0x55, 0x6d, 0xb6, 0xdb, 0x6d, 0xb5, 0x6a, 0xbf, 0xf5, 0x22, ...
```

### Main Program

The first section initializes the necessary components for the firmware.
Firstly, the onboard LED (connected to pin 0) is configured as an output.
Then, the display initialization is called.

```cpp
#include "750_T7.h"

void setup() {
  pinMode(0, OUTPUT);
  display.init();
}
```

In the main part of the program, the sample picture is displayed on the screen, after which the screen is switched to hibernation mode.
Subsequently, the onboard LED is turned on for one second and then turned off.
After that, a timer wakeup for the deep sleep mode is enabled, and the microcontroller is put into deep sleep.

```cpp
void loop() {
  display.drawImage(image, 0, 0, 800, 480);
  display.hibernate();
  digitalWrite(0, 1);
  delay(1e3);
  digitalWrite(0, 0);
  esp_sleep_enable_timer_wakeup(1e7);
  esp_deep_sleep_start();
}
```
