#pragma once

#include <Arduino.h>
#include "types/infraredData.h"

// Remote control codes
#include "remotes/RM-X155.h"

/*
 * Specify which protocol(s) should be used for decoding.
 * If no protocol is defined, all protocols (except Bang&Olufsen) are active.
 * This must be done before the #include <IRremote.hpp>
 */
//#define DECODE_DENON        // Includes Sharp
//#define DECODE_JVC
//#define DECODE_KASEIKYO
//#define DECODE_PANASONIC    // alias for DECODE_KASEIKYO
//#define DECODE_LG
//#define DECODE_NEC          // Includes Apple and Onkyo. To enable all protocols , just comment/disable this line.
//#define DECODE_SAMSUNG
// #define DECODE_SONY
//#define DECODE_RC5
//#define DECODE_RC6

//#define DECODE_BOSEWAVE
//#define DECODE_LEGO_PF
//#define DECODE_MAGIQUEST
//#define DECODE_WHYNTER
//#define DECODE_FAST

//#define DECODE_DISTANCE_WIDTH // Universal decoder for pulse distance width protocols
//#define DECODE_HASH         // special decoder for all protocols

//#define DECODE_BEO          // This protocol must always be enabled manually, i.e. it is NOT enabled if no protocol is defined. It prevents decoding of SONY!

//#define DEBUG               // Activate this for lots of lovely debug output from the decoders.

//#define USE_THRESHOLD_DECODER  // May give slightly better results especially for jittering signals and protocols with short 1 pulses / pauses. Saves 110 bytes program memory.
//#define RAW_BUFFER_LENGTH  750 // For air condition remotes it may require up to 750. Default is 200.

#if defined(ESP32) || defined(ARDUINO_ARCH_RP2040) || defined(PARTICLE) || defined(ARDUINO_ARCH_MBED)
#define SEND_PWM_BY_TIMER // We do not have pin restrictions for this CPU's, so lets use the hardware PWM for send carrier signal generation
#else
# if defined(SEND_PWM_BY_TIMER)
#undef IR_SEND_PIN // SendPin is determined by timer! This avoids warnings in IRremote.hpp and IRTimer.hpp
#  endif
#endif

#define IR_RECEIVE_PIN 5

void setupInfrared();
void updateInfrared();

void onInfraredPressed(InfraredData irData);
void onInfraredHeld(InfraredData irData);
void onInfraredReleased(InfraredData irData);
