#pragma once

#include "../../src/drivers/lpd8806driver.h"
#include "../../src/helpers/macros.h"

LPD8806Driver mainOutputDevice(14, 12, 0, 6);

WireDevice *wireDevices[] = {};
size_t wireDevicesCount = COUNT_OF(wireDevices);

OutputDevice *outputDevices[] = {
    &mainOutputDevice
};
size_t outputDevicesCount = COUNT_OF(outputDevices);
