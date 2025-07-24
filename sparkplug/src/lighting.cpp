#include "helpers/macros.h"
#include "helpers/progmem_readanything.h"

#include "lighting.h"

template <typename T>
constexpr auto uconstrain(T value, T b1, T b2)
{
    return constrain(value, min(b1, b2), max(b1, b2));
}

void setupChannel(Channel &channel)
{
    channel.presetsActive = new bool[channel.presetCount]();
    for (int i = 0; i < channel.presetCount; i++)
    {
        channel.presetsActive[i] = false;
    }
}

void setupChannels()
{
    for (int i = 0; i < channelsCount; i++)
    {
        Channel &channel = channels[i];
        setupChannel(channel);
    }
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
    for (int i = 0; i < modesCount; i++)
    {
        LightingMode &mode = modes[i];
        if (mode.nextState == -1) continue;
        if (onLightingModeChanged(i))
        {
            mode.currentState = mode.nextState;
            updatechannelValues(i);
        }
        mode.nextState = -1; // Maybe move this up to keep checking condition.
    }
}

__attribute__((weak)) bool onLightingModeChanged(int modeID)
{
    return true; // Parse mode change by default.
}

bool channelHasPresetWithModeID(Channel &channel, int modeID)
{
    for (int j = 0; j < channel.presetCount; j++)
    {
        const Preset preset = PROGMEM_getAnything(&channel.presets[j]);
        if (preset.modeID == modeID) return true;
    }

    return false;
}

void startFade(Channel &channel, uint16_t value, uint16_t fadeSpeed)
{
    channel.transitionFrom = channel.value;
    channel.transitionTo = value;

    if (channel.transitionFrom == value) return;

    uint16_t totalChange = abs(channel.transitionTo - channel.transitionFrom);
    channel.startTime = currentMillis;

    // When the fade speed should be constant.
    // channel.targetDelay = fadeSpeed * totalChange / 65536;

    // When the fade speed should be the same for every change.
    channel.targetDelay = fadeSpeed;

    // Instantly set channel to prevent fade and divide by zero.
    if (channel.targetDelay == 0)
    {
        uint16_t oldValue = channel.value;
        channel.value = channel.transitionTo;
        channel.wasUpdated = oldValue != channel.value;
    }
}

bool isPresetActive(SwopModes mode, uint16_t bufferIntensity, uint16_t presetIntensity)
{
    // TODO: we can really turn this into a shader with an `out` parameter.
    switch (mode)
    {
    case SwopModes::LTP:
        return true;
        break;
    case SwopModes::HTP:
        return (presetIntensity > bufferIntensity);
        break;
    case SwopModes::LoTP:
        return (presetIntensity < bufferIntensity);
        break;
    }

    return false;
}

void calculateChannelValue(Channel &channel)
{
    int16_t highestActivatedPresetIndex = -1;
    int16_t highestDeactivatedPresetIndex = -1;

    uint16_t targetValue = 0;
    int16_t highestEnabledBlinkIndex = -1;

    for (int i = 0; i < channel.presetCount; i++)
    {
        uint16_t presetIntensity = 0;
        bool presetActive = false;
        const Preset preset = PROGMEM_getAnything(&channel.presets[i]);

        if (modes[preset.modeID].currentState > 0)
        {
            // Scale preset intensity by mode state.
            presetIntensity = preset.intensity * modes[preset.modeID].currentState / 255;
            // Convert 8-bit to 16-bit.
            presetIntensity = presetIntensity << 8 | presetIntensity;

            if (preset.mode == PresetModes::Blink)
            {
                highestEnabledBlinkIndex = i;
                // Determines wheter or not the blink preset influences the channel value.
                // Should only happen on positive blink phase.
                if (channel.blinkPhase)
                {
                    presetActive = isPresetActive(preset.priorityMode, targetValue, presetIntensity);
                }
                else
                {
                    presetActive = false;
                }
            }
            else
            {
                presetActive = isPresetActive(preset.priorityMode, targetValue, presetIntensity);
            }
        }

        if (presetActive != channel.presetsActive[i])
        {
            channel.presetsActive[i] = presetActive;

            if (presetActive)
            {
                highestActivatedPresetIndex = i;
            }
            else
            {
                highestDeactivatedPresetIndex = i;
            }
        }

        if (presetActive)
        {
            targetValue = presetIntensity;
        }
    }

    if (highestEnabledBlinkIndex > -1 && channel.blinkPresetIndex != highestEnabledBlinkIndex)
    {
        // Starting blink.
        channel.blinkStartTime = currentMillis;
        channel.blinkPhase = 0;
    }

    channel.blinkPresetIndex = highestEnabledBlinkIndex;
    int16_t presetIndex = max(highestActivatedPresetIndex, highestDeactivatedPresetIndex);
    const Preset preset = PROGMEM_getAnything(&channel.presets[presetIndex]);
    int32_t fadeSpeed = channel.presetsActive[presetIndex] ? preset.fadeSpeedRising : preset.fadeSpeedFalling;
    startFade(channel, targetValue, fadeSpeed);
}

void updatechannelValues(int modeID)
{
    for (int i = 0; i < channelsCount; i++)
    {
        Channel &channel = channels[i];
        if (channelHasPresetWithModeID(channel, modeID)) calculateChannelValue(channel);
    }
}

void updateChannelValues()
{
    for (int i = 0; i < channelsCount; i++)
    {
        Channel &channel = channels[i];
        calculateChannelValue(channel);
    }
}

void updateChannels()
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

    uint16_t oldValue = channel.value;
    // TODO: Seems bad...
    channel.value = uconstrain<uint16_t>(val, channel.transitionFrom, channel.transitionTo);
    channel.wasUpdated = oldValue != channel.value;
}

void updateBlink(Channel &channel)
{
    if (channel.blinkPresetIndex == -1 || channel.blinkPresetIndex < channel.activePresetIndex) return;

    const Preset preset = PROGMEM_getAnything(&channel.presets[channel.blinkPresetIndex]);
    const uint8_t patternSize = sizeof(preset.blinkPattern) * 8;
    int16_t interval = preset.blinkInterval / patternSize;

    // TODO: Does the blinkCount actually work!?
    uint32_t maxBlinkTime = preset.blinkInterval * preset.blinkCount;
    uint32_t elapsed = currentMillis - channel.blinkStartTime;

    // TODO: Is this required? Is this only required for blinkcount?
    // Maybe add check if blinkphase is non-zero first?
    // Feels like this should be rewritten.
    if (elapsed > maxBlinkTime)
    {
        channel.blinkPhase = 0;
        if (onBlinkPhaseChanged(channel))
        {
            calculateChannelValue(channel);
        }
        return;
    }

    uint8_t blinkPatternStep = elapsed / interval % patternSize;
    bool patternIsHigh = preset.blinkPattern & (1 << patternSize - 1 - blinkPatternStep);

    if (channel.blinkPhase == patternIsHigh) return;
    channel.blinkPhase = patternIsHigh;
    if (onBlinkPhaseChanged(channel))
    {
        calculateChannelValue(channel);
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
