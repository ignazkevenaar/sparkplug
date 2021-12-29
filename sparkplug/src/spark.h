#pragma once

#include <Arduino.h>

#include "types/version.h"

#include "OTA.h"
#include "commands.h"
#include "deviceManager.h"
#include "input.h"
#include "lighting.h"
#include "timer.h"
#include "webServer.h"
#include "webSockets.h"
#include "wiFi.h"

void sparkInitialize();
bool onInitialize();
void sparkUpdate();
void onUpdate();

extern Version version;
extern uint32_t currentMillis;
