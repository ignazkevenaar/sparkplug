#include <Arduino.h>

#include "spark.h"

Version version(0, 0, 0, "indev");

uint32_t currentMillis = 0;

Timer timerLights(deltaTime);
Timer timerWire(1000);

void sparkInitialize()
{
  welcomeMessage();

  setupWiFi();
  setupOTA();
  setupWebServer();
  setupWebSockets();

  if (!onInitialize())
  {
    Serial.println("There was an error during initializing");
    for (;;)
    {
    } // Stop execution.
  }

  Serial.println("Ready.");
}

__attribute__((weak)) bool onInitialize()
{
  return true;
}

void sparkUpdate()
{
  currentMillis = millis();

  readSerialInput();
  applyLightModeChanges();

  if (timerWire.elapsed(currentMillis)) updateDeviceConnection();

  if (timerLights.elapsed(currentMillis))
  {
    updateFadeChannels();

    outputToDevices();
    clearAllChannelsChanged();
  }

  updateWebServer();
  updateWebSockets();

  onUpdate();
}

__attribute__((weak)) void onUpdate() {}
