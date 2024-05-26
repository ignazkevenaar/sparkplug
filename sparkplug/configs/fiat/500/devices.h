#pragma once

LP55231Driver exteriorDriverRear(0x32, 0, 9);
PCA9685 exteriorDriverFront(0x42, 9, 16);
PCA9685 interiorDriver(0x43, 25, 16);

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
