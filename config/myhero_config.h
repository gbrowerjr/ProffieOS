// myhero_config.h - 3.0
//
// This Hero saber has:
//   o Proffie v2.2 hardware.
//   o Aux and a regular button
//   o Uses alternate SA22c buttons
//   o An 7-pin TCSS blade connector
//   o All presets are stored in /styles
//   o 28mm WOW speaker
//   o Multiple blade length selection
//   o 2 Neopixel Crystal Chamber
//   o Seperate 2x White Standard LEDs  in control box w/ colored windows

#ifdef CONFIG_TOP
#include "proffieboard_v2_config.h"
// #include "proffieboard_config.h"
#define NUM_BLADES 3
// #define SUB_BLADES 2
#define NUM_BUTTONS 2
#define VOLUME 1000
const unsigned int maxLedsPerStrip = 144;
#define CLASH_THRESHOLD_G 2.0
#define ENABLE_AUDIO
#define ENABLE_MOTION
#define ENABLE_WS2811
#define ENABLE_SD
#define ENABLE_SERIAL
// #define KEEP_SAVEFILES_WHEN_PROGRAMMING
//#define SAVE_STATE
// #define SAVE_PRESET
// define SAVE_VOLUME
// #define SAVE_COLOR_CHANGE
// #define DISABLE_COLOR_CHANGE
#define IDLE_OFF_TIME 10000
// #define BLE_PASSWORD "625656" // Max 32 characters.
// #define BLE_NAME "Graflex1" // Max 9 characters
//#define BLE_SHORTNAME "Saber"
//#define ENABLE_SSD1306
#define SHARED_POWER_PINS
#define ENABLE_POWER_FOR_ID PowerPINS<bladePowerPin1, bladePowerPin2, bladePowerPin3>
#define DISABLE_DIAGNOSTIC_COMMANDS
#endif

#ifdef CONFIG_PROP
// #include "../props/saber_sa22c_buttons.h"
// #include "../props/saber_fett263_buttons.h"
// #include "../props/saber_shtok_buttons.h"
#endif

#ifdef CONFIG_PRESETS

Preset presets[] = {
#include "styles/HeroBlades.h"    
};

BladeConfig blades[] = {
// { 0, 
// SubBlade(2, 125, WS281XBladePtr<127, bladePin, Color8::GRB, PowerPINS<bladePowerPin2, bladePowerPin3>>()),
// SubBlade(0, 1, NULL),
// SimpleBladePtr<CreeXPE2WhiteTemplate<550>, NoLED, NoLED, NoLED, bladePowerPin4, -1, -1, -1>(),
// SimpleBladePtr<CreeXPE2WhiteTemplate<550>, NoLED, NoLED, NoLED, bladePowerPin5, -1, -1, -1>(),
//  CONFIGARRAY(presets)},
// };

 { 0,
    WS281XBladePtr<127, bladePin, Color8::GRB, PowerPINS<bladePowerPin2, bladePowerPin3> >(),
    SimpleBladePtr<CreeXPE2WhiteTemplate<550>, NoLED, NoLED, NoLED, bladePowerPin4, -1, -1, -1>(),
    SimpleBladePtr<CreeXPE2WhiteTemplate<550>, NoLED, NoLED, NoLED, bladePowerPin5, -1, -1, -1>(),
   CONFIGARRAY(presets)},
};
#endif
 
#ifdef CONFIG_BUTTONS
Button PowerButton(BUTTON_POWER, powerButtonPin, "pow");
Button AuxButton(BUTTON_AUX, auxPin, "aux");
#endif