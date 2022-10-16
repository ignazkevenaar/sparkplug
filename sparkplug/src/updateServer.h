#pragma once

#include <Arduino.h>

#include <ESP8266HTTPUpdateServer.h>

#include "webServer.h"

void setupUpdateServer();

extern const char *UpdateServerHostName;
extern ESP8266HTTPUpdateServer httpUpdater;
