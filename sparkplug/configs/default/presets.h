#pragma once

#include "../../src/helpers/macros.h"
#include "../../src/types/channel.h"
#include "../../src/types/lightingmode.h"
#include "../../src/types/preset.h"

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

const char *modeNames[modesCount] = {
    "DaytimeRunning",
    "Parking",
    "LowBeams",
    "HighBeams",
    "FlashToPass",
    "Brake",
    "Reverse",
    "BlinkL",
    "BlinkR",
    "Hazards",
    "FogRear",
    "FogFront",
};

const PROGMEM Preset presetsHeadlights[] = {
    {.modeID = LowBeams, .intensity = 128}
};

const PROGMEM Preset presetsHighBeams[] = {
    {.modeID = Parking, .intensity = 4},
    {.modeID = HighBeams},
    {.modeID = FlashToPass}
};

const PROGMEM Preset presetsBlinkersFrontLeft[] = {
    {.modeID = Parking, .intensity = 4},
    {.modeID = BlinkL, .mode = PresetModes::Blink},
    {.modeID = Hazards, .mode = PresetModes::Blink}
};

const PROGMEM Preset presetsBlinkersFrontRight[] = {
    {.modeID = Parking, .intensity = 4},
    {.modeID = BlinkR, .mode = PresetModes::Blink},
    {.modeID = Hazards, .mode = PresetModes::Blink}
};

const PROGMEM Preset presetsFogsFront[] = {
    {.modeID = FogFront, .intensity = 128},
    {.modeID = HighBeams, .intensity = 0},
    {.modeID = FlashToPass, .intensity = 0}
};

const PROGMEM Preset presetsTaillights[] = {
    {.modeID = Parking, .intensity = 1},
    {.modeID = Brake}
};

const PROGMEM Preset presetsBrake[] = {
    {.modeID = Brake},
};

const PROGMEM Preset pUnused[] = {};

const PROGMEM Preset presetsFogRear[] = {
    {.modeID = FogRear}
};

const PROGMEM Preset presetsReverse[] = {
    {.modeID = Reverse}
};

/// SEQ BLINKERS

const PROGMEM Preset presetBlinkerFirstLeft[] = {
    {.modeID = Brake},
    {.modeID = BlinkL, .intensity = 0},
    {.modeID = Hazards, .intensity = 0},
    {.modeID = Parking, .priorityMode = SwopModes::HTP, .intensity = 32},
    {.modeID = BlinkL,
     .mode = PresetModes::Blink,
     .blinkPattern = 0b11111111111111111100000000000000},
    {.modeID = Hazards,
     .mode = PresetModes::Blink,
     .blinkPattern = 0b11111111111111111100000000000000}
};

const PROGMEM Preset presetBlinkerSecondLeft[] = {
    {.modeID = Brake},
    {.modeID = BlinkL, .intensity = 0},
    {.modeID = Hazards, .intensity = 0},
    {.modeID = Parking, .priorityMode = SwopModes::HTP, .intensity = 32},
    {.modeID = BlinkL,
     .mode = PresetModes::Blink,
     .blinkPattern = 0b00000011111111111100000000000000},
    {.modeID = Hazards,
     .mode = PresetModes::Blink,
     .blinkPattern = 0b00000011111111111100000000000000}
};

const PROGMEM Preset presetBlinkerThirdLeft[] = {
    {.modeID = Brake},
    {.modeID = BlinkL, .intensity = 0},
    {.modeID = Hazards, .intensity = 0},
    {.modeID = Parking, .priorityMode = SwopModes::HTP, .intensity = 32},
    {.modeID = BlinkL,
     .mode = PresetModes::Blink,
     .blinkPattern = 0b00000000000011111100000000000000},
    {.modeID = Hazards,
     .mode = PresetModes::Blink,
     .blinkPattern = 0b00000000000011111100000000000000}
};

const PROGMEM Preset presetBlinkerFirstRight[] = {
    {.modeID = Brake},
    {.modeID = BlinkR, .intensity = 0},
    {.modeID = Hazards, .intensity = 0},
    {.modeID = Parking, .priorityMode = SwopModes::HTP, .intensity = 32},
    {.modeID = BlinkR,
     .mode = PresetModes::Blink,
     .blinkPattern = 0b11111111111111111100000000000000},
    {.modeID = Hazards,
     .mode = PresetModes::Blink,
     .blinkPattern = 0b11111111111111111100000000000000}
};

const PROGMEM Preset presetBlinkerSecondRight[] = {
    {.modeID = Brake},
    {.modeID = BlinkR, .intensity = 0},
    {.modeID = Hazards, .intensity = 0},
    {.modeID = Parking, .priorityMode = SwopModes::HTP, .intensity = 32},
    {.modeID = BlinkR,
     .mode = PresetModes::Blink,
     .blinkPattern = 0b00000011111111111100000000000000},
    {.modeID = Hazards,
     .mode = PresetModes::Blink,
     .blinkPattern = 0b00000011111111111100000000000000}
};

const PROGMEM Preset presetBlinkerThirdRight[] = {
    {.modeID = Brake},
    {.modeID = BlinkR, .intensity = 0},
    {.modeID = Hazards, .intensity = 0},
    {.modeID = Parking, .priorityMode = SwopModes::HTP, .intensity = 32},
    {.modeID = BlinkR,
     .mode = PresetModes::Blink,
     .blinkPattern = 0b00000000000011111100000000000000},
    {.modeID = Hazards,
     .mode = PresetModes::Blink,
     .blinkPattern = 0b00000000000011111100000000000000}
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

    {COUNT_OF(presetBlinkerSecondLeft), presetBlinkerSecondLeft},
    {COUNT_OF(presetBlinkerThirdLeft), presetBlinkerThirdLeft},
    {COUNT_OF(pUnused), pUnused},
    {COUNT_OF(presetBlinkerFirstLeft), presetBlinkerFirstLeft},

    {COUNT_OF(presetBlinkerSecondRight), presetBlinkerSecondRight},
    {COUNT_OF(presetBlinkerThirdRight), presetBlinkerThirdRight},
    {COUNT_OF(pUnused), pUnused},
    {COUNT_OF(presetBlinkerFirstRight), presetBlinkerFirstRight}
};
const size_t channelsCount = COUNT_OF(channels);
