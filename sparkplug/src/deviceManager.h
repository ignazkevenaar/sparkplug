#pragma once

#include <Arduino.h>

#include <Wire.h>

#include "types/OutputDevice.h"
#include "types/WireDevice.h"

// Device drivers.
#include "drivers/aw9523.h"
#include "drivers/builtinLED.h"
#include "drivers/lp55231.h"
#include "drivers/pca9685.h"

extern int wirePins[];
extern size_t wireDevicesCount;
extern WireDevice *wireDevices[];
extern size_t outputDevicesCount;
extern OutputDevice *outputDevices[];

void updateDeviceConnection();
void outputToDevices();
uint8_t deviceResponding(WireDevice &device);
bool deviceConnectionChanged(WireDevice &device);
bool onDeviceConnectionChanged(WireDevice &device);
