#include "button.h"

Button::Button(uint8_t pin_, bool reversed_)
{
    pin = pin_;
    reversed = reversed_;
    previousValue = reversed ? 1 : 0;
    value = previousValue;
};

void Button::update()
{
    uint8_t readValue = digitalRead(pin);
    pressed = false;
    released = false;

    if (readValue != previousValue)
    {
        delay(20);

        uint8_t debounceValue = digitalRead(pin);
        if (readValue != debounceValue) return;

        value = readValue;
        if (reversed)
        {
            pressed = !value;
            released = value;
        }
        else
        {
            pressed = value;
            released = !value;
        }
        previousValue = value;
    }
}

bool Button::isPressed()
{
    return pressed;
}

bool Button::isReleased()
{
    return released;
}

bool Button::changed()
{
    return pressed || released;
}

uint8_t Button::getValue()
{
    if (reversed) return 1 - value;
    return value;
}
