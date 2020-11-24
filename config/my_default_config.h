// This is a sample configuration file.
// This saber has:
//   o Proffieboard hardware.
//   o Two buttons
//   o A neopixel blade on LED 1-2-3 and neopixel data 1.

#ifdef CONFIG_TOP
// #include "proffieboard_v2_config.h"
#include "proffieboard_config.h"
#define NUM_BLADES 1
#define NUM_BUTTONS 2
#define VOLUME 1500 // rear facing SE speaker-1500, forward facing SE speaker-1300
const unsigned int maxLedsPerStrip = 144;
#define CLASH_THRESHOLD_G 3.0 // rear facing speaker-2.0, forward facing speaker-3.0
#define ENABLE_AUDIO
#define ENABLE_MOTION
#define ENABLE_WS2811 
#define ENABLE_SD
#define ENABLE_SERIAL
#define KEEP_SAVEFILES_WHEN_PROGRAMMING
#define SAVE_STATE // saves preset, vol and color change
// #define SAVE_PRESET
// define SAVE_VOLUME
// #define SAVE_COLOR_CHANGE
// #define DISABLE_COLOR_CHANGE
#define IDLE_OFF_TIME 16000 // time before deep sleep 
//
//                                                 Bluetooth
//#define BLE_PASSWORD "625656" // Max 32 characters.
//#define BLE_NAME "Graflex1" // Max 9 characters
//#define BLE_SHORTNAME "Saber"
//#define ENABLE_SSD1306 // 
#define SHARED_POWER_PINS
#define ENABLE_POWER_FOR_ID PowerPINS<bladePowerPin1, bladePowerPin2, bladePowerPin3>
#define DISABLE_DIAGNOSTIC_COMMANDS
#define COLOR_CHANGE_DIRECT // each click changes colors
//
//                                          FET263 Buttons defines
//
//                                          Battle Mode.. Pick one or none
//#define FETT263_BATTLE_MODE_ALWAYS_ON //Battle Mode is always on, toggle controls deactivated OR
#define FETT263_BATTLE_MODE_START_ON //Battle Mode is active with each ignition by default but can be toggled using Aux + Swing control 
//
//                                                   Misc
#define FETT263_LOCKUP_DELAY 200
#define FETT263_SWING_ON_SPEED 400 // 
#define FETT263_BM_DISABLE_OFF_BUTTON
//#define FETT263_FORCE_PUSH
#define FETT263_FORCE_PUSH_ALWAYS_ON
// #define FETT263_FORCE_PUSH_LENGTH 5
#define FETT263_MULTI_PHASE
#define MOTION_TIMEOUT 60 * 15 * 1000
//                                           swing on.... pick one
#define FETT263_SWING_ON
//#define FETT263_SWING_ON_PREON
//#define FETT263_SWING_ON_NO_BM
//                                             Twist... pick one
#define FETT263_TWIST_OFF
//#define FETT263_TWIST_ON
//#define FETT263_TWIST_ON_PREON
//#define FETT263_TWIST_ON_NO_BM
//
//                                              Stab... pick one
//#define FETT263_STAB_ON
//#define FETT263_STAB_ON_PREON
//#define FETT263_STAB_ON_NO_BM
//
//                                              Thrust... pick one
//#define FETT263_THRUST_ON
//#define FETT263_THRUST_ON_PREON
//#define FETT263_THRUST_ON_NO_BM

#endif

#ifdef CONFIG_PROP
// #include "../props/saber_sa22c_buttons.h"
#include "../props/saber_fett263_buttons.h"
// #include "../props/saber_shtok_buttons.h"
#endif

#ifdef CONFIG_PRESETS

Preset presets[] = {
#include "styles/Sith.h" // Add Sith styles    
//#include "styles/HeroBlades.h" // Add hero styles with crystal chamber and 2 control box LEDs
#include "styles/JediBlades.h" // Add Jedi styles
//#include "styles/Grievous.h" // Add Grievous styles
#include "styles/StockBlades.h"  // Add Kyber workshop styles  
};

