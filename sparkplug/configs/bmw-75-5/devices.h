#pragma once

#include "../../src/drivers/pca9685.h"
#include "../../src/drivers/sn3218driver.h"
#include "../../src/helpers/macros.h"

SN3218Driver mainOutputDevice(0, 14);

WireDevice *wireDevices[] = {
    &mainOutputDevice,
};
size_t wireDevicesCount = COUNT_OF(wireDevices);

OutputDevice *outputDevices[] = {
    &mainOutputDevice,
};
size_t outputDevicesCount = COUNT_OF(outputDevices);
