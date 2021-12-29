#pragma once

enum ModeIDs
{
  DRL,
  Parking,
  LowBeams,
  HighBeams,
  Banana,
  AnotherOne,
  FogRear,
  FogFront,
  Wowzer,
  Brake,
  ESS,
  Interior,
  Reverse,
  BlinkL,
  BlinkR,
  Hazards,
};

const size_t modesCount = Hazards + 1; // Last element of enum + 1.
LightingMode modes[modesCount];

const PROGMEM Preset presetsMainBeams[] =
    {
        {LowBeams, PresetModes::Normal, SwopModes::LTP, 0x1111, 100, 100},
        {HighBeams, PresetModes::Normal, SwopModes::LTP, 0x7777, 200, 200},
        {BlinkL, PresetModes::Normal, SwopModes::LTP, 0, 200, 200},
        {BlinkL, PresetModes::Blink, SwopModes::LTP, 0xFFFF, 200, 200, 600, 200},
};

const PROGMEM Preset presetBlinkerFirst[] = {{BlinkR, PresetModes::Blink, SwopModes::LTP, 0xFFFF, 1000, 2000, 200, 1000}};
const PROGMEM Preset presetBlinkerSecond[] = {{BlinkR, PresetModes::Blink, SwopModes::LTP, 0xFFFF, 1000, 2000, 400, 800}};
const PROGMEM Preset presetBlinkerThird[] = {{BlinkR, PresetModes::Blink, SwopModes::LTP, 0xFFFF, 1000, 2000, 600, 600}};

Channel channels[] =
    {
        {COUNT_OF(presetsMainBeams), presetsMainBeams},
        {COUNT_OF(presetBlinkerFirst), presetBlinkerFirst},
        {COUNT_OF(presetBlinkerSecond), presetBlinkerSecond},
        {COUNT_OF(presetBlinkerThird), presetBlinkerThird},
};
const size_t channelsCount = COUNT_OF(channels);
