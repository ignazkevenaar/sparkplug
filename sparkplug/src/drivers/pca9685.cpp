#include "../helpers/wirehelper.h"
#include "pca9685driver.h"

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
    bool lastChannelUpdated = false;

    for (int i = 0; i <= channelCount; i++)
    {
        if (channels[channelFrom + i].wasUpdated)
        {
            if (!lastChannelUpdated)
            {
                Wire.beginTransmission(address);
                Wire.write(PCA9685_LED0_ON_L + 4 * i);
            }

            writeChannel(useTimingFunction(Exponential, channels[channelFrom + i].value) >> 4);
            lastChannelUpdated = true;
        }
        else
        {
            if (lastChannelUpdated) Wire.endTransmission();
            lastChannelUpdated = false;
        }
    }
    if (lastChannelUpdated) Wire.endTransmission();
};

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

void PCA9685Driver::writeChannel(uint16_t value)
{
    uint16_t valueOn = 0;
    uint16_t valueOff = 0;
    getOnOff(value, valueOn, valueOff, true);

    Wire.write(valueOn);
    Wire.write(valueOn >> 8);
    Wire.write(valueOff);
    Wire.write(valueOff >> 8);
}

const char *PCA9685Driver::getName()
{
    return "PCA9685";
}
