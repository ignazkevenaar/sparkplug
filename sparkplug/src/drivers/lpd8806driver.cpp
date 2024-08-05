#include "lpd8806driver.h"

LPD8806Driver::LPD8806Driver(uint8_t dataPin, uint8_t clockPin, uint16_t channelFrom_, uint16_t channelCount_) : LPD8806(2, dataPin, clockPin)
{
    channelFrom = channelFrom_;
    channelCount = channelCount_;

    if (channelCount > outputCount)
    {
        Serial.println("Too many channels!");
        channelCount = outputCount;
        return;
    }
};

void LPD8806Driver::setup()
{
    begin();

    setPixelColor(0, 0, 0, 0);
    setPixelColor(1, 0, 0, 0);
};

void LPD8806Driver::output()
{
    uint8_t values[channelCount] = {};

    for (int i = 0; i < channelCount; i++)
    {
        values[i] = (channels[channelFrom + i].value >> 9) & 0xff; // useTimingFunction(Exponential, channels[channelFrom + i].value) >> 9;
    }

    setPixelColor(0, values[0], values[1], values[2]);
    setPixelColor(1, values[3], values[4], values[5]);
    show();
};
