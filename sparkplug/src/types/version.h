#pragma once

#include <Arduino.h>

struct Version
{
  uint8_t major, minor, patch;
  char *label;
  char *build;
  char buffer[64];

  Version(uint8_t major_ = 0, uint8_t minor_ = 0, uint8_t patch_ = 0, char *label_ = nullptr, char *build_ = nullptr) : major{major_}, minor{minor_}, patch{patch_}, label{label_}, build{build_}
  {
    snprintf(buffer, 16, "%d.%d.%d", major, minor, patch);

    if (label)
    {
      char versionLabel[32];
      snprintf(versionLabel, 32, "-%s", label);
      strncat(buffer, versionLabel, 32);
    }

    if (build)
    {
      char versionBuild[16];
      snprintf(versionBuild, 32, "+%s", build);
      strncat(buffer, versionBuild, 32);
    }
  }

  char *getString()
  {
    return buffer;
  }
};
