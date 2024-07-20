#include "UpdateServer.h"

const char *UpdateServerHostName = "esp8266-webupdate";
ESP8266HTTPUpdateServer httpUpdater;

void setupUpdateServer()
{
    // Setup UpdateServer
    httpUpdater.setup(&server);
    Serial.println("Update server ready. Visit /update");
}
