#pragma once

#include <Arduino.h>

struct Timer
{
  Timer(uint32_t interval_) : interval(interval_) {}

  bool elapsed(uint32_t currentMillis)
  {
    if (currentMillis - previousMillis > interval)
    {
      previousMillis = currentMillis - (currentMillis - previousMillis - interval);
      return true;
    }
    return false;
  }

  uint32_t previousMillis = 0;
  uint32_t interval;
};
