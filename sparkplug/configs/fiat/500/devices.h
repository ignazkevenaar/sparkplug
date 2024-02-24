#pragma once

PCA9685 exteriorDriverRear(0x40, 0, 16);
PCA9685 exteriorDriverFront(0x42, 16, 16);
PCA9685 interiorDriver(0x43, 32, 16);

WireDevice *wireDevices[] = {
    &exteriorDriverRear,
    &exteriorDriverFront,
    &interiorDriver,
};
size_t wireDevicesCount = COUNT_OF(wireDevices);

OutputDevice *outputDevices[] = {
    &exteriorDriverRear,
    &exteriorDriverFront,
    &interiorDriver,
};
size_t outputDevicesCount = COUNT_OF(outputDevices);
