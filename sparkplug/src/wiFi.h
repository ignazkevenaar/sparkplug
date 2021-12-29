#pragma once

#include <Arduino.h>

#include <ESP8266WiFi.h>

extern IPAddress accessPointAddress;
extern IPAddress subnetMask;
extern const char *ssid;
extern const char *password;

void setupWiFi();
