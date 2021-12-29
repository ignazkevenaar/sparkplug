#include "wiFi.h"

IPAddress accessPointAddress = IPAddress(192, 168, 4, 1);
IPAddress subnetMask = IPAddress(255, 255, 255, 0);
const char *ssid = "ESPap";
const char *password = "thereisnospoon";

void setupWiFi()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(accessPointAddress, accessPointAddress, subnetMask);
  WiFi.softAP(ssid, password);
}
