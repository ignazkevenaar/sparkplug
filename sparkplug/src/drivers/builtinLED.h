#pragma once

#include <Arduino.h>

#include "../types/outputdevice.h"
#include "../types/channel.h"
#include "../types/preset.h"

// extern const size_t channelsCount;
extern Channel channels[];

class builtinLED : OutputDevice
{
public:
  builtinLED(int channelFrom_ = 0);
  void setup();
  void output();

private:
  const static int outputCount = 1;
};
