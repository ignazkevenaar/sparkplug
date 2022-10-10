#include "commands.h"

#include "helpers/macros.h"
#include "input.h"
#include "lighting.h"

enum commandIDs
{
  idSetCommand,
  idUnsetCommand,
  idGetCommand,
  idTestCommand,
  idColorCommand,
  idHelpCommand,
  idVersionCommand,
};

void printSparkplugBranding()
{
  if (terminalSupportsANSI)
  {
    ansi.bold();
    ansi.color(ansi.black, ansi.rgb2color(242, 209, 110));
  }

  Serial.print("Sparkplug");

  if (terminalSupportsANSI)
  {
    ansi.normal();
    ansi.color(ansi.red, ansi.rgb2color(229, 129, 56));
  }

  Serial.print(" - version ");
  Serial.println(version.getString());

  if (terminalSupportsANSI) ansi.normal();

  Serial.println();
}

void welcomeMessage()
{
  Serial.println();
  printSparkplugBranding();
  Serial.println("Type `?` to see a list of all available commands.");
  Serial.println();
}

void versionExecute(const Command &command, char **arguments, uint8_t length)
{
  outputBuffer.print(version.getString());
}

const Command versionCommand =
    {
        idVersionCommand,
        "V",
        "version",
        "Get Sparkplug semantic version number.",
        &versionExecute,
};

void helpExecute(const Command &command, char **arguments, uint8_t length)
{
  Serial.println();
  printSparkplugBranding();

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
        idHelpCommand,
        "?",
        "help",
        "Get information on available commands and their usage. (This command.)",
        &helpExecute,
};

void testExecute(const Command &command, char **arguments, uint8_t length)
{
  // Serial.println("Sleeping...");
  // delay(1500);

  // // Your arguments in c-string format.
  // for (int i = 0; i < length; i++)
  //   Serial.println(arguments[i]);

  printError("Error", "This is an enormous error. Big mistake! Huge!");
}

const Command testCommand =
    {
        idTestCommand,
        "T",
        "test",
        "Test command used for echoing presented command arguments.",
        &testExecute,
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

void argumentToRangeTokens(char *string, char **firstToken, char **lastToken)
{
  const char delimiter[] = "-";
  char *token;

  token = strtok(string, delimiter);
  *firstToken = token;

  while (token != NULL)
  {
    *lastToken = token; // Only accept last token as 'end' of range.
    token = strtok(NULL, delimiter);
  }
}

uint32_t strToLong(char *string, bool &error)
{
  char *endptr;
  uint32_t number = strtoul(string, &endptr, 0);
  if (endptr == string) error |= true;
  return number;
}

bool argumentIsRange(char *string, uint16_t *rangeFrom, uint16_t *rangeTo, bool &error)
{
  char *firstToken;
  char *lastToken;
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
    return false;
  }

  bool isRange = firstToken != lastToken;

  *rangeFrom = min(firstNumber, lastNumber);
  *rangeTo = max(firstNumber, lastNumber);

  return isRange;
}

void setUnsetGetExecute(const Command &command, char **arguments, uint8_t length)
{
  const bool setUnset = command.ID == idSetCommand || command.ID == idUnsetCommand;

  if (!length)
  {
    for (int modeIndex = 0; modeIndex < modesCount; modeIndex++)
    {
      if (command.ID == idUnsetCommand) setLightMode(modeIndex, command.ID == idSetCommand);
      if (modes[modeIndex].currentState > 0) outputMode(modeIndex);
    }
    return;
  }

  for (int i = 0; i < length; i++)
  {
    bool error = false;
    uint16_t rangeFrom = 0;
    uint16_t rangeTo = 0;
    bool isRange = argumentIsRange(arguments[i], &rangeFrom, &rangeTo, error);
    if (error) continue; // Continue parsing following arguments.

    for (int modeIndex = rangeFrom; modeIndex <= rangeTo; modeIndex++)
    {
      if (setUnset && !setLightMode(modeIndex, command.ID == idSetCommand))
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
        idSetCommand,
        "S",
        "set",
        "Set light mode. [mode, range, ...]",
        &setUnsetGetExecute,
};

const Command unsetCommand =
    {
        idUnsetCommand,
        "U",
        "unset",
        "Unset light mode. [mode, range, ...]",
        &setUnsetGetExecute,
};

const Command getCommand =
    {
        idGetCommand,
        "G",
        "get",
        "Get light mode state. [mode, range, ...]",
        &setUnsetGetExecute,
};

void colorExecute(const Command &command, char **arguments, uint8_t length)
{
  Serial.println("Toggled serial mode.");
  terminalSupportsANSI = !terminalSupportsANSI;
}

const Command colorCommand =
    {
        idColorCommand,
        "C",
        "color",
        "ANSI magic?",
        &colorExecute,
};

const Command *commands[] =
    {
        &setCommand,
        &unsetCommand,
        &getCommand,
        &testCommand,
        &colorCommand,
        &helpCommand,
        &versionCommand,
};
size_t commandCount = COUNT_OF(commands);
