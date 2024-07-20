#include "helpers/macros.h"

#include "deviceManager.h"
#include "lighting.h"

__attribute__((weak)) int wirePins[] = {4, 5}; // { SDA, SCL }.
__attribute__((weak)) WireDevice *wireDevices[] = {};
__attribute__((weak)) extern size_t wireDevicesCount;
__attribute__((weak)) OutputDevice *outputDevices[] = {};
__attribute__((weak)) extern size_t outputDevicesCount;

const char *wireErrorMessagesByReturnCode[] = {
    "success",
    "data too long to fit in transmit buffer",
    "received NACK on transmit of address",
    "received NACK on transmit of data",
    "other error",
    "timeout"
};

void updateDeviceConnection()
{
    Wire.begin(wirePins[0], wirePins[1]);
    Wire.setClock(400000);

    bool shouldUpdateChannels = false;

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
    uint8_t error = Wire.endTransmission();

    if (error && error < 5)
    {
        Serial.print("I²C error at 0x");
        Serial.print(device.address, HEX);
        Serial.print(": ");
        Serial.print(wireErrorMessagesByReturnCode[error]);
        Serial.println(".");
    }

    return !error;
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
