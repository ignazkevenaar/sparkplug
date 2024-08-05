#pragma once

#include <LPD8806.h>

#include "../timingfunctions.h"
#include "../types/OutputDevice.h"
#include "../types/channel.h"
#include "../types/preset.h"

extern Channel channels[];

class LPD8806Driver : public LPD8806, public OutputDevice
{
  public:
    LPD8806Driver(uint8_t dataPin, uint8_t clockPin, uint16_t channelFrom_ = 0, uint16_t channelCount_ = 0);
    void setup();
    void output();

  private:
    const static int outputCount = 6;
};
