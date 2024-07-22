# Blinkers

Channels support basic blinking functionality that can be used for blinkers, alarm lights etc.

::: info KEEP IN MIND
Channels calculate what preset is applied for any given combination of active modes. Therefore, only a single preset is applied each time. This also means that only a single blinking preset can be applied at the time.
:::

The following example describes a basic blinking preset:
```c++
const PROGMEM Preset exampleBlinkPreset =
{
  .modeID = BlinkL,
  .mode = PresetModes::Blink,
  .blinkInterval = 600
};
```

This preset is applied and removed when the position in the blink pattern is `1`. The `blinkInterval` property determines how long the total period of the blink lasts.

## Blinkers with a default state

To define the off and on state, blinking presets are defined in sets:
* A 'normal' preset<br>
  acting as the underlying state when the blinking preset is in the off-phase.
* A blinking preset that applies changes when the blink preset is in the on-state.

The following example describes a channel with a set of blinking presets alternating between half and full intensity:

```c++
const PROGMEM Preset exampleBlinkPresets[] =
{
  { .modeID = BlinkL, .intensity = 127 },
  { .modeID = BlinkL, .mode = PresetModes::Blink, .intensity = 255 },
};
```

## Blinking patterns

Blink presets have a pattern that can be set to allow for more control over the blink. It also helps sync multiple blink presets.

Patterns are defined as an unsigned 32-bit integer where each bit represents an on or off state.

The default `blinkPattern` is `0b11111111111111110000000000000000`; A half-on half-off pattern in binary notation.

The most significant bit marks the start of the timeline and the pattern moves from left to right.

::: info KEEP IN MIND
The `blinkInterval` marks the period of the pattern. For the default pattern this means the example preset above is applied for 300ms and then not applied for another 300ms.
:::
