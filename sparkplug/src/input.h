#pragma once

#include <Arduino.h>

#include <PrintCharArray.h>

void readSerialInput();
void splitMessage(char *message, uint8_t messageLength);
void parseCommand(char *commandString, char **arguments, uint8_t argumentCount);

const char outputKeyValueSeparator = ':';
const char outputGroupSeparator = ',';
extern PrintCharArray outputBuffer;
