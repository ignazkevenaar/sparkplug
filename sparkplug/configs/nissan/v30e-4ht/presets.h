#pragma once

enum ModeIDs
{
//   Parking,   // 0
//   LowBeams,  // 1
//   HighBeams, // 2
//   FogRear,   // 3
//   FogFront,  // 4
//   Brake,     // 5
//   Interior,  // 6
//   Mood,      // 7
//   Reverse,   // 8
//   BlinkL,    // 9
//   BlinkR,    // 10
//   Hazards,   // 11
//   Stereo,    // 12

  /*  0 */ DRL,
  /*  1 */ Parking,
  /*  2 */ LowBeams,
  /*  3 */ HighBeams,
  /*  4 */ FlashToPass,
  /*  5 */ FogRear,
  /*  6 */ FogFront,
  /*  7 */ Brake,
  /*  8 */ ESS,
  /*  9 */ Interior,
  /* 10 */ Reverse,
  /* 11 */ BlinkL,
  /* 12 */ BlinkR,
  /* 13 */ Hazards,
  /* 14 */ Exhaust,
  /* 15 */ ExhaustGlow,
};

const size_t modesCount = ExhaustGlow + 1; // Last element of enum + 1.
LightingMode modes[modesCount];

const PROGMEM Preset presetsHeadlights[] =
    {
        {.modeID = Parking, .intensity = 63},
        {.modeID = LowBeams, .intensity = 127},
        {.modeID = HighBeams, .intensity = 0},
};

const PROGMEM Preset presetsHighBeams[] =
    {
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

const PROGMEM Preset presetsPositionFront[] =
    {
        {.modeID = Parking, .intensity = 63},
};

const PROGMEM Preset presetsSideMarkerLeft[] =
    {
        {.modeID = Parking, .intensity = 63},
        {.modeID = BlinkL, .mode = PresetModes::Blink, .intensity = 0},
        {.modeID = Hazards, .mode = PresetModes::Blink, .intensity = 0},
};

const PROGMEM Preset presetsSideMarkerRight[] =
    {
        {.modeID = Parking, .intensity = 63},
        {.modeID = BlinkR, .mode = PresetModes::Blink, .intensity = 0},
        {.modeID = Hazards, .mode = PresetModes::Blink, .intensity = 0},
};

const PROGMEM Preset presetsTaillights[] =
    {
        {.modeID = Parking, .intensity = 63},
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

const PROGMEM Preset presetsReverse[] =
    {
        {.modeID = Reverse},
};

const PROGMEM Preset presetsInteriorDome[] =
    {
        {.modeID = Interior, .fadeSpeedFalling = 5000},
};

const PROGMEM Preset presetsInteriorMood[] =
    {
        {.modeID = Exhaust, .intensity = 127},
};

// Interior

const PROGMEM Preset presetsCluster[] =
    {
        {.modeID = Parking},
};

const PROGMEM Preset presetsInstruments[] =
    {
        {.modeID = Parking, .intensity = 0x7777},
};

const PROGMEM Preset presetsAC[] =
    {
        {.modeID = Parking, .intensity = 0x3333},
};

const PROGMEM Preset presetsStereo[] =
    {
        {.modeID = ExhaustGlow, .intensity = 0x3333},
};

const PROGMEM Preset presetsHoodEmblem[] =
    {
        {.modeID = Parking, .intensity = 1024},
};

const PROGMEM Preset dud[] = {};

Channel channels[] =
    {
        // First exerior.
        {COUNT_OF(presetsHeadlights), presetsHeadlights},
        {COUNT_OF(presetsBlinkersFrontRight), presetsBlinkersFrontRight},
        {COUNT_OF(presetsHighBeams), presetsHighBeams},
        {COUNT_OF(presetsPositionFront), presetsPositionFront},

        {COUNT_OF(presetsSideMarkerRight), presetsSideMarkerRight},
        {COUNT_OF(presetsSideMarkerRight), presetsSideMarkerRight},
        {COUNT_OF(dud), dud},
        {COUNT_OF(dud), dud},

        {COUNT_OF(presetsReverse), presetsReverse},
        {COUNT_OF(dud), dud},
        {COUNT_OF(presetsTaillights), presetsTaillights},
        {COUNT_OF(dud), dud},

        {COUNT_OF(presetsTaillights), presetsTaillights},
        {COUNT_OF(dud), dud},
        {COUNT_OF(presetsBlinkerRearRight), presetsBlinkerRearRight},
        {COUNT_OF(dud), dud},

        // Last exerior.
        {COUNT_OF(presetsInteriorDome), presetsInteriorDome},
        {COUNT_OF(presetsInteriorMood), presetsInteriorMood},
        {COUNT_OF(presetsSideMarkerLeft), presetsSideMarkerLeft},
        {COUNT_OF(presetsSideMarkerLeft), presetsSideMarkerLeft},

        {COUNT_OF(presetsHighBeams), presetsHighBeams},
        {COUNT_OF(presetsPositionFront), presetsPositionFront},
        {COUNT_OF(presetsHeadlights), presetsHeadlights},
        {COUNT_OF(presetsBlinkersFrontLeft), presetsBlinkersFrontLeft},

        {COUNT_OF(presetsBlinkerRearLeft), presetsBlinkerRearLeft},
        {COUNT_OF(dud), dud},
        {COUNT_OF(presetsTaillights), presetsTaillights},
        {COUNT_OF(dud), dud},

        {COUNT_OF(presetsTaillights), presetsTaillights},
        {COUNT_OF(dud), dud},
        {COUNT_OF(presetsReverse), presetsReverse},
        {COUNT_OF(dud), dud},

        // Interior.
        {COUNT_OF(dud), dud},
        {COUNT_OF(dud), dud},
        {COUNT_OF(presetsHoodEmblem), presetsHoodEmblem},
        {COUNT_OF(presetsCluster), presetsCluster},
        {COUNT_OF(presetsAC), presetsAC},
        {COUNT_OF(presetsInteriorDome), presetsInteriorDome},
        {COUNT_OF(presetsInstruments), presetsInstruments},
        {COUNT_OF(presetsInstruments), presetsInstruments},
        {COUNT_OF(presetsStereo), presetsStereo},
};
const size_t channelsCount = COUNT_OF(channels);
