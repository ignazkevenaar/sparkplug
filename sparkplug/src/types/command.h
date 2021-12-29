#pragma once

struct Command
{
  char *shortIndentifier;
  char *identifier;
  char *helpText;

  void (*execute)(char **arguments, uint8_t length);
};
