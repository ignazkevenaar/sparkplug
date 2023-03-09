#pragma once

AW9523Driver interiorDriver(0x59, 0, 16);

WireDevice *wireDevices[] = {
    &interiorDriver
};
size_t wireDevicesCount = COUNT_OF(wireDevices);

OutputDevice *outputDevices[] = {
    &interiorDriver
};
size_t outputDevicesCount = COUNT_OF(outputDevices);
