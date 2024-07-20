#include "helpers/macros.h"
#include "helpers/progmem_readanything.h"

#include "lighting.h"

template <typename T>
constexpr auto uconstrain(T value, T b1, T b2)
{
    return constrain(value, min(b1, b2), max(b1, b2));
}

bool setLightMode(int modeID, int newState)
{
    if (modeID >= modesCount) return false;
    if (modes[modeID].currentState == newState) return false;
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
    int16_t chosenPresetIndex = -1;
    uint32_t baseValue = 0;
    int16_t highestEnabledBlinkIndex = -1;

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

        const uint16_t presetIntensity = preset.intensity << 8 | preset.intensity; // Shift 8-bit to 16-bit intensity.
        const int modeIntensity = modes[preset.modeID].currentState;
        const uint16_t intensity = presetIntensity * modeIntensity / 255;

        switch (preset.priorityMode)
        {
        case SwopModes::LTP:
            chosenPresetIndex = i;
            baseValue = intensity;
            break;
        case SwopModes::HTP:
            if (intensity > baseValue)
            {
                chosenPresetIndex = i;
                baseValue = intensity;
            }
            break;
        case SwopModes::LoTP:
            if (intensity < baseValue)
            {
                chosenPresetIndex = i;
                baseValue = intensity;
            }
            break;
        }
    }

    if (highestEnabledBlinkIndex > -1 && channel.blinkPresetIndex != highestEnabledBlinkIndex)
    {
        // Starting blink.
        channel.blinkStartTime = currentMillis;
        channel.blinkPhase = 0;
    }

    channel.previousPresetIndex = channel.activePresetIndex;
    channel.activePresetIndex = chosenPresetIndex;
    channel.blinkPresetIndex = highestEnabledBlinkIndex;

    return baseValue;
}

void startFade(Channel &channel, uint16_t value)
{
    channel.transitionFrom = channel.value;
    channel.transitionTo = value;

    if (channel.transitionFrom == value) return;

    uint16_t presetIndex = 0;
    if (channel.previousPresetIndex != -1 || channel.activePresetIndex != -1) presetIndex = max(channel.previousPresetIndex, channel.activePresetIndex);

    const Preset preset = PROGMEM_getAnything(&channel.presets[presetIndex]);
    int32_t fadeSpeed = channel.previousPresetIndex < channel.activePresetIndex ? preset.fadeSpeedRising : preset.fadeSpeedFalling;

    uint16_t totalChange = abs(channel.transitionTo - channel.transitionFrom);
    channel.startTime = currentMillis;

    // When the fade speed should be constant.
    // channel.targetDelay = fadeSpeed * totalChange / 65536;

    // When the fade speed should be the same for every change.
    channel.targetDelay = fadeSpeed;

    // Instantly set channel to prevent fade and divide by zero.
    if (channel.targetDelay == 0)
    {
        channel.value = channel.transitionTo;
        channel.wasUpdated = true;
    }
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
    if (channel.value == channel.transitionTo) return;

    int32_t totalChange = channel.transitionTo - channel.transitionFrom;
    uint32_t elapsed = (currentMillis - channel.startTime);
    elapsed = min(elapsed, (uint32_t)channel.targetDelay);

    uint32_t change = abs(totalChange) * elapsed / channel.targetDelay;
    uint32_t val = channel.transitionFrom;

    if (totalChange > 0)
        val += change;
    else
        val -= change;

    channel.value = uconstrain<uint32_t>(val, channel.transitionFrom, channel.transitionTo);
    channel.wasUpdated = true;
}

void updateBlink(Channel &channel)
{
    if (channel.blinkPresetIndex == -1 || channel.blinkPresetIndex < channel.activePresetIndex) return;

    const Preset preset = PROGMEM_getAnything(&channel.presets[channel.blinkPresetIndex]);
    const uint8_t patternSize = sizeof(preset.blinkPattern) * 8;
    int16_t interval = preset.blinkInterval / patternSize;
    uint32_t maxBlinkTime = interval * patternSize * preset.blinkCount;
    uint32_t elapsed = currentMillis - channel.blinkStartTime;

    if (elapsed > maxBlinkTime)
    {
        channel.blinkPhase = 0;
        if (onBlinkPhaseChanged(channel)) startFade(channel, getChannelValue(channel));
        return;
    }

    uint8_t blinkPatternStep = elapsed / interval % patternSize;
    bool patternIsHigh = preset.blinkPattern & (1 << patternSize - 1 - blinkPatternStep);

    if (channel.blinkPhase == patternIsHigh) return;
    channel.blinkPhase = patternIsHigh;
    if (onBlinkPhaseChanged(channel)) startFade(channel, getChannelValue(channel));
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
