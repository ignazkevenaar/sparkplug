#include "sn3218driver.h"
#include "../helpers/gamma8.h"
#include "../helpers/progmem_readanything.h"
#include "../helpers/wirehelper.h"

SN3218Driver::SN3218Driver(uint16_t channelFrom_, uint16_t channelCount_) : _sn3218()
{
    address = 0x54; // SN3218a has only one address.
    channelFrom = channelFrom_;
    channelCount = channelCount_;

    if (channelCount > outputCount)
    {
        Serial.println("Too many channels!");
        channelCount = outputCount;
        return;
    }
};

void SN3218Driver::setup()
{
    Serial.println("Setting up SN3218a.");
    begin();
    enable_leds(SN3218_CH_ALL);

    for (int i = 0; i < outputCount; i++)
        set(i, 0);

    sn3218.update();
};

void SN3218Driver::output()
{
    bool lastChannelUpdated = false;

    for (int i = 0; i <= channelCount; i++)
    {
        if (channels[channelFrom + i].wasUpdated)
        {
            if (!lastChannelUpdated)
            {
                Wire.beginTransmission(SN3218_ADDR);
                Wire.write(SN3218_CMD_SET_PWM_VALUES + i);
            }

            uint8_t value = channels[channelFrom + i].value >> 8;
            uint8_t logValue = PROGMEM_getAnything(&gamma8[value]);
            Wire.write(logValue);
            lastChannelUpdated = true;
        }
        else
        {
            if (lastChannelUpdated) Wire.endTransmission();
            lastChannelUpdated = false;
        }
    }
    if (lastChannelUpdated) Wire.endTransmission();

    sn3218.update();
};

const char *SN3218Driver::getName()
{
    return "SN3218";
}
