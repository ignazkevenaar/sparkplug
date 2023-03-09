#pragma once

enum ModeIDs
{
  /*  0 */ Parking,
  /*  1 */ LowBeams,
  /*  2 */ HighBeams,
  /*  3 */ FogRear,
  /*  4 */ FogFront,
  /*  5 */ Brake,
  /*  6 */ Interior,
  /*  7 */ Reverse,
  /*  8 */ BlinkL,
  /*  9 */ BlinkR,
  /* 10 */ Hazards,
};

const size_t modesCount = Hazards + 1; // Last element of enum + 1.
LightingMode modes[modesCount];

const PROGMEM Preset presetsHeadlights[] =
    {
        {.modeID = LowBeams, .intensity = 0x7777},
};

const PROGMEM Preset presetsHighBeams[] =
    {
        {.modeID = Parking },
        {.modeID = HighBeams},
};

const PROGMEM Preset presetsBlinkersFrontLeft[] =
    {
        {.modeID = BlinkL, .mode = PresetModes::Blink},
        {.modeID = Hazards, .mode = PresetModes::Blink},
};

const PROGMEM Preset presetsBlinkersFrontRight[] =
    {
        {.modeID = BlinkR, .mode = PresetModes::Blink},
        {.modeID = Hazards, .mode = PresetModes::Blink},
};

const PROGMEM Preset presetsFogsFront[] =
    {
        {.modeID = FogFront},
        {.modeID = HighBeams, .intensity = 0},
};

const PROGMEM Preset presetsTaillights[] =
    {
        {.modeID = Parking, .intensity = 0x7777},
        {.modeID = Brake},
};

const PROGMEM Preset presetsBrake[] =
    {
        {.modeID = Brake},
};

const PROGMEM Preset presetsBlinkerRearLeft[] =
    {
        {.modeID = BlinkL, .mode = PresetModes::Blink},
        {.modeID = Hazards, .mode = PresetModes::Blink},
};

const PROGMEM Preset presetsBlinkerRearRight[] =
    {
        {.modeID = BlinkR, .mode = PresetModes::Blink},
        {.modeID = Hazards, .mode = PresetModes::Blink},
};

const PROGMEM Preset presetsFogRear[] =
    {
        {.modeID = FogRear},
};

const PROGMEM Preset presetsReverse[] =
    {
        {.modeID = Reverse},
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

        // // Interior
        // {COUNT_OF(presetsBlinkersFrontRight), presetsBlinkersFrontRight},
        // {COUNT_OF(presetsBlinkersFrontRight), presetsBlinkersFrontRight},
        // {COUNT_OF(presetsBlinkersFrontRight), presetsBlinkersFrontRight},

        // {COUNT_OF(presetsBlinkersFrontRight), presetsBlinkersFrontRight},
        // {COUNT_OF(presetsBlinkersFrontRight), presetsBlinkersFrontRight},
        // {COUNT_OF(presetsBlinkersFrontRight), presetsBlinkersFrontRight},

        // {COUNT_OF(presetsBlinkersFrontRight), presetsBlinkersFrontRight},
        // {COUNT_OF(presetsBlinkersFrontRight), presetsBlinkersFrontRight},
        // {COUNT_OF(presetsBlinkersFrontRight), presetsBlinkersFrontRight}
};
const size_t channelsCount = COUNT_OF(channels);
