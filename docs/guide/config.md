# Creating a Config

Sparkplug organises physical lights — output devices with channels containing state — and functionality of those lights — presets applied when a mode is active — into a readable and extendible syntax:

* [Modes](#modes) - Contain state for lighting modes e.g. low beams, left blinker.
* [Presets](#presets) - Define the state of a channel per mode or combination of modes.
* [Channels](#channels) - Contain lighting state and assigned presets.
* [Devices](#devices) - I²C output devices with an assigned range of channels.

**To create a lighting setup:**
1. Group your desired lighting functionality into modes and name them well.
2. Define presets with the state of any psyical lights for any combination of modes.
3. Define the psysical output channels and assign the previously defined presets to the right channels.
4. Define output devices and assign ranges of channels to the right devices.

Sparkplug uses header files in order to separate the configuration for different models from each other.

This config contains definitions of:
* I²C output devices.
* Lighting modes.
* Lighting presets.
* Lighting channels.

The config is also the place to hook into any events to run custom code specific to that config.

1. Create a folder inside `/sparkplug/configs` with the name of your config.

2. Create a `config.h` file inside the config folder:

```c++
#pragma once

#include "../../src/spark.h"
```

3. Set your config in the main sketch file `sparkplug.ino`:

```c++{1}
#include "configs/YOUR-FOLDER/config.h"
#include "src/spark.h"

void setup()
{
    ...
```
