#pragma once

struct Device
{
  bool connected;
  virtual void setup() = 0;
};
