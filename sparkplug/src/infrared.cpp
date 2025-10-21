#include "infrared.h"
#include <IRremote.hpp>

InfraredData previousInfraredData;
const int infraredHoldDelay = 150;
unsigned long previousInfraredMillis;
bool infraredHolding = false;

void setupInfrared()
{
    // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
    IrReceiver.begin(IR_RECEIVE_PIN);

    Serial.print(F("Ready to receive IR signals of protocols: "));
    printActiveIRProtocols(&Serial);
}

void updateInfrared()
{
    /*
     * Check if received data is available and if yes, try to decode it.
     * Decoded result is in the IrReceiver.decodedIRData structure.
     *
     * E.g. command is in IrReceiver.decodedIRData.command
     * address is in command is in IrReceiver.decodedIRData.address
     * and up to 32 bit raw data in IrReceiver.decodedIRData.decodedRawData
     */
    if (!IrReceiver.decode()) return;

    unsigned long currentMillis = millis();

    InfraredData currentIRData =
    {
        IrReceiver.decodedIRData.protocol,
        IrReceiver.decodedIRData.address,
        IrReceiver.decodedIRData.command
    };

    if (currentIRData.command == REMOTE_RELEASE)
    {
        if (previousInfraredData.command != 0)
        {
            if (infraredHolding)
            {
                infraredHolding = false;
                onInfraredReleased(previousInfraredData);
            }
            else
            {
                onInfraredPressed(previousInfraredData);
            }

            previousInfraredData = {};
            previousInfraredMillis = 0;
        }
    }
    else
    {
        // New command
        if (previousInfraredData.command != currentIRData.command)
        {
            previousInfraredData = currentIRData;
            previousInfraredMillis = currentMillis;
        }

        // When crossing hold threshold
        if (!infraredHolding &&
            previousInfraredData.command != 0 &&
            currentMillis - previousInfraredMillis > infraredHoldDelay
        )
        {
            infraredHolding = true;
            onInfraredHeld(currentIRData);
        }
    }

    IrReceiver.resume();
}

__attribute__((weak)) void onInfraredPressed(InfraredData irData)
{

}

__attribute__((weak)) void onInfraredHeld(InfraredData irData)
{

}
