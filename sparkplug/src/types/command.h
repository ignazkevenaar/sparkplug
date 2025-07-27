#pragma once

struct Command
{
    const char *shortIndentifier;
    const char *identifier;
    const char *helpText;

    void (*execute)(const Command &command, char **arguments, uint8_t length);
};
