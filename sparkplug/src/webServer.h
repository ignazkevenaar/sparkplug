#pragma once

#include <Arduino.h>

#include <ESP8266WebServer.h>
#include <LittleFS.h>

extern uint16_t portHTTP;

void setupWebServer();
void updateWebServer();
String getContentType(String filename);
void handleNotFound(); // This function is called for all unknown URLs.
