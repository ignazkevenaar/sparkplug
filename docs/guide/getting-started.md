# Getting Started

## Supported Hardware

Sparkplug is designed to run on an ESP8266 module. It uses modular LED driver chips on connected to an I²C bus.

## Software Requirements

Sparkplug is an Arduino sketch with interchangable configurations for each of your models.

To build and upload the sketch you need either:

* [Arduino CLI](https://github.com/arduino/arduino-cli) ≥0.28
* [Arduino IDE](https://www.arduino.cc/en/software) ≥1.8.15

To upload any data to the [LittleFS](https://github.com/littlefs-project/littlefs) file system using the Arduino CLI please refer to [this section](#uploading-filesystem)

## Compiling using Arduino CLI

It is recommended to use the Arduino CLI for compiling and uploading your sketch.

When using Arduino CLI, the sketch dependencies are managed; They are automatically downloaded and installed in in isolated folder when compiling.

Dependencies on cores and libraries are tracked in `sketch.yml`.

[Read more](https://arduino.github.io/arduino-cli/latest/sketch-build-process/)

To compile using the default profile:

```shell
arduino-cli compile
```

## Using Arduino IDE 1

### Installing core

Follow these instructions to install the ESP8266 core to the Arduino IDE board manager:
https://github.com/esp8266/Arduino#installing-with-boards-manager

### Installing Libraries

* [SparkFun LP55231 LED Driver Breakout Arduino Library
](https://github.com/sparkfun/SparkFun_LP55231_Arduino_Library)
* [Adafruit PCA9685 PWM Servo Driver Library](https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library)
* [WebSocket Server and Client for Arduino](https://github.com/Links2004/arduinoWebSockets)
* [PrintCharArray](https://github.com/RobTillaart/PrintCharArray)

Refer to `sketch.yml` to install the correct library version tested with the sketch.
