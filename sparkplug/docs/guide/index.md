# Guide

Sparkplug is an Arduino boilerplate to add extendible and high-detailed lighting to scale model vehicles.

::: warning
Note: this software is currently under active development: anything can change at any time, API and UI must be considered unstable until we release version 1.0.0.
:::

## Getting started

Sparkplug requires some programming, but is designed to be extendible without having to jump through lots of hoops.

### What is Sparkplug?

Sparkplug is an Arduino boilerplate designed to run on an ESP8266 to add extendible and high-detailed lighting to scale model vehicles.

While being designed to run on the ESP8266, because of the Arduino platform, it can be ported to run on different architectures.

The combination of cheap and well-known hardware and Wifi connectivity for controlling the lights using a [web interface](#coilpack-remote-control) made the esp8266 a fitting solution.

### Installing dependencies

To build and upload the sketch you need either:

* [Arduino IDE](https://www.arduino.cc/en/software) 1.8.15
* [Arduino CLI](https://github.com/arduino/arduino-cli) 0.20

::: info NOTE
To upload any data to the [LittleFS](https://github.com/littlefs-project/littlefs) file system, the Arduino IDE is required.
:::

#### Core

Using Arduino CLI:

```shell
arduino-cli core update-index --additional-urls https://arduino.esp8266.com/stable/package_esp8266com_index.json
arduino-cli core install esp8266:esp8266@3.0.2
```

Using the Arduino IDE board manager you can follow these instructions:
https://github.com/esp8266/Arduino#installing-with-boards-manager

#### Libraries

* [SparkFun LP55231 LED Driver Breakout Arduino Library
](https://github.com/sparkfun/SparkFun_LP55231_Arduino_Library)
* [Adafruit PCA9685 PWM Servo Driver Library](https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library)
* [WebSocket Server and Client for Arduino](https://github.com/Links2004/arduinoWebSockets)
* [PrintCharArray](https://github.com/RobTillaart/PrintCharArray)

Installing these libraries using Arduino CLI:

```shell
arduino-cli lib install "SparkFun LP55231 Breakout" "Adafruit PWM Servo Driver Library" "WebSockets" "PrintCharArray"
```

### Adding config

Sparkplug uses header files in order to separate the configuration for different models from eachother.

To add a new config, create a new directory in the `./configs/` directory, and add a header file. Below is an example config with two modes and a single channel using the built-in LED as an output device:

```cpp
#pragma once

#include "../../src/spark.h"

enum ModeIDs
{
    LowBeams
    Hazards,
};
const int modesCount = 2;
LightingMode modes[modesCount];

PCA9685 pcaDevices[] =
{
  { 0x40, false, 0, 1, false }
};
size_t pcaDevicesCount = COUNT_OF(pcaDevices);

const PROGMEM Preset presetsMainBeams[] =
{
  { LowBeams, PresetModes::Normal, SwopModes::LTP, 0x3333, 100, 100 },
  { HighBeams, PresetModes::Normal, SwopModes::LTP, 0x7777, 200, 200 },
};

Channel channels[] =
{
  { COUNT_OF(presetsMainBeams), presetsMainBeams },
};
const int channelsCount = COUNT_OF(channels);
```

Then include this header in the sketch file after `spark.h`:

```cpp{2}
#include "src/spark.h"
#include "configs/myconfig/myconfig.h"
```

This config contains definitions of:
* Lighting modes.
* Lichting channels.
* Lighting presets.
* I²C output devices.

The config is also the place to hook into any events to run custom code specific to that config.

### Build and upload

## Lighting

Sparkplug organises physical lights — output devices with channels containing state — and functionality of those lights — presets applied when a mode is active — into a readable and extendible syntax:

* [Modes](#modes) - Contain state for lighting modes e.g. low beams, left blinker.
* [Presets](#presets) - Define the state of a channel per mode or combination of modes.
* [Channels](#channels) - Contain lighting state and assigned presets.
* [Devices](#devices) - I²C output devices with an assigned range of channels.

**In short:**
1. Group your desired lighting functionality into modes and name them well.
2. Define presets with the state of any psyical lights for any combination of modes.
3. Define the psysical output channels and assign the previously defined presets to the right channels.
4. Define output devices and assign ranges of channels to the right devices.

### Modes

To group lighting functionality into groups of light with a shared functionality that can be turned on and off with only the relevant lights changing, sparkplug groups those functionalities into "modes".

Modes serve as IDs for presets, so only the relevant presets are applied when a mode changes state.

Modes are defined in your config. Sparkplug does not come with a default set of modes, but you can use the following as an example:

```cpp
enum ModeIDs
{
  DaytimeRunningLights,
  Parking,
  LowBeams,
  HighBeams,
  BlinkL,
  BlinkR,
};

const size_t modesCount = BlinkR + 1;
LightingMode modes[modesCount];
```

The `enum` values should be used to define `modeID`s of [presets](#presets) in a human-readable way.

::: info KEEP IN MIND
The array of `LightingMode` contains state of all modes and should therefore be the same size as the `ModeIDs` enum.
:::

### Presets

A Preset defines the state of a [channel](#channel) that is applied when the mode set in the presets `modeID` is active.

The most basic presets contain a valid [`modeID`](#modes) and an `intensity` as a 16-bit unsigned value:

```cpp
const PROGMEM Preset examplePreset =
{
  .modeID = HighBeams,
  .intensity = 0xFFFF
};
```
_If you omit the `intensity` property, it will be treated as full intensity._

By default, presets make channels 'act' like incandescent bulbs; when a preset is applied, the channel fades in to the desired `intensity`, and fades out slower when the preset is no longer applied.

If you want to emulate LED-based modern vehicle lighting you can set those fade times to different values:

```cpp{4,5}
const PROGMEM Preset exampleLEDPreset =
{
  .modeID = DaytimeRunningLights,
  .fadeSpeedRising = 0,
  .fadeSpeedFalling = 0,
};
```

In most real-world applications, a single vehicle light fixture can serve more than one purpose, so it is likely that a channel has multiple presets defined for each desired state of the bulb. Presets are cascading; they can take or give precedence over other presets.

This allows you to define intricate lighting that takes priority over other modes when needed, but not interfere with other modes when that is not desirable. (e.g. [US tail lights](#us-tail-lights) where the blinker takes priority over the parking lights and brake light)

Presets also support basic blinking.

[Cascading in-depth](#cascading-in-depth)

### Channels

A channel represets a physical light in your model.
previously defined presets are assigned to channels so the output intensity of a channel can be calculated correctly for each combination of active [modes](#modes).

The number of channels your config requires depends on the number of physical LEDs and the output devices that are driving those LEDs. If you have two LED drivers, one with 16 and the other 9 with outputs, you will need 15 channels.

The following example defines a single channel with two basic presets:

```cpp{9}
const PROGMEM Preset presetsMainBeams[] =
{
  { .modeID = LowBeams, .intensity = 0x1111 },
  { .modeID = HighBeams, .intensity = 0x7777 },
};

Channel channels[] =
{
  { COUNT_OF(presetsMainBeams), presetsMainBeams }
};
const size_t channelsCount = COUNT_OF(channels);
```

::: info KEEP IN MIND
All channels should be defined in a global `channels[]` array. In this example, this array only contains a single channel.
:::

How many channels you need depends on the amount of physical lights you plan to include in your project, and the amount of output channels your [hardware](#devices) is able to support.

### Devices

Devices represent external or built-in means to output lighting. Most devices have multiple channels (e.g. LED-driver ICs, or pins on a microcontroller). Every device requires its own driver with a `setup()` and, in the case of an output device, an `output()`.

Devices using the I²C protocol are "hot-swappable"; A setup routine runs when the device is connected, after which the current lighting state is sent to the device.

It comes built-in with support for these LED diver ICs:

* [NXP PCA9685](https://www.nxp.com/docs/en/data-sheet/PCA9685.pdf)
* [TI LP55231](https://www.ti.com/lit/ds/symlink/lp55231.pdf)

Example definition of devices in a config:
```cpp
#pragma once

builtinLED builtin(0);
PCA9685 dashboard(0x40, 0, 4);

WireDevice *wireDevices[] =
{
  &dashboard
};
size_t wireDevicesCount = COUNT_OF(wireDevices);

OutputDevice *outputDevices[] =
{
  &dashboard,
  &builtin,
};
size_t outputDevicesCount = COUNT_OF(outputDevices);
```

* Devices in `wireDevices[]` will be checked for (dis-)connection and initialized when needed.
* Devices in `outputDevices[]` will be updated with changed lighting channels for every frame.

## Presets in-depth

Presets are cascading; they can take or give precedence over other presets:

* Latest takes priority (`LTP`)<br>
  A later preset takes priority over previous presets.
* Lowest takes priority (`LoTP`)<br>
  When a preset with a lower value than the current preset is already active, that preset will take priority, even if it comes before the current preset.
* Highest takes priority (`HTP`)<br>
  When a preset with a higher value than the current preset is already active, that preset will take priority, even if it comes before the current preset.

This allows you to define intricate lighting that takes priority over other modes when needed, but not interfere with other modes when that is not desirable.

Since what you can do with cascading can be a bit hard to grasp, the following examples will make use of different kinds of cascading to hopefully make it understandable as a useful tool.

### Blinkers

Channels support basic blinking functionality that can be used for blinkers, alarm lights etc.

::: info KEEP IN MIND
Channels calculate what preset is applied for any given combination of active modes. Therefore, only a single preset is applied each time. This also means that only a single blinking preset can be applied at the time.
:::

The following example describes a basic blinking preset:
```cpp
const PROGMEM Preset exampleBlinkPreset =
{
  .modeID = BlinkL,
  .mode = PresetModes::Blink,
  .timeOff = 400,
  .timeOn = 200
};
```

This preset is applied and removed when the blink cycle swaps phase. The `timeOff` and `timeOn` properties determine how long the preset is applied and defines the blinks [duty cycle](https://en.wikipedia.org/wiki/Duty_cycle).

### Blinkers with a default state

Most of the time, blinking presets are defined in sets:
* A normal preset<br>
  acting as the default preset that is applied when the blinking preset is in the off-phase. You can use this preset to turn off
* A blinking preset that is applied when the blink phase is in the on-state.

The following example describes a set of blinking presets alternating between half intensity and full intensity:

```cpp
const PROGMEM Preset exampleBlinkPresets[] =
{
  { .modeID = BlinkL, .intensity = 0x7777 },
  { .modeID = BlinkL, .mode = PresetModes::Blink, .intensity = 0xFFFF },
};
```

### Sequential blinkers

When you define multiple channels with blink presets that have the same period (the total of `timeOn` and `timeOff` is equal between them), you can easily configure those channels as a squential blinking pattern.

Example:
```cpp
const PROGMEM Preset presetBlinkerFirst[] =
{
  { .modeID = BlinkL, .mode = PresetModes::Blink, .timeOff = 200, .timeOn = 1000 }
};

const PROGMEM Preset presetBlinkerSecond[] =
{
  { .modeID = BlinkL, .mode = PresetModes::Blink, .timeOff = 400, .timeOn = 800 }
};

const PROGMEM Preset presetBlinkerThird[] =
{
  { .modeID = BlinkL, .mode = PresetModes::Blink, .timeOff = 600, .timeOn = 600 }
};

Channel channels[] =
{
  { COUNT_OF(presetBlinkerFirst), presetBlinkerFirst },
  { COUNT_OF(presetBlinkerSecond), presetBlinkerSecond },
  { COUNT_OF(presetBlinkerThird), presetBlinkerThird },
};
const size_t channelsCount = COUNT_OF(channels);
```

### US tail lights
...with combined brake lights and blinkers.

The way most old North-American cars use a single bulb for tail lights, brake lights and turn signals is [fascinating](https://www.youtube.com/watch?v=O1lZ9n2bxWA).

```cpp
const PROGMEM Preset USTaillightPresets[] =
{
  { .modeID = Parking, .intensity = 0x7777 },
  { .modeID = Brake },
  { .modeID = BlinkL, .intensity = 0 },
  { .modeID = BlinkL, .mode = PresetModes::Blink },
};
```
In this example, the blinking light always alternates between fully off, and fully on, regardless of if the `Brake` or `Parking` modes are applied.

#### Thunderbird

In some older models, the tail lights are bit more [complicated](https://www.youtube.com/watch?v=Qwzxn9ZPW-M): The blinkers and brake lights are 'overlaid' over the parking lights.

The hard part is letting the blinker take priority over the brake lights, while still taking the state of the parking lights into consideration. The following example achieves that effect:

```cpp
const PROGMEM Preset thunderbirdPresets[] =
{
  { .modeID = Brake },
  { .modeID = BlinkL, .intensity = 0 },
  { .modeID = BlinkL, .mode = PresetModes::Blink },
  { .modeID = Parking, .priorityMode = SwopModes::HTP, .intensity = 0x7777 },
};
```

At first glance, the order of the presets might be a little unconventional but here is how it works:

In the example;
* the `Brake` preset is overwritten by the first `BlinkL` preset.
* the `Parking` preset has a `HTP` priority, which only applies the preset when the calculated channel intensity up to that point is **lower** than the preset intensity;<br>
  The intensity of the `Parking` preset is overlaid over the `0` intensity of the first `BlinkL` preset.

_(How to combine this example with the [sequential blinkers](#sequential-blinkers) is left as an exercise for the reader.)_
