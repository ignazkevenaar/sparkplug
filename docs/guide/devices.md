# Setting up Devices

Devices represent external or built-in means to output lighting. Most devices have multiple channels (e.g. LED-driver ICs, or pins on a microcontroller). Every device requires its own driver with a `setup()` and, in the case of an output device, an `output()`.

Devices using the I²C protocol are "hot-swappable"; A setup routine runs when the device is connected, after which the current lighting state is sent to the device.

It comes built-in with support for the following LED diver ICs:

* [NXP PCA9685](https://www.nxp.com/docs/en/data-sheet/PCA9685.pdf)
* [TI LP55231](https://www.ti.com/lit/ds/symlink/lp55231.pdf)
* [Awinic AW9523](https://doc.awinic.com/doc/202403/deffbf3b-7e7b-4ff6-8e91-fd85e2d845d5.pdf)

Example definition of devices in a config:
```cpp
#pragma once

builtinLED builtin(0);
PCA9685 dashboard(0x40, 0, 4);

WireDevice *wireDevices[] =
{
  &dashboard
};
size_t wireDevicesCount = COUNT_OF(wireDevices);

OutputDevice *outputDevices[] =
{
  &dashboard,
  &builtin,
};
size_t outputDevicesCount = COUNT_OF(outputDevices);
```

* Devices in `wireDevices[]` will be checked for (dis-)connection and initialized when connected.
* Devices in `outputDevices[]` will be updated with changed lighting channels for every frame.
