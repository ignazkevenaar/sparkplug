#include "pca9685.h"
#include "../helpers/wirehelper.h"

PCA9685Driver::PCA9685Driver(uint8_t address_, uint16_t channelFrom_, uint16_t channelCount_, bool totemPoleOutput_) : Adafruit_PWMServoDriver(address_)
{
  address = address_;
  channelFrom = channelFrom_;
  channelCount = channelCount_;
  totemPoleOutput = totemPoleOutput_;

  if (channelCount > outputCount)
  {
    Serial.println("Too many channels!");
    channelCount = outputCount;
    return;
  }
};

void PCA9685Driver::setup()
{
  begin();
  setPWMFreq(1600);
  setOutputMode(totemPoleOutput);

  for (int i = 0; i < outputCount; i++)
    setPin(i, 0, true);
};

void PCA9685Driver::output()
{
  if (channelCount == 1)
  {
    uint16_t value = useTimingFunction(Exponential, channels[channelFrom].value) >> 4;
    setPin(channelFrom, value, true);
    return;
  }

  uint16_t values[outputCount] = {}; // Buffer for values of changed channels.

  // Split updated channels into ranges.
  int length = 1;

  for (int i = 1; i <= channelCount; i++)
  {
    if (channels[channelFrom + i - 1].wasUpdated)
      values[i - 1] = useTimingFunction(Exponential, channels[channelFrom + i - 1].value) >> 4;

    if (i == channelCount || channels[channelFrom + i].wasUpdated != channels[channelFrom + i - 1].wasUpdated)
    {
      if (channels[channelFrom + i - 1].wasUpdated)
      {
        if (i - length == i - 1)
          setPin(i - length, values[i - length], true);
        else
          writeSequentially(values, true, i - length, i - 1);
      }

      length = 1;
      continue;
    }

    length++;
  }
};

void PCA9685Driver::writeSequentially(uint16_t values[], bool invert, int rangeFrom, int rangeTo)
{
  Wire.beginTransmission(address);
  Wire.write(PCA9685_LED0_ON_L + 4 * rangeFrom);

  // LED Addresses are auto incrementing.
  for (int i = rangeFrom; i <= rangeTo; i++)
  {
    uint16_t valueOn = 0;
    uint16_t valueOff = 0;
    getOnOff(values[i], valueOn, valueOff, true);

    Wire.write(valueOn);
    Wire.write(valueOn >> 8);
    Wire.write(valueOff);
    Wire.write(valueOff >> 8);
  }

  Wire.endTransmission();
}

void PCA9685Driver::getOnOff(uint16_t value, uint16_t &valueOn, uint16_t &valueOff, bool invert)
{
  // Clamp value between 0 and 4095 inclusive.
  uint16_t value_ = min(value, (uint16_t)4095);
  if (invert) value_ = 4095 - value_;

  if (value_ == 4095)
  {
    valueOn = 4096;
    valueOff = 0;
  }
  else if (value_ == 0)
  {
    valueOn = 0;
    valueOff = 4096;
  }
  else
  {
    valueOff = value_;
  }
}
