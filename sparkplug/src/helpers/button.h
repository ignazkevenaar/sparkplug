#pragma once

#include <Arduino.h>

class Button
{
  public:
    Button(uint8_t pin_, bool reversed_);
    // Button(uint8_t pin_) : pin(pin_) {};
    void update();
    bool isPressed();
    bool isReleased();
    bool changed();
    uint8_t getValue();

  private:
    uint8_t pin;

    uint8_t previousValue, value;
    bool reversed, pressed, released;
};
