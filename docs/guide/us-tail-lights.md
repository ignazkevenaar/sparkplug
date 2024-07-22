# US tail lights
...with combined brake lights and blinkers.

Older North-American cars [use a single bulb](https://www.youtube.com/watch?v=O1lZ9n2bxWA) for tail lights, brake lights and turn signals.

```c++
const PROGMEM Preset USTaillightPresets[] =
{
  { .modeID = Parking, .intensity = 63 },
  { .modeID = Brake },
  { .modeID = BlinkL, .intensity = 0 },
  { .modeID = BlinkL, .mode = PresetModes::Blink },
};
```
In this example, the blinking light always alternates between fully off, and fully on, taking priority over the `Brake` and `Parking` presets.

## Thunderbirds

In some models, the tail lights are bit more [complicated](https://www.youtube.com/watch?v=Qwzxn9ZPW-M): The blinkers and brake lights are 'overlaid' over the parking lights.

The hard part is letting the blinker take priority over the brake lights, while still taking the state of the parking lights into consideration. The following example achieves that effect:

```c++{4,6}
const PROGMEM Preset thunderbirdPresets[] =
{
  { .modeID = Brake },
  { .modeID = BlinkL, .intensity = 0 },
  { .modeID = BlinkL, .mode = PresetModes::Blink },
  { .modeID = Parking, .priorityMode = SwopModes::HTP, .intensity = 63 },
};
```

At first glance, the order of the presets might be a little unconventional but here is how it works:

In the example;
* the `Brake` preset is cancelled by the first `BlinkL` preset.
* the `Parking` preset has a `HTP` priority, which only applies the preset when the calculated channel intensity up to that point is **lower** than the preset intensity;<br>
  The intensity of the `Parking` preset is overlaid over the `0` intensity of the first `BlinkL` preset.

_(How to combine this example with the [sequential blinkers](/guide/sequential-blinkers) is left as an exercise for the reader.)_
