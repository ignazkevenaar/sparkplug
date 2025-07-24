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
    FogFront,
    Interior
};
const size_t modesCount = Interior + 1;
LightingMode modes[modesCount];

const PROGMEM Preset pUnused[] = {};

const PROGMEM Preset presetsHeadlights[] = {
    {.modeID = LowBeams, .intensity = 128}
};

const PROGMEM Preset presetsHighBeams[] = {
    {.modeID = HighBeams},
    {.modeID = FlashToPass}
};

const PROGMEM Preset presetsBlinkersLeft[] = {
    {
        .modeID = BlinkL,
        .mode = PresetModes::Blink,
    },
    {
        .modeID = Hazards,
        .mode = PresetModes::Blink,
    }
};

const PROGMEM Preset presetsBlinkersRight[] = {
    {
        .modeID = BlinkR,
        .mode = PresetModes::Blink,
    },
    {
        .modeID = Hazards,
        .mode = PresetModes::Blink,
    }
};

const PROGMEM Preset presetsFogsFront[] = {
    {.modeID = FogFront}
};

const PROGMEM Preset presetsTaillights[] = {
    {.modeID = Parking, .intensity = 32},
    {.modeID = Brake}
};

const PROGMEM Preset presetsBrake[] = {
    {.modeID = Brake},
};

const PROGMEM Preset presetsReverse[] = {
    {.modeID = Reverse}
};

const PROGMEM Preset presetsPlate[] = {
    {.modeID = Parking, .intensity = 64}
};

const PROGMEM Preset presetsMarker[] = {
    {.modeID = Parking, .intensity = 8}
};

const PROGMEM Preset presetsDome[] = {
    {.modeID = Interior, .fadeSpeedRising = 500, .fadeSpeedFalling = 3000 }
};

// Interior

const PROGMEM Preset presetsInteriorButtons[] = {
    {.modeID = Parking, .intensity = 8}
};

const PROGMEM Preset presetsCluster[] = {
    {.modeID = Parking, .intensity = 128}
};

const PROGMEM Preset presetsSpeedometer[] = {
    {.modeID = DaytimeRunning, .intensity = 32, .fadeSpeedRising = 0, .fadeSpeedFalling = 0},
    {.modeID = Parking, .intensity = 8, .fadeSpeedRising = 0, .fadeSpeedFalling = 0}
};

const PROGMEM Preset presetsHUD[] = {
    {.modeID = DaytimeRunning, .intensity = 16, .fadeSpeedRising = 0, .fadeSpeedFalling = 0},
    {.modeID = Parking, .intensity = 4, .fadeSpeedRising = 0, .fadeSpeedFalling = 0}
};

Channel channels[] = {
    // LP55231 - Interior
    CHA(presetsInteriorButtons),
    CHA(presetsCluster),
    CHA(presetsSpeedometer),
    CHA(presetsHUD),

    // SN3218
    CHA(pUnused),
    CHA(pUnused),
    CHA(pUnused),
    CHA(presetsBlinkersLeft),
    CHA(presetsMarker),
    CHA(presetsBlinkersLeft),
    CHA(presetsHeadlights),
    CHA(presetsHighBeams),
    CHA(presetsFogsFront),
    CHA(presetsFogsFront),
    CHA(presetsHighBeams),
    CHA(presetsHeadlights),
    CHA(presetsBlinkersRight),
    CHA(presetsMarker),
    CHA(presetsBlinkersRight),
    CHA(presetsDome),
    CHA(presetsPlate),

    // LP55231
    CHA(presetsTaillights),
    CHA(presetsTaillights),
    CHA(presetsBlinkersLeft),
    CHA(presetsReverse),
    CHA(presetsBrake),
    CHA(presetsReverse),
    CHA(presetsBlinkersRight),
    CHA(presetsTaillights),
    CHA(presetsTaillights),
};
const size_t channelsCount = COUNT_OF(channels);
