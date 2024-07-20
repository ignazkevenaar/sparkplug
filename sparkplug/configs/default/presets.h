#pragma once

enum ModeIDs
{
  DaytimeRunning,
  Parking,
  LowBeams,
  HighBeams,
  FlashToPass,
  Brake,
  Reverse,
  BlinkL,
  BlinkR,
  Hazards,
  FogRear,
  FogFront
};
const size_t modesCount = FogFront + 1;
LightingMode modes[modesCount];

const PROGMEM Preset presetsHeadlights[] = {
    {.modeID = LowBeams, .intensity = 128},
};

const PROGMEM Preset presetsHighBeams[] = {
    {.modeID = Parking, .intensity = 4},
    {.modeID = HighBeams},
    {.modeID = FlashToPass},
};

const PROGMEM Preset presetsBlinkersFrontLeft[] = {
    {.modeID = Parking, .intensity = 4},
    {.modeID = BlinkL, .mode = PresetModes::Blink},
    {.modeID = Hazards, .mode = PresetModes::Blink},
};

const PROGMEM Preset presetsBlinkersFrontRight[] = {
    {.modeID = Parking, .intensity = 4},
    {.modeID = BlinkR, .mode = PresetModes::Blink},
    {.modeID = Hazards, .mode = PresetModes::Blink},
};

const PROGMEM Preset presetsFogsFront[] = {
    {.modeID = FogFront, .intensity = 128},
    {.modeID = HighBeams, .intensity = 0},
    {.modeID = FlashToPass, .intensity = 0},
};

const PROGMEM Preset presetsTaillights[] = {
    {.modeID = Parking, .intensity = 1},
    {.modeID = Brake},
};

const PROGMEM Preset presetsBrake[] = {
    {.modeID = Brake},
};

const PROGMEM Preset presetsBlinkerRearLeft[] = {
    {.modeID = BlinkL, .mode = PresetModes::Blink},
    {.modeID = Hazards, .mode = PresetModes::Blink},
};

const PROGMEM Preset presetsBlinkerRearRight[] = {
    {.modeID = BlinkR, .mode = PresetModes::Blink},
    {.modeID = Hazards, .mode = PresetModes::Blink},
};

const PROGMEM Preset presetsFogRear[] = {
    {.modeID = FogRear},
};

const PROGMEM Preset presetsReverse[] = {
    {.modeID = Reverse},
};

Channel channels[] = {
    {COUNT_OF(presetsHeadlights), presetsHeadlights},
    {COUNT_OF(presetsBlinkersFrontRight), presetsBlinkersFrontRight},
    {COUNT_OF(presetsHighBeams), presetsHighBeams},
    {COUNT_OF(presetsFogsFront), presetsFogsFront},

    {COUNT_OF(presetsHeadlights), presetsHeadlights},
    {COUNT_OF(presetsBlinkersFrontLeft), presetsBlinkersFrontLeft},
    {COUNT_OF(presetsHighBeams), presetsHighBeams},
    {COUNT_OF(presetsFogsFront), presetsFogsFront},

    {COUNT_OF(presetsTaillights), presetsTaillights},
    {COUNT_OF(presetsBrake), presetsBrake},
    {COUNT_OF(presetsBlinkerRearLeft), presetsBlinkerRearLeft},
    {COUNT_OF(presetsFogRear), presetsFogRear},

    {COUNT_OF(presetsTaillights), presetsTaillights},
    {COUNT_OF(presetsBrake), presetsBrake},
    {COUNT_OF(presetsBlinkerRearRight), presetsBlinkerRearRight},
    {COUNT_OF(presetsReverse), presetsReverse},
};
const size_t channelsCount = COUNT_OF(channels);
