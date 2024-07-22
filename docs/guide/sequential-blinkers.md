# Sequential Blinkers

When you define multiple channels with blink presets that have the same `blinkInterval`, you can easily configure those channels as sequential by setting different blinking patterns.

Example:
```c++{6,15,24}
const PROGMEM Preset presetBlinkerFirst[] =
{
    {
        .modeID = BlinkL,
        .mode = PresetModes::Blink,
        .blinkPattern = 0b11111111111111111100000000000000
    }
};

const PROGMEM Preset presetBlinkerSecond[] =
{
    {
        .modeID = BlinkL,
        .mode = PresetModes::Blink,
        .blinkPattern = 0b00000011111111111100000000000000
    }
};

const PROGMEM Preset presetBlinkerThird[] =
{
    {
        .modeID = BlinkL,
        .mode = PresetModes::Blink,
        .blinkPattern = 0b00000000000011111100000000000000
    }
};

Channel channels[] =
{
    { COUNT_OF(presetBlinkerFirst), presetBlinkerFirst },
    { COUNT_OF(presetBlinkerSecond), presetBlinkerSecond },
    { COUNT_OF(presetBlinkerThird), presetBlinkerThird },
};
const size_t channelsCount = COUNT_OF(channels);
```
