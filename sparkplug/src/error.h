#pragma once

#include <Arduino.h>

#include <ansi.h>

void printError(char *title, char *message);
extern const char titleMessageSeparator;
extern boolean terminalSupportsANSI;
