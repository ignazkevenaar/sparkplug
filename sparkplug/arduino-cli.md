## Install

```sh
arduino-cli lib install "SparkFun LP55231 Breakout" "Adafruit PWM Servo Driver Library" "WebSockets" "PrintCharArray"

```

## List

```sh
arduino-cli board list
```

## Compile

```sh
arduino-cli compile -b esp8266:esp8266:generic:led=2,eesz=4M3M,baud=921600 -e
arduino-cli compile -b esp8266:esp8266:d1_mini -e
```

Upload after compile.

```sh
arduino-cli compile -b esp8266:esp8266:d1_mini -e -u -p COM8
```

https://arduino.github.io/arduino-cli/latest/getting-started/#adding-3rd-party-cores

## Upload

```sh
arduino-cli upload -p COM8 --fqbn esp8266:esp8266:d1_mini SparkplugNew
```
