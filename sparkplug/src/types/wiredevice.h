#pragma once

#include "device.h"

struct WireDevice : Device
{
    uint8_t bus;
    uint8_t address;
    bool connected;
    uint8_t errorState;
};
