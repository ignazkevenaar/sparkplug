#include "helpers/macros.h"
#include "helpers/progmem_readanything.h"

#include "lighting.h"

const uint16_t deltaTime = 16; // +- 60 FPS.

constexpr auto uconstrain(auto value, auto b1, auto b2)
{
  return constrain(value, min(b1, b2), max(b1, b2));
}

bool setLightMode(int modeID, int newState)
{
  if (modeID >= modesCount) return false;
  modes[modeID].nextState = newState;
  return true;
}

void applyLightModeChanges()
{
  bool anyModeChanged = false;

  for (int i = 0; i < modesCount; i++)
  {
    LightingMode &mode = modes[i];
    if (mode.nextState == -1) continue;
    if (onLightingModeChanged(i))
    {
      mode.currentState = mode.nextState;
      anyModeChanged = true;
    }
    mode.nextState = -1; // Maybe move this up to keep checking condition.
  }

  // Update mode changes to channels.
  if (anyModeChanged) updateChannelValues();
}

__attribute__((weak)) bool onLightingModeChanged(int modeID)
{
  return true; // Parse mode change by default.
}

void updateChannelValues()
{
  for (int i = 0; i < channelsCount; i++)
  {
    Channel &channel = channels[i];
    uint16_t newValue = getChannelValue(channel);
    startFade(channel, newValue);
  }
}

uint16_t getChannelValue(Channel &channel)
{
  int chosenIndex = 0;
  float baseValue = 0;
  int highestEnabledBlinkIndex = -1;

  for (int i = 0; i < channel.presetCount; i++)
  {
    const Preset preset = PROGMEM_getAnything(&channel.presets[i]);

    if (modes[preset.modeID].currentState <= 0) continue;

    if (preset.mode == PresetModes::Blink)
    {
      highestEnabledBlinkIndex = i;
      // Determines wheter or not the blink preset influences the channel value.
      // Should only happen on positive blink phase.
      if (!channel.blinkPhase) continue;
    }

    switch (preset.priorityMode)
    {
    case SwopModes::LTP:
      chosenIndex = i;
      baseValue = preset.intensity;
      break;
    case SwopModes::HTP:
      if (preset.intensity > baseValue)
      {
        chosenIndex = i;
        baseValue = preset.intensity;
      }
      break;
    case SwopModes::LoTP:
      if (preset.intensity < baseValue)
      {
        chosenIndex = i;
        baseValue = preset.intensity;
      }
      break;
    }
  }

  channel.previousPresetIndex = channel.activePresetIndex;
  channel.activePresetIndex = chosenIndex;
  channel.blinkPresetIndex = highestEnabledBlinkIndex;

  if (channel.blinkPresetIndex < channel.activePresetIndex)
  {
    // Stopping blink.
    channel.timerBlink = 0;
    channel.blinkPhase = 0;
  }

  return baseValue;
}

bool startFade(Channel &channel, uint16_t value)
{
  channel.transitionFrom = channel.value;
  channel.transitionTo = value;

  if (channel.transitionFrom != channel.transitionTo)
  {
    // Precalculate fade speeds.
    uint16_t presetIndex = channel.previousPresetIndex < channel.activePresetIndex ? channel.activePresetIndex : channel.previousPresetIndex;

    const Preset preset = PROGMEM_getAnything(&channel.presets[presetIndex]);

    int32_t fadeSpeed = channel.previousPresetIndex < channel.activePresetIndex ? preset.fadeSpeedRising : preset.fadeSpeedFalling;

    int32_t fadeAmount = 65536 / fadeSpeed * deltaTime;
    if (channel.transitionTo < channel.transitionFrom) fadeAmount *= -1;
    channel.fadeAmount = fadeAmount;

    return true;
  }

  return false;
}

void updateFadeChannels()
{
  for (int i = 0; i < channelsCount; i++)
  {
    Channel &channel = channels[i];
    updateFade(channel);
    updateBlink(channel);
  }
}

void updateFade(Channel &channel)
{
  if (channel.value == channel.transitionTo || channel.activePresetIndex == -1) return;

  // This onwards can be precalculated on fade start.

  // Until here.

  channel.value = uconstrain((int32_t)channel.value + channel.fadeAmount, channel.transitionFrom, channel.transitionTo);
  channel.wasUpdated = true;
}

void updateBlink(Channel &channel)
{
  if (channel.blinkPresetIndex == -1) return;

  const Preset preset = PROGMEM_getAnything(&channel.presets[channel.blinkPresetIndex]);
  int16_t interval = channel.blinkPhase ? preset.timeOff : preset.timeOn;

  if (currentMillis - channel.timerBlink > interval)
  {
    channel.timerBlink = currentMillis - (currentMillis - channel.timerBlink - interval);

    // Call onBlinkPhaseChanged event.
    if (!onBlinkPhaseChanged(channel)) return;

    channel.blinkPhase = !channel.blinkPhase;
    uint16_t newValue = getChannelValue(channel);
    startFade(channel, newValue);
  }
}

__attribute__((weak)) bool onBlinkPhaseChanged(Channel &channel)
{
  return true; // Apply blink phase change by default.
}

void clearAllChannelsChanged()
{
  for (int i = 0; i < channelsCount; i++)
    channels[i].wasUpdated = false;
}
