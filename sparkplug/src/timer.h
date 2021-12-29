#pragma once

#include <Arduino.h>

struct Timer
{
  Timer(uint32_t interval_) : interval{interval_} {}

  bool elapsed(uint32_t currentMillis)
  {
    bool elapsed = currentMillis - previousMillis >= interval;
    if (elapsed) previousMillis = (currentMillis - previousMillis - interval);
    return elapsed;
  }

  uint32_t previousMillis;
  uint32_t interval;
};
