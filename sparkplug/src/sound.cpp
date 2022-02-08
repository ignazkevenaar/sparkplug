#include <Arduino.h>

#include "sound.h"
#include "timer.h"

const int pinSound = D3;
Timer timerTick(300);

bool swap = false;

void setupSound()
{
    pinMode(pinSound, OUTPUT);
}

void updateSound()
{
    uint32_t currentMillis = millis();

    if (timerTick.elapsed(currentMillis))
    {
        playSound();
    }
}

void playSound()
{
    swap = !swap;
    tone(pinSound, swap ? 1500 : 1000, 5);
}
