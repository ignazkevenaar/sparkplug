# Adding Presets

A Preset defines the state of a [channel](#channel) that is applied when the mode set in the presets `modeID` is active.

The most basic presets contain a valid [`modeID`](#modes) and an `intensity` as a 8-bit unsigned value:

```c++
const PROGMEM Preset examplePreset =
{
  .modeID = HighBeams,
  .intensity = 255
};
```
_If you omit the `intensity` property, it will be treated as full intensity._

By default, presets make channels 'act' like incandescent bulbs; when a preset is applied, the channel fades in to the desired `intensity`, and fades out slower when the preset is no longer applied.

If you want to emulate LED-based modern vehicle lighting you can set those fade times to different values:

```c++{4,5}
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
