#pragma once

struct Command
{
  int ID;
  char *shortIndentifier;
  char *identifier;
  char *helpText;

  void (*execute)(const Command &command, char **arguments, uint8_t length);
};
