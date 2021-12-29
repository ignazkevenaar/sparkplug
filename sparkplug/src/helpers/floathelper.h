#pragma once

#define FLT_EPSILON 1.19209290E-07F // decimal constant

class FloatHelper
{
public:
  const static bool relativelyEqual(float a, float b, float maxRelativeDiff = FLT_EPSILON)
  {
    const float difference = fabs(a - b);
    // Scale to the largest value.
    a = fabs(a);
    b = fabs(b);
    const float scaledEpsilon =
        maxRelativeDiff * max(a, b);

    return difference <= scaledEpsilon;
  };
};
