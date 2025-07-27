#include "commands.h"

#include <Wire.h>

#include "fileSystem.h"
#include "helpers/macros.h"
#include "input.h"
#include "lighting.h"
#include "spark.h"

void printNameVersionAndConfig()
{
    Serial.println();
    Serial.print("Sparkplug - version ");
    Serial.println(version.getString());
    Serial.print("Config: ");
    Serial.println(configName);
    Serial.println();
}

void welcomeMessage()
{
    printNameVersionAndConfig();
    Serial.println("Type `?` to see a list of all available commands.");
    Serial.println();
}

void versionExecute(const Command &command, char **arguments, uint8_t length)
{
    outputBuffer.print(version.getString());
}

const Command versionCommand =
    {
        "V",
        "version",
        "Get Sparkplug semantic version number.",
        &versionExecute,
};

void infoExecute(const Command &command, char **arguments, uint8_t length)
{
    Serial.println();
    Serial.print(modesCount);
    Serial.println(" modes:");

    for (int i = 0; i < modesCount; i++)
    {
        Serial.print(i);
        Serial.print('\t');
        Serial.println(modeNames[i]);
    }

    Serial.println();
}

const Command infoCommand =
    {
        "I",
        "info",
        "Get configuration info.",
        &infoExecute,
};

void helpExecute(const Command &command, char **arguments, uint8_t length)
{
    printNameVersionAndConfig();
    Serial.println("Usage:");
    Serial.println(" command argument, argument...");
    Serial.println();
    Serial.println("Available commands:");
    Serial.println();

    for (int i = 0; i < commandCount; i++)
    {
        const Command &command = *commands[i];
        Serial.print(" ");
        Serial.print(command.shortIndentifier);
        Serial.print(" ");
        Serial.print(command.identifier);
        Serial.print("\t");
        Serial.println(command.helpText);
    }

    Serial.println();
}

const Command helpCommand =
    {
        "?",
        "help",
        "Get information on available commands and their usage. (This command.)",
        &helpExecute,
};

void fileExecute(const Command &command, char **arguments, uint8_t length)
{
    listHomeDirectory("/");
}

const Command fileCommand =
    {
        "F",
        "file",
        "List files in the littleFS root directory.",
        &fileExecute,
};

void scanExecute(const Command &command, char **arguments, uint8_t length)
{
    // From: https://playground.arduino.cc/Main/I2cScanner/

    byte error, address;
    int nDevices;

    Serial.println("Scanning...");

    nDevices = 0;
    for (address = 1; address < 127; address++)
    {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.print("I2C device found at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);

            nDevices++;
        }
        else if (error == 4)
        {
            Serial.print("Unknown error at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0)
        Serial.println("No I2C devices found\n");
    else
        Serial.println("done\n");
}

const Command scanCommand =
    {
        "B",
        "scan",
        "Scan the I2C bus for connected devices.",
        &scanExecute,
};

void outputMode(int modeIndex)
{
    if (outputBuffer.size() == 0)
        outputBuffer.print("M ");
    else
        outputBuffer.print(outputGroupSeparator);
    outputBuffer.print(modeIndex);
    outputBuffer.print(outputKeyValueSeparator);
    outputBuffer.print(modes[modeIndex].nextState > -1 ? modes[modeIndex].nextState : modes[modeIndex].currentState);
}

uint32_t strToLong(char *string, bool &error)
{
    char *endptr = nullptr;
    uint32_t number = strtoul(string, &endptr, 0);
    if (endptr == string)
    {
        error |= true;
        return 0;
    }

    return number;
}

void argumentToRangeTokens(char *string, char **firstToken, char **lastToken)
{
    const char delimiter[] = "-";
    char *token = strtok(string, delimiter);
    *firstToken = token;

    while (token != NULL)
    {
        *lastToken = token;
        token = strtok(NULL, delimiter);
    }
}

void argumentToRange(char *string, uint16_t *rangeFrom, uint16_t *rangeTo, bool &error)
{
    char *firstToken = nullptr;
    char *lastToken = nullptr;
    argumentToRangeTokens(string, &firstToken, &lastToken);

    char *endptr;
    bool errorFirst = false;
    bool errorLast = false;
    unsigned int firstNumber = strToLong(firstToken, errorFirst);
    unsigned int lastNumber = strToLong(lastToken, errorLast);

    if (errorFirst || errorLast)
    {
        Serial.print("Error in ");
        Serial.print(errorFirst ? "first" : "last");
        Serial.println(" range index.");

        error |= true;
        return;
    }

    *rangeFrom = min(firstNumber, lastNumber);
    *rangeTo = max(firstNumber, lastNumber);
}

void argumentToIDValue(char *string, char **modeID, char **value)
{
    int counter = 0;
    const char delimiter[] = ":";
    char *token = strtok(string, delimiter);

    while (token != NULL)
    {
        if (counter == 0) *modeID = token;
        else
            *value = token;

        token = strtok(NULL, delimiter);
        counter++;
    }
}

void setUnsetGetExecute(const Command &command, char **arguments, uint8_t length)
{
    const bool setUnset = command.shortIndentifier == "S" || command.shortIndentifier == "U";

    if (!length)
    {
        // If no arguments are provided for the unset command, all modes are turned off.
        // If no arguments are provided for the get command, the state of all modes is returned.
        for (int modeIndex = 0; modeIndex < modesCount; modeIndex++)
        {
            if (command.shortIndentifier == "U") setLightMode(modeIndex, 0);
            if (modes[modeIndex].currentState > 0) outputMode(modeIndex);
        }
        return;
    }

    for (int i = 0; i < length; i++)
    {
        // Split argument into mode ID or range and new mode value.
        char *modeIDOrRange = nullptr;
        char *valueArgument = nullptr;
        argumentToIDValue(arguments[i], &modeIDOrRange, &valueArgument);

        bool errorValue = false;
        unsigned int newModeValue = 255;
        if (valueArgument != NULL)
        {
            newModeValue = strToLong(valueArgument, errorValue);
            if (errorValue)
            {
                Serial.println("Error: Given value cannot be converted to unsigned long.");
                continue;
            }
        }

        // Try converting first half of command into a valid range.
        bool errorRange = false;
        uint16_t rangeFrom = 0;
        uint16_t rangeTo = 0;
        argumentToRange(modeIDOrRange, &rangeFrom, &rangeTo, errorRange);
        if (errorRange)
        {
            Serial.println("Error converting argument to valid range.");
            continue;
        }

        for (int modeIndex = rangeFrom; modeIndex <= rangeTo; modeIndex++)
        {
            if (setUnset && !setLightMode(modeIndex, command.shortIndentifier == "S" ? newModeValue : 0))
            {
                Serial.println("Mode index out of range or already set.");
                continue;
            }
            outputMode(modeIndex);
        }
    }
}

const Command setCommand =
    {
        "S",
        "set",
        "Set light mode. [mode, range, ...]",
        &setUnsetGetExecute,
};

const Command unsetCommand =
    {
        "U",
        "unset",
        "Unset light mode. [mode, range, ...]",
        &setUnsetGetExecute,
};

const Command getCommand =
    {
        "G",
        "get",
        "Get light mode state. [mode, range, ...]",
        &setUnsetGetExecute,
};

const Command *commands[] =
    {
        &helpCommand,
        &versionCommand,
        &setCommand,
        &unsetCommand,
        &getCommand,
        &scanCommand,
        &infoCommand,
        &fileCommand,
};
size_t commandCount = COUNT_OF(commands);
