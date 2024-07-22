# Assigning Presets to Channels

A channel represets a single physical light source in your hardware setup.Previously defined presets are assigned to channels so the output intensity of a channel can be calculated correctly for each combination of active [modes](#modes).

The number of channels your config requires depends on the number of physical light sources and the output devices that are driving those. If you have two LED drivers, one with 16 and the other with 9 outputs, you must define 15 channels in your config.

The following example defines a single channel with two basic presets:

```c++{9}
const PROGMEM Preset presetsHeadlightLeft[] =
{
    { .modeID = LowBeams, .intensity = 32 },
    { .modeID = HighBeams, .intensity = 128 },
};

Channel channels[] =
{
    { COUNT_OF(presetsHeadlightLeft), presetsHeadlightLeft }
};
const size_t channelsCount = COUNT_OF(channels);
```

::: info KEEP IN MIND
All channels should be defined in a global `channels[]` array. In this example, this array only contains a single channel.
:::

How many channels you need depends on the amount of physical lights you plan to include in your project, and the amount of output channels your [hardware](/guide/devices) is able to support.
