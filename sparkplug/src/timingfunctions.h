#pragma once

#include <Arduino.h>

enum TimingFunctions
{
    Linear,
    Exponential
};

uint16_t useTimingFunction(int kind, uint16_t input);
