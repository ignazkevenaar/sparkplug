#pragma once

#include <Adafruit_PWMServoDriver.h>

#include "../../timingfunctions.h"
#include "../OutputDevice.h"
#include "../WireDevice.h"
#include "../channel.h"
#include "../preset.h"

extern Channel channels[];

class PCA9685 : public Adafruit_PWMServoDriver, public WireDevice, public OutputDevice
{
public:
  PCA9685(uint8_t address_ = 0x00, uint16_t channelFrom_ = 0, uint16_t channelCount_ = 0, bool totemPoleOutput_ = false);
  void setup();
  void output();

private:
  void writeSequentially(uint16_t values[], bool invert, int rangeFrom, int rangeTo);
  void getOnOff(uint16_t value, uint16_t &valueOn, uint16_t &valueOff, bool invert = false);

  bool totemPoleOutput;
  const static int outputCount = 16;
};
