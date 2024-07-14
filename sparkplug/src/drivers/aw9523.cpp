#include "aw9523.h"
#include "../helpers/wirehelper.h"

AW9523Driver::AW9523Driver(uint8_t address_, uint16_t channelFrom_, uint16_t channelCount_) : Adafruit_AW9523()
{
  address = address_;
  channelFrom = channelFrom_;
  channelCount = channelCount_;

  if (channelCount > outputCount)
  {
    Serial.println("Too many channels!");
    channelCount = outputCount;
    return;
  }
};

// Blocked by https://github.com/adafruit/Adafruit_AW9523/pull/5/
bool AW9523Driver::configureLEDCurrent(uint8_t quarters_to_reduce)
{
  Adafruit_I2CRegister gcrreg =
      Adafruit_I2CRegister(i2c_dev, AW9523_REG_GCR, 1);

  Adafruit_I2CRegisterBits ISEL =
      Adafruit_I2CRegisterBits(&gcrreg, 2, 0); // # bits, bit_shift

  return ISEL.write(quarters_to_reduce);
}

void AW9523Driver::setup()
{
    begin(address);

    for (int i = 0; i < channelCount; i++)
    {
      Serial.print("in: ");
      Serial.print(i);
      Serial.print(" out: ");
      Serial.println(pinTable[i]);

      pinMode(pinTable[i], AW9523_LED_MODE);
    }

    configureLEDCurrent(AW9523_IMAX_9MA);
};

void AW9523Driver::output()
{
  for (int i = 0; i < channelCount; i++)
  {
    if (!channels[channelFrom + i].wasUpdated) continue;

    uint8_t value = useTimingFunction(Exponential, channels[channelFrom + i].value) >> 8;
    analogWrite(pinTable[i], value);
  }
}
