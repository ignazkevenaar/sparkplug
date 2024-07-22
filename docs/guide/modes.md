# Defining Modes

To group lighting functionality into groups of light with a shared functionality that can be turned on and off with only the relevant lights changing, sparkplug groups those functionalities into "modes".

Modes serve as IDs for presets, so only the relevant presets are applied when a mode changes state.

Modes are defined in your config. Sparkplug does not come with a default set of modes, but you can use the following as an example:

```c++
enum ModeIDs
{
    DaytimeRunning,
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
