#include "wiFi.h"

IPAddress accessPointAddress = IPAddress(192, 168, 4, 1);
IPAddress subnetMask = IPAddress(255, 255, 255, 0);
extern const char *ssid;
extern const char *password;

void setupWiFi()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(accessPointAddress, accessPointAddress, subnetMask);
    WiFi.softAP(ssid, password);
}
