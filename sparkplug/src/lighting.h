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
extern const uint16_t deltaTime;

void setupChannel(Channel &channel);
void setupChannels();

bool setLightMode(int modeID, int newState);

void applyLightModeChanges();
void updatechannelValues(int modeID);
void updateChannelValues();
void calculateChannelValue(Channel &channel);
void clearAllChannelsChanged();

void startFade(Channel &channel, uint16_t value, uint16_t fadeSpeed);
void updateChannels();
void updateFade(Channel &channel);
void updateBlink(Channel &channel);

bool onLightingModeChanged(int modeID);
bool onBlinkPhaseChanged(Channel &channel);
