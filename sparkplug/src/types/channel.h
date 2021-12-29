#pragma once

#include "preset.h"

struct Channel
{
  int presetCount = 0;
  const Preset *presets = NULL;

  // Fade.
  uint16_t transitionFrom = 0;
  uint16_t transitionTo = 0;
  uint16_t value = 0;
  int16_t activePresetIndex = -1;
  int16_t previousPresetIndex = -1;

  // Blink.
  uint32_t timerBlink = 0;
  int8_t blinkPhase = 0;
  int8_t blinkCount = -1;
  int8_t blinkPresetIndex = -1;

  bool wasUpdated = false;

  int timingFunction = 0;
};
