#pragma once

enum ModeIDs
{
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
  /* 14 */ Stereo,
  /* 15 */ LASTMODE,
};

const size_t modesCount = LASTMODE;
LightingMode modes[modesCount];

const PROGMEM Preset presetsHeadlights[] =
    {
        {.modeID = Parking, .intensity = 63},
        {.modeID = LowBeams, .intensity = 127},
        {.modeID = HighBeams, .intensity = 255},
        {.modeID = FlashToPass, .intensity = 255},
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
        {.modeID = DRL, .intensity = 128},
        {.modeID = Parking, .intensity = 63},
};

const PROGMEM Preset presetsTaillights[] =
    {
        {.modeID = Parking, .intensity = 63}
};

const PROGMEM Preset presetsBrakelights[] =
    {
        {.modeID = Brake}
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

const PROGMEM Preset presetsFogFront[] =
    {
        {.modeID = FogFront},
};

const PROGMEM Preset presetsReverse[] =
    {
        {.modeID = Reverse},
};

const PROGMEM Preset presetsInteriorDome[] =
    {
        {.modeID = Interior, .fadeSpeedFalling = 5000},
};

// Interior

const PROGMEM Preset presetsCluster[] =
    {
        {.modeID = DRL},
};

const PROGMEM Preset presetsInstruments[] =
    {
        {.modeID = Parking},
};

const PROGMEM Preset presetsStereo[] =
    {
        {.modeID = Stereo},
        {.modeID = Hazards, .mode = PresetModes::Blink}, // Temporary.
};

const PROGMEM Preset dud[] = {};

Channel channels[] =
    {
        // Rear exterior.
        {COUNT_OF(presetsTaillights), presetsTaillights},
        {COUNT_OF(presetsBrakelights), presetsBrakelights},
        {COUNT_OF(presetsBlinkersFrontLeft), presetsBlinkersFrontLeft},
        {COUNT_OF(presetsFogRear), presetsFogRear},

        {COUNT_OF(presetsBrakelights), presetsBrakelights}, // Center high mounted stop light.
        {COUNT_OF(presetsInteriorDome), presetsInteriorDome},
        {COUNT_OF(dud), dud},
        {COUNT_OF(dud), dud},

        {COUNT_OF(dud), dud},
        {COUNT_OF(dud), dud},
        {COUNT_OF(dud), dud},
        {COUNT_OF(dud), dud},

        {COUNT_OF(presetsReverse), presetsReverse},
        {COUNT_OF(presetsBlinkersFrontRight), presetsBlinkersFrontRight},
        {COUNT_OF(presetsBrakelights), presetsBrakelights},
        {COUNT_OF(presetsTaillights), presetsTaillights},

        // Front exerior.
        {COUNT_OF(presetsHeadlights), presetsHeadlights},
        {COUNT_OF(presetsPositionFront), presetsPositionFront},
        {COUNT_OF(presetsBlinkersFrontLeft), presetsBlinkersFrontLeft},
        {COUNT_OF(presetsFogFront), presetsFogFront},

        {COUNT_OF(presetsBlinkersFrontLeft), presetsBlinkersFrontLeft},
        {COUNT_OF(dud), dud},
        {COUNT_OF(dud), dud},
        {COUNT_OF(dud), dud},

        {COUNT_OF(dud), dud},
        {COUNT_OF(dud), dud},
        {COUNT_OF(dud), dud},
        {COUNT_OF(presetsBlinkersFrontRight), presetsBlinkersFrontRight},

        {COUNT_OF(presetsFogFront), presetsFogFront},
        {COUNT_OF(presetsBlinkersFrontRight), presetsBlinkersFrontRight},
        {COUNT_OF(presetsPositionFront), presetsPositionFront},
        {COUNT_OF(presetsHeadlights), presetsHeadlights},

        // Interior.
        {COUNT_OF(presetsInstruments), presetsInstruments},
        {COUNT_OF(presetsInstruments), presetsInstruments},
        {COUNT_OF(presetsCluster), presetsCluster},
        {COUNT_OF(presetsStereo), presetsStereo},

        {COUNT_OF(dud), dud},
        {COUNT_OF(dud), dud},
        {COUNT_OF(dud), dud},
        {COUNT_OF(dud), dud},

        {COUNT_OF(dud), dud},
        {COUNT_OF(dud), dud},
        {COUNT_OF(dud), dud},
        {COUNT_OF(dud), dud},

        {COUNT_OF(dud), dud},
        {COUNT_OF(dud), dud},
        {COUNT_OF(dud), dud},
        {COUNT_OF(dud), dud},
};
const size_t channelsCount = COUNT_OF(channels);
