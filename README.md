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
 * Connectivity: I2C, UART over USB, UART

## ⚡ Circuit Diagram

Coming soon...

## Software capabilities

Coming soon...

## Board and connections

Coming soon...

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

Coming soon...

## Power consumption

The power consumption in deep sleep mode of the ESP32-C3 was measured using the [Power Profiler Kit II](https://www.nordicsemi.com/Products/Development-hardware/Power-Profiler-Kit-2) from Nordic Semiconductor.
The example firmware in this project was used as a benchmark.
A daughter board such as the [Egg_LDO_1000](https://github.com/Plaenkler/Egg_LDO_1000) was not used, and VOUT and GND of the kit were connected directly to the corresponding pads.
During the measurement, a 7.5 inch black and white display ([WFT0583CZ61](https://www.good-display.com/product/396.html)) from [Good Display](https://www.good-display.com) was connected to the FPC port.
The duration of the measurement in this case was one minute after the first cycle of the firmware, which resulted in an average current of **~35μA**.
When the display is not connected, the current is approximately **~10μA** in deep sleep mode.

![One_minute_deep_sleep](https://github.com/Plaenkler/Gulu_ESP32-C3_ePaper/assets/60503970/87c6e501-ffcb-41a7-be25-fa08fab55342)

