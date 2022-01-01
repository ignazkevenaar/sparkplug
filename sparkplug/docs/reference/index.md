# Reference

## Events

Events are [weak functions](https://en.wikipedia.org/wiki/Weak_symbol) that can be used in your configuration to react to changes in the main program loop.

Default return values of non-overridden events with a `bool` return type return `true`.
### onInitialize

Called at end of default initialization. Run any config-specific initialization in this callback.

**Usage:**

```cpp
bool onInitialize()
{
  // if (error) return false;
  return true;
}
```

**Arguments:** None.

**Return type**: `bool` — To stop execution after an initialization error, return `false`.

### onUpdate

Called at end of each `loop()` iteration. Run any config-specific initialization for in this callback.

**Usage:**

```cpp
void onUpdate()
{
  // Foo.
}
```

**Arguments:** None.

**Return type**: `void`

### onLightingModeChanged

Called when a [`mode`](/guide/#modes) is about to change state. Channels are only recalculated when the event handler returns `true`. New mode state can be accessed using the modes `nextState` property.

**Usage:**

```cpp
bool onLightingModeChanged(int modeID)
{
  LightingMode &mode = modes[i];
  if (mode.currentState < mode.nextState)
  {
    // Foo.
  }
  return true;
}
```

**Arguments:**

* `int` `modeID` — ID of the mode that changed.

**Return type**: `bool` — To discard the mode change, return `false`.

### onBlinkPhaseChanged

Called whenever a `Channel` that is currently in `Blink` mode changes blink phase.

**Usage:**

```cpp
bool onBlinkPhaseChanged(Channel &channel)
{
  // return false // Prevent blink phase change.
  return true; // Allow blink phase change.
}
```

**Arguments:**

* `Channel` `&channel` — Channel reference which blink phase changed.

**Return type**: `bool` — To discard the blink phase change, return `false`.

### onSocketConnectionChanged

Called when a websocket client connects or disconnects to the websockets server.

**Usage:**

```cpp
void onSocketConnectionChanged(uint8_t connectedClients)
{
  // Foo.
}
```

**Arguments:**

* `uint8_t` `connectedClients` — Number of connected clients after the connection event.

**Return type**: `void`

### onDeviceConnectionChanged

Called when a `WireDevice` connects or disconnects to the wire bus. In the case of connection, the event is called _after_ the device's `setup()`-routine has run.

**Usage:**

```cpp
void onSocketConnectionChanged(uint8_t connectedClients)
{
  // return false // Don't recalculate channel values.
  return true; // Recalculate channel values.
}
```

**Arguments:**

* `WireDevice` `&device` — Reference to the `WireDevice` that co.

**Return type**: `bool` — To prevent recalculation of [channels](/guide/#channels) return `false`.

## Output devices

:::tip KEEP IN MIND
Output devices require consecutive channels.
:::

### Digital pin as output

Wrapper to use any digital or PWM pin for light output.

**Usage:**

:::warning TODO
Improve example with actual code and sensible defaults.
:::

```cpp{3}
// Initialize PinDevice on LED_BUILTIN and pin 7, totaling 2 pins,
// starting from channel 0 to 1.
PinDevice pinDevice({ LED_BUILTIN, 7 }, 2, 0, 1);

WireDevice *wireDevices[] = { &pinDevice };
size_t wireDevicesCount = COUNT_OF(wireDevices);

OutputDevice *outputDevices[] = { &pinDevice };
size_t outputDevicesCount = COUNT_OF(outputDevices);
```

**Constructor arguments:**

* `uint8_t` `*pins_` — Array of pins to be used for lighting output.
* `size_t` `pinCount_` — Number of pins defined in `*pins` array.
* `uint16_t` `channelFrom_` — Starting index of [`channels[]`](/guide/#channels) that the device will output.
* `uint16_t` `channelCount_` — Number of channels to output from the starting index.

### PCA9685

[**Datasheet**](https://www.nxp.com/docs/en/data-sheet/PCA9685.pdf)

**Type:** `WireDevice`

**Usage:**

```cpp{3}
// Initialize PCA9685 on address 0x40,
// starting from channel 0 to 16, without totem pole output.
PCA9685 pcaDevice(0x40, 0, 16, false);

WireDevice *wireDevices[] = { &pcaDevice };
size_t wireDevicesCount = COUNT_OF(wireDevices);

OutputDevice *outputDevices[] = { &pcaDevice };
size_t outputDevicesCount = COUNT_OF(outputDevices);
```

**Constructor arguments:**

* `uint8_t` `address_` — I²C address used for communication.
* `size_t` `address_` — I²C address used for communication.
* `uint16_t` `channelFrom_` — Starting index of [`channels[]`](/guide/#channels) that the device will output.
* `uint16_t` `channelCount_` — Number of channels to output from the starting index.
* `bool` `totemPoleOutput_` — Outputs are set as [totem pole](https://en.wikipedia.org/wiki/Push%E2%80%93pull_output) drivers when `true` and [open-drain](https://en.wikipedia.org/wiki/Open_collector) outputs when `false`.

**I²C Address range:** [`0x40`](# "64")—[`0x7F`](# "127")

### LP55231

[**Datasheet**](https://www.ti.com/lit/ds/symlink/lp55231.pdf)

**Type:** `WireDevice`

**Usage:**

```cpp{3}
// Initialize LP55231 on address 0x32,
// starting from channel 16 to 25, with logarithmic brightness.
LP55231 lpDevice(0x32, 16, 9, true);

WireDevice *wireDevices[] = { &lpDevice };
size_t wireDevicesCount = COUNT_OF(wireDevices);

OutputDevice *outputDevices[] = { &lpDevice };
size_t outputDevicesCount = COUNT_OF(outputDevices);
```

**Constructor arguments:**

* `uint8_t` `address_` — I²C address used for communication.
* `uint16_t` `channelFrom_` — Starting index of [`channels[]`](/guide/#channels) that the device will output.
* `uint16_t` `channelCount_` — Number of channels to output from the starting index.
* `bool` `logarithmicBrightness_` — Outputs are set to [logarithmic brightness](https://learn.adafruit.com/led-tricks-gamma-correction) curve when `true` and linear brightness when `false`.

**I²C Address range:** [`0x32`](# "50")—[`0x35`](# "53")
