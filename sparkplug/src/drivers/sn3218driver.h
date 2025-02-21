#pragma once

#include "../lib/pimoroni_arduino_sn3218-master/sn3218.h"

#include "../timingfunctions.h"
#include "../types/OutputDevice.h"
#include "../types/WireDevice.h"
#include "../types/channel.h"
#include "../types/preset.h"

extern Channel channels[];

class SN3218Driver : public _sn3218, public WireDevice, public OutputDevice
{
  public:
    SN3218Driver(uint16_t channelFrom_ = 0, uint16_t channelCount_ = 0);
    void setup();
    void output();

  private:
    const static int outputCount = 18;
};
