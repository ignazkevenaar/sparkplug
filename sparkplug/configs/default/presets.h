#pragma once

enum ModeIDs
{
  Parking,
  LowBeams,
  HighBeams,
  FogRear,
  FogFront,
  Brake,
  Interior,
  Reverse,
  BlinkL,
  BlinkR,
  Hazards,
};

const size_t modesCount = Hazards + 1; // Last element of enum + 1.
LightingMode modes[modesCount];

const PROGMEM Preset presetsHeadlights[] =
    {
        {.modeID = LowBeams, .intensity = 0x7777},

        {.modeID = Hazards, .mode = PresetModes::Blink},
};

const PROGMEM Preset presetsHighBeams[] =
    {
        {.modeID = Parking, .intensity = 16},
        {.modeID = HighBeams},

        {.modeID = Hazards, .mode = PresetModes::Blink},
};

const PROGMEM Preset presetsBlinkersRear[] =
    {
        {.modeID = BlinkL, .mode = PresetModes::Blink},
        {.modeID = BlinkR, .mode = PresetModes::Blink},
        {.modeID = Hazards, .mode = PresetModes::Blink},
};

const PROGMEM Preset presetsBlinkersFrontLeft[] =
    {
        {.modeID = Parking, .intensity = 16},
        {.modeID = BlinkL, .mode = PresetModes::Blink},
        {.modeID = Hazards, .mode = PresetModes::Blink},
};

const PROGMEM Preset presetsBlinkersFrontRight[] =
    {
        {.modeID = Parking, .intensity = 16},
        {.modeID = BlinkR, .mode = PresetModes::Blink},
        {.modeID = Hazards, .mode = PresetModes::Blink},
};

const PROGMEM Preset presetsFogsFront[] =
    {
        {.modeID = FogFront, .intensity = 0x7777},
        {.modeID = HighBeams, .intensity = 0},

        {.modeID = Hazards, .mode = PresetModes::Blink},
};

const PROGMEM Preset presetsTaillights[] =
    {
        {.modeID = Parking, .intensity = 0x1111},
        {.modeID = Brake},

        {.modeID = Hazards, .mode = PresetModes::Blink},
};

const PROGMEM Preset presetsBrake[] =
    {
        {.modeID = Brake},

        {.modeID = Hazards, .mode = PresetModes::Blink},
};

const PROGMEM Preset presetsBlinkerRearLeft[] =
    {
        {.modeID = BlinkL, .mode = PresetModes::Blink},
        {.modeID = Hazards, .mode = PresetModes::Blink},

        {.modeID = Hazards, .mode = PresetModes::Blink},
};

const PROGMEM Preset presetsBlinkerRearRight[] =
    {
        {.modeID = BlinkR, .mode = PresetModes::Blink},
        {.modeID = Hazards, .mode = PresetModes::Blink},

        {.modeID = Hazards, .mode = PresetModes::Blink},
};

const PROGMEM Preset presetsFogRear[] =
    {
        {.modeID = FogRear},

        {.modeID = Hazards, .mode = PresetModes::Blink},
};

const PROGMEM Preset presetsReverse[] =
    {
        {.modeID = Reverse},

        {.modeID = Hazards, .mode = PresetModes::Blink},
};

Channel channels[] =
    {
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
