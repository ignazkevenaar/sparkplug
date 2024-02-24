#pragma once

#include "../../../src/spark.h"

#include "devices.h"
#include "presets.h"

bool onInitialize()
{
  Serial.println("Hello from Fiat 500!");

  setLightMode(Hazards, 255);
  return true;
}

bool onLightingModeChanged(int modeID)
{
  return true; // Allow mode change to apply.
}

bool onDeviceConnectionChanged(WireDevice &device)
{
  Serial.print("Device ");
  if (!device.connected) Serial.print("dis");
  Serial.print("connected at ");
  Serial.print("0x");
  Serial.println(device.address, HEX);

  return true; // Recalculate lights on device connection change.
}
