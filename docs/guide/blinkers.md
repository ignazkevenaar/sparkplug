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
  .timeOff = 400,
  .timeOn = 200
};
```

This preset is applied and removed when the blink cycle swaps phase. The `timeOff` and `timeOn` properties determine how long the preset is applied and defines the blinks [duty cycle](https://en.wikipedia.org/wiki/Duty_cycle).

## Blinkers with a default state

Most of the time, blinking presets are defined in sets:
* A normal preset<br>
  acting as the default preset that is applied when the blinking preset is in the off-phase. You can use this preset to turn off
* A blinking preset that is applied when the blink phase is in the on-state.

The following example describes a set of blinking presets alternating between half intensity and full intensity:

```c++
const PROGMEM Preset exampleBlinkPresets[] =
{
  { .modeID = BlinkL, .intensity = 0x7777 },
  { .modeID = BlinkL, .mode = PresetModes::Blink, .intensity = 0xFFFF },
};
```

## Sequential blinkers

When you define multiple channels with blink presets that have the same period (the total of `timeOn` and `timeOff` is equal between them), you can easily configure those channels as a squential blinking pattern.

Example:
```c++
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

## US tail lights
...with combined brake lights and blinkers.

The way most old North-American cars use a single bulb for tail lights, brake lights and turn signals is [fascinating](https://www.youtube.com/watch?v=O1lZ9n2bxWA).

```c++
const PROGMEM Preset USTaillightPresets[] =
{
  { .modeID = Parking, .intensity = 0x7777 },
  { .modeID = Brake },
  { .modeID = BlinkL, .intensity = 0 },
  { .modeID = BlinkL, .mode = PresetModes::Blink },
};
```
In this example, the blinking light always alternates between fully off, and fully on, regardless of if the `Brake` or `Parking` modes are applied.

### Thunderbird

In some older models, the tail lights are bit more [complicated](https://www.youtube.com/watch?v=Qwzxn9ZPW-M): The blinkers and brake lights are 'overlaid' over the parking lights.

The hard part is letting the blinker take priority over the brake lights, while still taking the state of the parking lights into consideration. The following example achieves that effect:

```c++
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
