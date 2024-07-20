#pragma once

#include "presetmodes.h"
#include "swopmodes.h"

struct Preset
{
    int modeID;
    PresetModes mode = PresetModes::Normal;
    SwopModes priorityMode = SwopModes::LTP;
    uint8_t intensity = 255;
    uint16_t fadeSpeedRising = 100;
    uint16_t fadeSpeedFalling = 200;
    int16_t blinkInterval = 600;
    uint32_t blinkPattern = 0b11111111111111110000000000000000;
    int16_t blinkCount = -1; // Infinite
};
