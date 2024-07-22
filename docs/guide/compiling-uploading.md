# Compiling and Uploading

## Compiling using Arduino CLI

It is recommended to use the Arduino CLI for compiling and uploading your sketch.

When using Arduino CLI, the sketch dependencies are managed; They are automatically downloaded and installed in in isolated folder when compiling.

Dependencies on cores and libraries are defined in `sketch.yml`.

[Read more](https://arduino.github.io/arduino-cli/latest/sketch-build-process/)

To compile using the default profile (for generic ESP8266 modules):

```shell
arduino-cli compile
```

### Uploading

First, list connected boards:

```shell
arduino-cli board list
```

Then, compile and upload after setting your desired port:

```shell
arduino-cli compile -u -p [YOUR_PORT]
```

## Using Arduino IDE 1

### Installing core

Follow these instructions to install the ESP8266 core to the Arduino IDE board manager:
https://github.com/esp8266/Arduino#installing-with-boards-manager

### Installing Libraries

Arduino IDE 1 has no way of automatically managing and installing sketch dependencies from `sketch.yml`.

Please refer to `sketch.yml` to install the correct cores and dependencies.
