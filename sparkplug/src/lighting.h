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

/**
A brief description on a single line, ended by a period or blank line.
@param myParam1 Description of 1st parameter.
@param myParam2 Description of 2nd parameter.
@returns Description of returned value.
*/
bool setLightMode(int modeID, int newState);

void applyLightModeChanges();
void updateChannelValues();
uint16_t getChannelValue(Channel &channel);
void clearAllChannelsChanged();

bool startFade(Channel &channel, uint16_t value);
void updateFadeChannels();
void updateFade(Channel &channel);
void updateBlink(Channel &channel);

bool onLightingModeChanged(int modeID);
bool onBlinkPhaseChanged(Channel &channel);
