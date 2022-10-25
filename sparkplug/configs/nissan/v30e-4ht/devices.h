#pragma once

builtinLED builtin(0);
PCA9685 exteriorDriverFirst(0x40, 0, 16);
PCA9685 exteriorDriverLast(0x42, 16, 16);
LP55231Driver interiorDriver(0x32, 32, 9);

WireDevice *wireDevices[] = {
    &exteriorDriverFirst,
    &exteriorDriverLast,
    &interiorDriver
};
size_t wireDevicesCount = COUNT_OF(wireDevices);

OutputDevice *outputDevices[] = {
    &exteriorDriverFirst,
    &exteriorDriverLast,
    &interiorDriver
};
size_t outputDevicesCount = COUNT_OF(outputDevices);
