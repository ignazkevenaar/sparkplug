#pragma once

#include "../../src/drivers/pca9685.h"
#include "../../src/helpers/macros.h"

PCA9685Driver mainOutputDevice(0x40, 0, 16);

WireDevice *wireDevices[] = {
    &mainOutputDevice,
};
size_t wireDevicesCount = COUNT_OF(wireDevices);

OutputDevice *outputDevices[] = {
    &mainOutputDevice
};
size_t outputDevicesCount = COUNT_OF(outputDevices);
