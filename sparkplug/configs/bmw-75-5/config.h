#pragma once

#include "../../src/spark.h"

#include "devices.h"
#include "presets.h"

// WiFI settings
const char *ssid = "Sparkplug - BMW R75/5";
const char *password = "thereisnospoon";

bool onInitialize()
{
    return true;
}

bool onLightingModeChanged(int modeID)
{
    return true; // Allow mode change to apply.
}

bool onDeviceConnectionChanged(WireDevice &device)
{
    Serial.print("Device ");
    if (!device.connected) Serial.print("dis");
    Serial.print("connected at ");
    Serial.print("0x");
    Serial.println(device.address, HEX);

    return true; // Recalculate lights on device connection change.
}
