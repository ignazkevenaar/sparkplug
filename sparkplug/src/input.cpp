#include <Arduino.h>

#include "input.h"

#include "commands.h"
#include "helpers/macros.h"

// Max number of input characters.
const int inputBufferSize = 64;
// Max length of command identifier string.
const int commandMaxLength = 16;
// Max number of argument pointers.
const int argumentsMaxLength = 16;
// String token separators.
const char *commandArgumentSeparator = " ";
const char *argumentsSeparator = ", ";

int bufferIndex = 0;
char inputBuffer[inputBufferSize] = {};
// Array with pointers to c-string arguments out of tokens.
char *arguments[argumentsMaxLength] = {};

// Output
const int outputBufferSize = 256;
PrintCharArray outputBuffer(outputBufferSize);

void readSerialInput()
{
  while (Serial.available())
  {
    inputBuffer[bufferIndex] = Serial.read();

    if (inputBuffer[bufferIndex] == '\r' || inputBuffer[bufferIndex] == '\n')
    {
      inputBuffer[bufferIndex] = '\0';
      if (bufferIndex > 0)
      {
        splitMessage(inputBuffer, bufferIndex + 1);
        Serial.print(outputBuffer.getBuffer());
      }

      bufferIndex = 0;
      inputBuffer[0] = '\0';
    }
    else
      bufferIndex = (bufferIndex + 1) % inputBufferSize;
  }
}

void splitMessage(char *message, uint8_t messageLength)
{
  int tokenIndex = 0;
  char commandString[commandMaxLength];

  char *token = strtok(message, commandArgumentSeparator);

  while (token != NULL)
  {
    if (tokenIndex == 0) strcpy(commandString, token);
    else
      arguments[tokenIndex - 1] = token;

    token = strtok(NULL, argumentsSeparator);
    tokenIndex++;
  }

  outputBuffer.clear();
  parseCommand(commandString, arguments, tokenIndex - 1);

  // Clean argument pointers.
  memset(arguments, 0, COUNT_OF(arguments));
}

void parseCommand(char *commandString, char **arguments, uint8_t length)
{
  for (int i = 0; i < commandCount; i++)
  {
    const Command &command = *commands[i];
    int resultLong = strcmp(commandString, command.identifier);
    int resultShort = strcmp(commandString, command.shortIndentifier);

    if (resultLong == 0 || resultShort == 0)
    {
      command.execute(arguments, length);
      return;
    }
  }

  // If identifier doesn't match any command.
  Serial.print("Unknown command: \"");
  Serial.print(commandString);
  Serial.println("\"");
}
