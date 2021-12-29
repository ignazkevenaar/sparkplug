#pragma once

#include "../OutputDevice.h"
#include "../channel.h"
#include "../preset.h"

// extern const size_t channelsCount;
extern Channel channels[];

struct builtinLED : OutputDevice
{
  builtinLED(int channelFrom_ = 0)
  {
    channelFrom = channelFrom_;
  };

  void setup()
  {
    Serial.println("Setting up builtin LED.");
    pinMode(LED_BUILTIN, OUTPUT);
  };

  void output()
  {
    analogWrite(LED_BUILTIN, channels[channelFrom].value >> 4);
  };

  int getMaxChannelCount()
  {
    return 1;
  };
};
