#pragma once

struct Command
{
  int ID;
  const char *shortIndentifier;
  const char *identifier;
  const char *helpText;

  void (*execute)(const Command &command, char **arguments, uint8_t length);
};
