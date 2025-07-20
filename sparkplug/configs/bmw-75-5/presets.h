#pragma once

#include "../../src/helpers/macros.h"
#include "../../src/types/channel.h"
#include "../../src/types/lightingmode.h"
#include "../../src/types/preset.h"

enum ModeIDs
{
    Parking,
    LowBeams,
    HighBeams,
    FlashToPass,
    Brake,
    BlinkL,
    BlinkR,
    Hazards,
    Neutral
};
const size_t modesCount = Hazards + 1;
LightingMode modes[modesCount];

const PROGMEM Preset presetParking[] = {
    {.modeID = Parking, .intensity = 16},
};

const PROGMEM Preset presetsHeadlights[] = {
    {.modeID = LowBeams},
    {.modeID = HighBeams, .intensity = 0},
    {.modeID = FlashToPass, .intensity = 0}
};

const PROGMEM Preset presetsHighBeams[] = {
    {.modeID = HighBeams},
    {.modeID = FlashToPass}
};

const PROGMEM Preset presetsBlinkersLeft[] = {
    {.modeID = BlinkL, .mode = PresetModes::Blink},
    {.modeID = Hazards, .mode = PresetModes::Blink}
};

const PROGMEM Preset presetsBlinkersRight[] = {
    {.modeID = BlinkR, .mode = PresetModes::Blink},
    {.modeID = Hazards, .mode = PresetModes::Blink}
};

const PROGMEM Preset presetsTaillights[] = {
    {.modeID = Parking, .intensity = 64},
    {.modeID = Brake}
};

const PROGMEM Preset instruments[] = {
    {.modeID = Parking, .intensity = 64},
};

const PROGMEM Preset indicatorBlue[] = {
    {.modeID = HighBeams, .intensity = 64}
};

const PROGMEM Preset indicatorRed[] = {
    {.modeID = Parking, .intensity = 64},
    {.modeID = LowBeams, .intensity = 0},
};

const PROGMEM Preset indicatorGreen[] = {
    {.modeID = Neutral, .intensity = 64},
};

const PROGMEM Preset indicatorOrange[] = {
    {.modeID = Parking, .intensity = 64},
    {.modeID = LowBeams, .intensity = 0},
};

const PROGMEM Preset presetsTattleTale[] = {
    {.modeID = BlinkL, .mode = PresetModes::Blink},
    {.modeID = BlinkR, .mode = PresetModes::Blink},
    {.modeID = Hazards, .mode = PresetModes::Blink}
};

const PROGMEM Preset DUMMY[] = {};

Channel channels[] = {
    {COUNT_OF(presetParking), presetParking},
    {COUNT_OF(presetsHeadlights), presetsHeadlights},
    {COUNT_OF(presetsHighBeams), presetsHighBeams},
    {COUNT_OF(instruments), instruments},

    {COUNT_OF(indicatorBlue), indicatorBlue},
    {COUNT_OF(indicatorRed), indicatorRed},
    {COUNT_OF(indicatorGreen), indicatorGreen},
    {COUNT_OF(indicatorOrange), indicatorOrange},

    {COUNT_OF(presetsTattleTale), presetsTattleTale},
    {COUNT_OF(presetsBlinkersLeft), presetsBlinkersLeft},
    {COUNT_OF(presetsBlinkersRight), presetsBlinkersRight},
    {COUNT_OF(presetsBlinkersLeft), presetsBlinkersLeft},

    {COUNT_OF(presetsBlinkersRight), presetsBlinkersRight},
    {COUNT_OF(presetsTaillights), presetsTaillights},
};
const size_t channelsCount = COUNT_OF(channels);
