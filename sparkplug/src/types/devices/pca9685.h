#pragma once

#include <Adafruit_PWMServoDriver.h>

#include "../OutputDevice.h"
#include "../WireDevice.h"
#include "../channel.h"
#include "../preset.h"

#include "../../timingfunctions.h"

// extern const size_t channelsCount;
extern Channel channels[];

struct PCA9685 : WireDevice, OutputDevice
{
  PCA9685(uint8_t address_ = 0x00, uint16_t channelFrom_ = 0, uint16_t channelCount_ = 0, bool totemPoleOutput_ = false)
  {
    address = address_;
    channelFrom = channelFrom_;
    channelCount = channelCount_;
    totemPoleOutput = totemPoleOutput_;

    if (channelCount > getMaxChannelCount())
    {
      Serial.println("Too many channels!");
      channelCount = getMaxChannelCount();
      return;
    }
  };

  void setup()
  {
    Serial.println("Setting up pca device.");

    driver.begin();
    driver.setOscillatorFrequency(27000000);
    driver.setPWMFreq(1600);

    for (int i = 0; i < getMaxChannelCount(); i++)
      driver.setPin(i, 0, true);
  };

  void output()
  {
    for (int i = channelFrom; i < channelCount; i++)
    {
      uint16_t hmm = useTimingFunction(Linear, channels[i].value) >> 4;
      // hmm = 5;

      if (channels[i].wasUpdated) driver.setPin(i - channelFrom, hmm, true);
    }
  };

  int getMaxChannelCount()
  {
    return 16;
  };

  bool totemPoleOutput;
  Adafruit_PWMServoDriver driver;
};
