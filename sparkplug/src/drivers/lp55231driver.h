#pragma once

#include <lp55231.h>

#include "../timingfunctions.h"
#include "../types/OutputDevice.h"
#include "../types/WireDevice.h"
#include "../types/channel.h"
#include "../types/preset.h"

extern Channel channels[];

class LP55231Driver : public Lp55231, public WireDevice, public OutputDevice
{
  public:
    LP55231Driver(uint8_t address_ = 0x00, uint16_t channelFrom_ = 0, uint16_t channelCount_ = 0);
    void setup();
    void output();
    const char *getName();

  private:
    static const uint8_t REG_D1_PWM = 0x16;
    static const uint8_t REG_MISC = 0x36;

    const static int outputCount = 9;
};
