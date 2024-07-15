#pragma once

builtinLED builtin(0);
PCA9685Driver dashboard(0x40, 0, 16);

WireDevice *wireDevices[] = {
    &dashboard};
size_t wireDevicesCount = COUNT_OF(wireDevices);

OutputDevice *outputDevices[] = {
    &dashboard,
    // &builtin,
};
size_t outputDevicesCount = COUNT_OF(outputDevices);
