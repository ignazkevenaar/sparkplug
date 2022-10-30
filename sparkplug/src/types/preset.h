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
  int16_t timeOff = 300;
  int16_t timeOn = 300;
};
