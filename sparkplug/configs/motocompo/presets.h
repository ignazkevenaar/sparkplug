#pragma once

#include "../../src/helpers/macros.h"
#include "../../src/types/channel.h"
#include "../../src/types/lightingmode.h"
#include "../../src/types/preset.h"

enum ModeIDs
{
    LowBeams,
    Brake,
    BlinkL,
    BlinkR,
    Hazards
};
const size_t modesCount = Hazards + 1;
LightingMode modes[modesCount];

const PROGMEM Preset presetsHeadlight[] = {
    {.modeID = LowBeams}
};

const PROGMEM Preset presetsBrake[] = {
    {.modeID = LowBeams, .intensity = 32},
    {.modeID = Brake},
};

const PROGMEM Preset presetsBlinkersLeft[] = {
    {.modeID = BlinkL, .mode = PresetModes::Blink},
    {.modeID = Hazards, .mode = PresetModes::Blink}
};

const PROGMEM Preset presetsBlinkersRight[] = {
    {.modeID = BlinkR, .mode = PresetModes::Blink},
    {.modeID = Hazards, .mode = PresetModes::Blink}
};

Channel channels[] = {
    {COUNT_OF(presetsBrake), presetsBrake},
    {COUNT_OF(presetsHeadlight), presetsHeadlight},
    {COUNT_OF(presetsBlinkersLeft), presetsBlinkersLeft},
    {COUNT_OF(presetsBlinkersRight), presetsBlinkersRight},
    {COUNT_OF(presetsBlinkersRight), presetsBlinkersRight},
    {COUNT_OF(presetsBlinkersLeft), presetsBlinkersLeft},
};
const size_t channelsCount = COUNT_OF(channels);
