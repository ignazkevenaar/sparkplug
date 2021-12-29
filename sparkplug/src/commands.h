#pragma once

#include <Arduino.h>

#include "types/command.h"
#include "types/version.h"

void welcomeMessage();

extern const Command *commands[];
extern size_t commandCount;
extern Version version;
