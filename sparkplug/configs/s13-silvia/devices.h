#pragma once

#include "../../src/drivers/lp55231.h"
#include "../../src/drivers/sn3218driver.h"
#include "../../src/helpers/macros.h"

LP55231Driver outputInterior(0x33, 0, 4);
SN3218Driver outputHigh(4, 17);
LP55231Driver outputLow(0x32, 21, 9);

WireDevice *wireDevices[] = {
    &outputInterior,
    &outputLow,
    &outputHigh,
};
size_t wireDevicesCount = COUNT_OF(wireDevices);

OutputDevice *outputDevices[] = {
    &outputInterior,
    &outputLow,
    &outputHigh,
};
size_t outputDevicesCount = COUNT_OF(outputDevices);
