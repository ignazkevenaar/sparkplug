#pragma once

#include <Arduino.h>

#include <HTTPUpdateServer.h>

#include "webServer.h"

void setupUpdateServer();

extern const char *UpdateServerHostName;
extern HTTPUpdateServer httpUpdater;
