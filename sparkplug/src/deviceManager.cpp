#include "helpers/macros.h"

#include "deviceManager.h"
#include "lighting.h"

__attribute__((weak)) int wirePins[] = {4, 5}; // { SDA, SCL }.
__attribute__((weak)) WireDevice *wireDevices[] = {};
__attribute__((weak)) extern size_t wireDevicesCount;
__attribute__((weak)) OutputDevice *outputDevices[] = {};
__attribute__((weak)) extern size_t outputDevicesCount;

void updateDeviceConnection()
{
  Wire.begin(wirePins[0], wirePins[1]);

  bool shouldUpdateChannels = false;

  // Put on timer.
  for (int i = 0; i < wireDevicesCount; i++)
  {
    WireDevice &device = *wireDevices[i];
    if (deviceConnectionChanged(device))
    {
      if (device.connected) device.setup();
      shouldUpdateChannels = onDeviceConnectionChanged(device);
    }
  }

  if (shouldUpdateChannels) updateChannelValues();
}

void outputToDevices()
{
  for (int i = 0; i < outputDevicesCount; i++)
    outputDevices[i]->output();
}

bool deviceResponding(WireDevice &device)
{
  Wire.beginTransmission(device.address);
  return Wire.endTransmission() == 0;
}

bool deviceConnectionChanged(WireDevice &device)
{
  bool connected = deviceResponding(device);
  bool connectionChanged = device.connected != connected;
  device.connected = connected;
  return connectionChanged;
}

__attribute__((weak)) bool onDeviceConnectionChanged(WireDevice &device)
{
  return true; // Recalculate lights on device change by default.
}
