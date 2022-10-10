#include <Arduino.h>

#include "error.h"

const char titleMessageSeparator = ':';
ANSI ansi(&Serial);
boolean terminalSupportsANSI = true;

void printError(char *title, char *message)
{
    if (terminalSupportsANSI) ansi.color(ansi.black, ansi.red);
    Serial.print(title);

    if (terminalSupportsANSI) ansi.color(ansi.red, ansi.black);
    else Serial.print(titleMessageSeparator);

    Serial.print(' ');
    Serial.print(message);

    if (terminalSupportsANSI) ansi.normal();
}
