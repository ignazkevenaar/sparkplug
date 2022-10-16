#pragma once

#include <Arduino.h>

#include <ESP8266WebServer.h>
#include <LittleFS.h>

void setupWebServer();
void updateWebServer();
String getContentType(String filename);
void handleNotFound(); // This function is called for all unknown URLs.

extern uint16_t portHTTP;
extern ESP8266WebServer server;
