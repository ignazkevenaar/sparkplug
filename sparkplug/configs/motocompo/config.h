#pragma once

#include "../../src/spark.h"

#include "devices.h"
#include "presets.h"

// WiFI settings
const char *ssid = "Sparkplug - Motocompo";
const char *password = "thereisnospoon";

bool onInitialize()
{
    mainOutputDevice.setup();

    setLightMode(LowBeams, 255);
    setLightMode(BlinkL, 255);

    return true;
}
