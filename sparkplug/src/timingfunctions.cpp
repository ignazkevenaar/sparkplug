#include "timingfunctions.h"

uint16_t timingLinear(uint16_t input)
{
    return input;
}

uint16_t timingExponential(uint16_t input)
{
    float exp = 2.8;
    uint16_t v = pow(input, exp) / pow(2, 16 * (exp - 1));
    return v;
}

typedef uint16_t (*FunctionPointer)(uint16_t);

FunctionPointer functionPointers[] = {
    &timingLinear,
    &timingExponential
};

uint16_t useTimingFunction(int kind, uint16_t input)
{
    return (*functionPointers[kind])(input);
}
