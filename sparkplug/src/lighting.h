#pragma once

#include <Arduino.h>

#include "helpers/macros.h"
#include "helpers/progmem_readanything.h"
#include "types/channel.h"
#include "types/lightingmode.h"
#include "types/preset.h"

extern uint32_t currentMillis;
extern const size_t modesCount;
extern LightingMode modes[];
extern Channel channels[];
extern const size_t channelsCount;

bool setLightMode(int modeID, int newState);
void applyLightModeChanges();
void updateChannelValues();
uint16_t getChannelValue(Channel &channel);
void clearAllChannelsChanged();

bool startFade(Channel &channel, uint16_t value);
void updateFadeChannels(uint16_t deltaTime);
void updateFade(Channel &channel, uint16_t deltaTime);
void updateBlink(Channel &channel);

bool onLightingModeChanged(int modeID);
bool onBlinkPhaseChanged(Channel &channel);
