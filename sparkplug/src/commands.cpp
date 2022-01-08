#include "commands.h"

#include "helpers/macros.h"
#include "input.h"
#include "lighting.h"

void welcomeMessage()
{
  Serial.println();
  Serial.print("Sparkplug - version ");
  Serial.println(version.getString());
  Serial.println("Type `?` to see a list of all available commands.");
  Serial.println();
}

void versionExecute(char **arguments, uint8_t length)
{
  outputBuffer.print(version.getString());
}

const Command versionCommand =
    {
        "V",
        "version",
        "Get Sparkplug semantic version number.",
        &versionExecute};

void helpExecute(char **arguments, uint8_t length)
{
  Serial.println();
  Serial.print("Sparkplug - version ");
  Serial.println(version.getString());

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
        &helpExecute};

void testExecute(char **arguments, uint8_t length)
{
  Serial.println("Sleeping...");
  delay(1500);

  // Your arguments in c-string format.
  for (int i = 0; i < length; i++)
    Serial.println(arguments[i]);
}

const Command testCommand =
    {
        "T",
        "test",
        "Test command used for echoing presented command arguments.",
        &testExecute};

void outputMode(int modeIndex, bool nextState = false)
{
  outputBuffer.print(modeIndex);
  outputBuffer.print(outputKeyValueSeparator);
  outputBuffer.print(nextState ? modes[modeIndex].nextState : modes[modeIndex].currentState);
  outputBuffer.print(outputGroupSeparator);
}

void setExecute(char **arguments, uint8_t length)
{
  outputBuffer.print("M ");
  for (int i = 0; i < length; i++)
  {
    // Convert each argument to int.
    int modeIndex = strtol(arguments[i], NULL, 10);
    if (!setLightMode(modeIndex, 1))
    {
      Serial.println("Mode index out of range or already set.");
      continue;
    }
    outputMode(modeIndex, true);
  }
  outputBuffer.println();
}

const Command setCommand =
    {
        "S",
        "set",
        "Set light mode. [mode, ...]",
        &setExecute};

void unsetExecute(char **arguments, uint8_t length)
{
  outputBuffer.print("M ");
  for (int i = 0; i < length; i++)
  {
    // Convert each argument to int.
    int modeIndex = strtol(arguments[i], NULL, 10);
    if (!setLightMode(modeIndex, 0))
    {
      Serial.println("Mode index out of range or already set.");
      continue;
    }
    outputMode(modeIndex, true);
  }
  outputBuffer.println();
}

const Command unsetCommand =
    {
        "U",
        "unset",
        "Unset light mode. [mode, ...]",
        &unsetExecute};

void getExecute(char **arguments, uint8_t length)
{
  outputBuffer.print("M ");
  if (!length)
  {
    for (int i = 0; i < modesCount; i++)
    {
      if (modes[i].currentState == 0) continue;
      outputMode(i);
    }
  }
  else
  {
    for (int i = 0; i < length; i++)
    {
      // Convert each argument to int.
      int modeIndex = strtol(arguments[i], NULL, 10);
      if (modeIndex < 0 || modeIndex > modesCount) continue;
      outputMode(modeIndex);
    }
  }
  outputBuffer.println();
}

const Command getCommand =
    {
        "G",
        "get",
        "Get light mode state. [(all)], [mode, ...]",
        &getExecute};

const Command *commands[] =
    {
        &setCommand,
        &unsetCommand,
        &getCommand,
        &testCommand,
        &helpCommand,
        &versionCommand,
};
size_t commandCount = COUNT_OF(commands);
