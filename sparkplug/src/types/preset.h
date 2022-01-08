#pragma once

#include "presetmodes.h"
#include "swopmodes.h"

struct Preset
{
  int modeID;
  PresetModes mode = PresetModes::Normal;
  SwopModes priorityMode = SwopModes::LTP;
  uint16_t intensity = 0xFFFF;
  uint16_t fadeSpeedRising = 500;
  uint16_t fadeSpeedFalling = 1000;
  int16_t timeOff = 300;
  int16_t timeOn = 300;
};
