#include "UpdateServer.h"

const char *UpdateServerHostName = "esp32-webupdate";
HTTPUpdateServer httpUpdater;

void setupUpdateServer()
{
    // Setup UpdateServer
    httpUpdater.setup(&server);
    Serial.println("Update server ready. Visit /update");
}
