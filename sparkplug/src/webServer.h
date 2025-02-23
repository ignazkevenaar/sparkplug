#pragma once

#include <Arduino.h>

#include <LittleFS.h>
#include <WebServer.h>

void setupWebServer();
void updateWebServer();
String getContentType(String filename);
void handleNotFound(); // This function is called for all unknown URLs.

extern uint16_t portHTTP;
extern WebServer server;
