#pragma once

#include <Adafruit_AW9523.h>

#include "../timingfunctions.h"
#include "../types/OutputDevice.h"
#include "../types/WireDevice.h"
#include "../types/channel.h"
#include "../types/preset.h"

extern Channel channels[];

class AW9523Driver : public Adafruit_AW9523, public WireDevice, public OutputDevice
{
  public:
    AW9523Driver(uint8_t address_ = 0x59, uint16_t channelFrom_ = 0, uint16_t channelCount_ = 0);
    bool configureLEDCurrent(uint8_t quarters_to_reduce);
    void setup();
    void output();
    const char *getName();

  private:
    // Adafruit uses logical port pin order for their
    // Sparkplug SL-40 boards go by physical pin order around IC.

    const uint8_t pinTable[16] = {
        /*  0   0_0 */ 8,
        /*  1   0_1 */ 9,
        /*  2   0_2 */ 10,
        /*  3   0_3 */ 11,
        /*  4   0_4 */ 0,
        /*  5   0_5 */ 1,
        /*  6   0_6 */ 2,
        /*  7   0_7 */ 3,
        /*  8   1_0 */ 4,
        /*  9   1_1 */ 5,
        /* 10   1_2 */ 6,
        /* 11   1_3 */ 7,
        /* 12   1_4 */ 12,
        /* 13   1_5 */ 13,
        /* 14   1_6 */ 14,
        /* 15   1_7 */ 15,
    };

    const static int outputCount = 16;

    enum AW9523_CURRENT
    {
        AW9523_IMAX_36MA,
        AW9523_IMAX_28MA,
        AW9523_IMAX_18MA,
        AW9523_IMAX_9MA,
    };
};
