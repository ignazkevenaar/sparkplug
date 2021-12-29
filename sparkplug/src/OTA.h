#pragma once

#include <Arduino.h>

#include <ArduinoOTA.h>

extern const char *OTAHostName;
extern const char *OTAPassword;

void setupOTA();

void onStartOTA();
void onEndOTA();
void onProgressOTA(unsigned int progress, unsigned int total);
void onErrorOTA(ota_error_t error);
