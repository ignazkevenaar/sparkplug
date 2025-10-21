#pragma once

#include "../../src/spark.h"

#include "devices.h"
#include "presets.h"
#include "../../src/helpers/button.h"
#include "../../src/remotes/RM-X155.h"

const char *configName = "Default";

// WiFI settings
const char *ssid = "Sparkplug - Default";
const char *password = "thereisnospoon";

const uint8_t pinRotaryA = 24;
const uint8_t pinRotaryB = 25;
const uint8_t pinBuzzer = A0;
const uint8_t pinDialLED = 12;
const uint8_t pinInfrared = 5;
const uint8_t pinBattery = A3;
const uint8_t pinScorpioStart = 16;
const uint8_t scorpioCount = 8;

Button buttonRotaryA(pinRotaryA, true);
Button buttonRotaryB(pinRotaryB, true);
Button buttonScorpio[scorpioCount] = {
    Button(pinScorpioStart, true),     // FlashToPass,
    Button(pinScorpioStart + 1, true), // HighBeams,
    Button(pinScorpioStart + 2, true), // Hazards,
    Button(pinScorpioStart + 3, true), // Neutral,
    Button(pinScorpioStart + 4, true), // BlinkRight,
    Button(pinScorpioStart + 5, true), // BlinkLeft,
    Button(pinScorpioStart + 6, true), // Brake,
    Button(pinScorpioStart + 7, true), // BrakeHold
};

auto& [
    buttonFlashToPass,
    buttonHighBeams,
    buttonHazards,
    buttonNeutral,
    buttonBlinkRight,
    buttonBlinkLeft,
    buttonBrake,
    buttonBrakeHold
] = buttonScorpio;

bool shouldClickForBlinker = false;

bool onInitialize()
{
    // Scorpio IO port
    for (int i = 0; i <= scorpioCount; i++) {
        pinMode(pinScorpioStart + i, INPUT);
    }

    // Rotary switch
    pinMode(pinRotaryA, INPUT_PULLUP);
    pinMode(pinRotaryB, INPUT_PULLUP);

    // Battery monitor
    pinMode(pinBattery, INPUT);
    analogReadResolution(12);

    // Beep!
    pinMode(pinBuzzer, OUTPUT);
    digitalWrite(pinBuzzer, HIGH);
    delay(50);
    digitalWrite(pinBuzzer, LOW);

    pinMode(pinDialLED, OUTPUT);

    return true;
}

__attribute__((weak)) void onInfraredPressed(InfraredData irData)
{
    Serial.print("Remote pressed 0x");
    Serial.println(irData.command, HEX);

    if (irData.command == BUTTON_UP)
    {
        if (modes[LowBeams].currentState == 255)
        {
            setLightMode(Parking, 0);
            setLightMode(LowBeams, 0);
        }
        else if (modes[Parking].currentState == 255)
        {
            setLightMode(LowBeams, 255);
        }
        else
        {
            setLightMode(Parking, 255);
        }
    }
    else if (irData.command == BUTTON_DOWN)
    {
        toggleLightMode(Brake);
    }
    else if (irData.command == BUTTON_LEFT)
    {
        toggleLightMode(BlinkL);
    }
    else if (irData.command == BUTTON_RIGHT)
    {
        toggleLightMode(BlinkR);
    }
    else if (irData.command == BUTTON_ENTER)
    {
        toggleLightMode(Hazards);
    }
}

__attribute__((weak)) void onInfraredHeld(InfraredData irData)
{
    Serial.print("Remote held 0x");
    Serial.println(irData.command, HEX);

    if (irData.command == BUTTON_UP)
    {
        setLightMode(FlashToPass, 255);
    }
    else if (irData.command == BUTTON_DOWN)
    {
        setLightMode(Brake, 255);
    }
}

__attribute__((weak)) void onInfraredReleased(InfraredData irData)
{
    Serial.print("Remote released 0x");
    Serial.println(irData.command, HEX);

    if (irData.command == BUTTON_UP)
    {
        setLightMode(FlashToPass, 0);
    }
    else if (irData.command == BUTTON_DOWN)
    {
        setLightMode(Brake, 0);
    }
}

void onUpdate()
{
    buttonRotaryA.update();
    buttonRotaryB.update();

    for (int i = 0; i <= scorpioCount; i++) {
        buttonScorpio[i].update();
    }

    // Handle changes...
    if (buttonFlashToPass.changed()) setLightMode(FlashToPass, buttonFlashToPass.getValue() * 255);
    if (buttonHighBeams.changed() || buttonRotaryB.changed()) {
        setLightMode(HighBeams,   (buttonHighBeams.getValue() && buttonRotaryB.getValue()) * 255);
    }
    if (buttonHazards.changed() && buttonHazards.getValue() == 1) toggleLightMode(Hazards);
    // if (buttonNeutral.changed() && buttonNeutral.getValue() == 1) toggleLightMode(Neutral);
    if (buttonBlinkRight.changed())  setLightMode(BlinkR,      buttonBlinkRight.getValue() * 255);
    if (buttonBlinkLeft.changed())   setLightMode(BlinkL,      buttonBlinkLeft.getValue() * 255);
    if (buttonBrake.changed())       setLightMode(Brake,       buttonBrake.getValue() * 255);
    if (buttonBrakeHold.changed())   setLightMode(Brake,       buttonBrakeHold.getValue() * 255);

    if (buttonRotaryA.changed() || buttonRotaryB.changed())
    {
        digitalWrite(pinDialLED, buttonRotaryA.getValue() || buttonRotaryB.getValue());
    }

    if (buttonRotaryA.changed())   {
        setLightMode(Parking,  buttonRotaryA.getValue() * 255);
    }
    if (buttonRotaryB.changed()) {
        setLightMode(DaytimeRunning, buttonRotaryB.getValue() * 255);
        setLightMode(Parking, buttonRotaryB.getValue() * 255);
        setLightMode(LowBeams, buttonRotaryB.getValue() * 255);
    }

    if (shouldClickForBlinker)
    {
        shouldClickForBlinker = false;
        // Tick!
        digitalWrite(pinBuzzer, HIGH);
        delay(1);
        digitalWrite(pinBuzzer, LOW);
    }
}

bool onBlinkPhaseChanged(Channel &channel)
{
    shouldClickForBlinker = true;
    return true;
}
