#include "lp55231driver.h"
#include "../helpers/wirehelper.h"

LP55231Driver::LP55231Driver(uint8_t address_, uint16_t channelFrom_, uint16_t channelCount_) : Lp55231(address_)
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

void LP55231Driver::setup()
{
    Begin();
    Enable();

    // Enable internal clock & set charge pump to auto & write auto increment.
    const uint8_t EN_AUTO_INCR = 0b01000000;

    const uint8_t CP_MODE_OFF = 0b00000000;
    const uint8_t CP_MODE_BYPASS = 0b00001000;
    const uint8_t CP_MODE_BOOST = 0b00010000;
    const uint8_t CP_MODE_AUTO = 0b00011000;

    const uint8_t CLK_DET_EN = 0b00000010;
    const uint8_t INT_CLK_EN = 0b00000001;

    WriteReg(REG_MISC, EN_AUTO_INCR | CP_MODE_BYPASS | CLK_DET_EN | INT_CLK_EN);

    for (int i = 0; i < outputCount; i++)
    {
        SetLogBrightness(i, true);
        SetChannelPWM(i, 0);
    }
};

void LP55231Driver::output()
{
    for (int i = 0; i < channelCount; i++)
    {
        if (!channels[channelFrom + i].wasUpdated) continue;

        uint8_t value = channels[channelFrom + i].value >> 8;
        SetChannelPWM(i, value);
    }
}