BladeConfig blades[] = {
{ 645, WS2811BladePtr<125, WS2811_ACTUALLY_800kHz | WS2811_GRB, bladePin, PowerPINS<bladePowerPin1, bladePowerPin2, bladePowerPin3>>(), CONFIGARRAY(presets) },   // Standard VV 34" blade
{ 14, WS2811BladePtr<69, WS2811_ACTUALLY_800kHz | WS2811_GRB, bladePin, PowerPINS<bladePowerPin1, bladePowerPin2, bladePowerPin3>>(), CONFIGARRAY(presets) }, // My 19" demo blade
};
#endif

#ifdef CONFIG_BUTTONS
Button PowerButton(BUTTON_POWER, powerButtonPin, "pow");
Button AuxButton(BUTTON_AUX, auxPin, "aux");
#endif

//
// Prop file bottons
//
// Fett263 Buttons with Gesture Controls and Battle Mode with Smart Lockup
//
// Includes Gesture Controls, "Battle Mode" with "Smart Lockup", "Multi-Blast" Mode (to enable Swing Blast control)
// "Multi-Phase" Mode, "On Demand Power Save", "On Demand Battery Level", "Fast On" Ignition (no preon) and SA22C volume menu
//
// DEFAULT 2 BUTTON CONTROLS (PWR and AUX):
//
// "Battle Mode" - hold AUX and Swing while blade is ON to toggle mode ON/OFF
// Ignite (ON) - click PWR while OFF (Swing On, Twist On and Stab On available with defines)
// Muted Ignition (ON) - double click PWR while OFF
// Retract (OFF) - click PWR while ON (disabled during swinging, Twist Off available with define)
// Play/Stop Music Track - hold and release PWR while OFF or hold and release PWR while ON and pointing blade straight up
// Blast - click AUX while ON
// Multi-Blast Mode - hold and release AUX while ON to enter mode, Swing to initiate Blasts, click Aux to exit mode
//                    lockup, clash, stab, melt, drag or any button presses automatically exits mode
// Clash - clash blade while ON
//         in Battle Mode clash and pull away quickly for "Clash" (requires BEGIN_LOCKUP and END_LOCKUP styles)
// Lockup - hold AUX and clash while ON
//          in Battle Mode clash and hold steady to activate, pull away to disengage
// Drag - hold AUX and stab down while ON
//        in Battle Mode stab down, pull away to disengage
// Melt - hold PWR (or AUX) and thrust forward and clash while ON
//        in Battle Mode thrust and clash to engage, pull away to disengage
// Lightning Block - hold PWR and click AUX while ON
// Force - hold and release PWR while ON (not pointing straight up)
// Stab - thrust forward and clash blade while ON - deactivated in Battle Mode
// Power Save - hold Aux and click PWR while ON (pointing up) to use Power Save (requires style)
// Color Change - hold AUX and click PWR while ON (parallel or down) to enter CCWheel,
//                turn hilt to rotate through colors, click PWR to select/exit
//                if using COLOR_CHANGE_DIRECT each button press advances one Color at a time
// Next Preset - click AUX while OFF (parallel or up)
// Previous Preset - click Aux while OFF (pointing down)
// MULTI_PHASE Next Preset - hold AUX and TWIST while ON (use define to enable)
// MULTI_PHASE Previous Preset - hold PWR and TWIST while ON (use define to enable)
// Battery Level - hold AUX and click PWR while OFF (requires style)
// Enter SA22C Volume Menu - hold and release AUX while OFF
// Volume Up (10% increment, 100% max) - click PWR while in Volume Menu while OFF
// Volume Down (10% increment) - click AUX while in Volume Menu while OFF
// Exit Volume Menu - hold and release AUX while in Volume Menu while OFF
//