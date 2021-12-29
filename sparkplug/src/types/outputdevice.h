#pragma once

#include "device.h"

struct OutputDevice : Device
{
  uint16_t channelFrom;
  uint16_t channelCount;
  virtual void output() = 0;
  virtual int getMaxChannelCount() = 0;
};
