#include "builtinLED.h"

builtinLED::builtinLED(int channelFrom_)
{
    channelFrom = channelFrom_;
};

void builtinLED::setup()
{
    Serial.println("Setting up builtin LED.");
    pinMode(LED_BUILTIN, OUTPUT);
};

void builtinLED::output()
{
    analogWrite(LED_BUILTIN, channels[channelFrom].value >> 4);
};
