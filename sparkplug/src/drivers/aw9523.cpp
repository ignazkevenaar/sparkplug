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

void AW9523Driver::setup()
{
    Serial.println("Help!");

    begin(address);

    Serial.println(channelCount);

    for (int i = 0; i < channelCount; i++)
    {
      Serial.print("in: ");
      Serial.print(i);
      Serial.print(" out: ");
      Serial.println(pinTable[i]);

      pinMode(pinTable[i], AW9523_LED_MODE);
    }
};

void AW9523Driver::output()
{
  for (int i = 0; i < channelCount; i++)
  {
    if (!channels[channelFrom + i].wasUpdated) continue;

    uint8_t value = channels[channelFrom + i].value >> 8;
    analogWrite(pinTable[i], value);
  }
}
