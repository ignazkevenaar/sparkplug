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
_Omitting the `intensity` property will default to full intensity._

By default, presets simulate incandescent bulbs; channels fade in to the desired `intensity`, and fade out slower when the preset is no longer applied.

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

This allows you to define intricate lighting that takes priority over other modes when needed, but not interfere with other modes when that is not desirable. (e.g. US tail lights, where the blinkers take priority over the parking and brake lights)

Presets also support [Blinking](/guide/blinkers) and [Cascading](/guide/cascading) to allow presets to overtake presets with lower priority in different ways.
