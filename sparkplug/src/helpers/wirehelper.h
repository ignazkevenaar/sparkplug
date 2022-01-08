#pragma once

class WireHelper
{
public:
  const static uint8_t read8(uint8_t deviceAddress, uint8_t registerAddress)
  {
    Wire.beginTransmission(deviceAddress);
    Wire.write(registerAddress);
    Wire.endTransmission();

    Wire.requestFrom((uint8_t)deviceAddress, (uint8_t)1);
    return Wire.read();
  }

  const static void write8(uint8_t deviceAddress, uint8_t registerAddress, uint8_t data)
  {
    Wire.beginTransmission(deviceAddress);
    Wire.write(registerAddress);
    Wire.write(data);
    Wire.endTransmission();
  }
};
