#ifdef FSDIY_GCU478

#include "devices/Gcu478.h"

#include <devices/G1000nxi.h>
#include <components/PulsedEncoder.h>

#include "ComponentDefs.h"

using namespace admux;
using namespace std;

const String BACKLIGHT_VARIABLE = "Backlight";

vector<SpadButton> buttons = {
    // Numbers
    {1, "BTN_GCU_NUM_1", 18 },
    {2, "BTN_GCU_NUM_2", 20 },
    {3, "BTN_GCU_NUM_3", 22 },
    {4, "BTN_GCU_NUM_4", 24 },
    {5, "BTN_GCU_NUM_5", 26 },
    {6, "BTN_GCU_NUM_6", 28 },
    {7, "BTN_GCU_NUM_7", 19 },
    {8, "BTN_GCU_NUM_8", 21 },
    {9, "BTN_GCU_NUM_9", 30 },
    {10, "BTN_GCU_NUM_0", 15 },
    {11, "BTN_GCU_DEC", 11 },
    {12, "BTN_GCU_PM", 17 },

    // Letters
    {13, "BTN_GCU_LTR_A", 32 },
    {14, "BTN_GCU_LTR_B", 34 },
    {15, "BTN_GCU_LTR_C", 36 },
    {16, "BTN_GCU_LTR_D", 38 },
    {17, "BTN_GCU_LTR_E", 40 },
    {18, "BTN_GCU_LTR_F", 42 },
    {19, "BTN_GCU_LTR_G", 7, 0 },
    {20, "BTN_GCU_LTR_H", 8, 0 },
    {21, "BTN_GCU_LTR_I", 9, 0 },
    {22, "BTN_GCU_LTR_J", 10, 0 },
    {23, "BTN_GCU_LTR_K", 11, 0 },
    {24, "BTN_GCU_LTR_L", 44 },
    {25, "BTN_GCU_LTR_M", 46 },
    {26, "BTN_GCU_LTR_N", 47 },
    {27, "BTN_GCU_LTR_O", 48 },
    {28, "BTN_GCU_LTR_P", 50 },
    {29, "BTN_GCU_LTR_Q", 52 },
    {30, "BTN_GCU_LTR_R", 2, 0 },
    {31, "BTN_GCU_LTR_S", 3, 0 },
    {32, "BTN_GCU_LTR_T", 4, 0 },
    {33, "BTN_GCU_LTR_U", 5, 0 },
    {34, "BTN_GCU_LTR_V", 6, 0 },
    {35, "BTN_GCU_LTR_W", 9 },
    {36, "BTN_GCU_LTR_X", 7 },
    {37, "BTN_GCU_LTR_Y", 5 },
    {38, "BTN_GCU_LTR_Z", 3 },
    {39, "BTN_GCU_LTR_SPC", 0, 0 },
    {40, "BTN_GCU_LTR_BKSP", 1, 0 },

    // Pan
    {41, "BTN_GCU_RANGE_UP", 12 },
    {42, "BTN_GCU_RANGE_DOWN", 14 },
    {43, "BTN_GCU_RANGE_LEFT", 0 },
    {44, "BTN_GCU_RANGE_RIGHT", 6 },
    {45, "BTN_NAV_RANGE_PUSH", 4 },

    // Buttons
    {46, "BTN_GCU_FMS_SELECT", 13, 0 },
    {47, "BTN_GCU_COM_SELECT", 12, 0 },
    {48, "BTN_GCU_NAV_SELECT", 15, 0 },
    {49, "BTN_GCU_XPDR", 49 },
    {50, "BTN_GCU_DIRECT", A9 },
    {51, "BTN_GCU_MENU", A3 },
    {52, "BTN_GCU_FPL", A11 },
    {53, "BTN_GCU_PROC", A5 },
    {54, "BTN_GCU_CLR", A13 },
    {55, "BTN_GCU_ENT", A7 },

    // Encoder Push
    {56, "BTN_GCU_HDG_PUSH", A15 },
    {57, "BTN_GCU_FMS_PUSH", A2 },
    {58, "BTN_GCU_CRS_PUSH", 37 },
    {59, "BTN_GCU_ALT_PUSH", 43 },
    {60, "BTN_GCU_NAV_FF", A5 },
    {61, "BTN_GCU_COM_FF", A7 }
};


vector<SpadEncoder> rotaries = {
    {101,"ENC_FMS", OUTER, new PulsedEncoder(A0, A1)},
    {101,"ENC_FMS", INNER, new PulsedEncoder(A4, A6)},
    {102,"ENC_HDG", SINGLE, new PulsedEncoder(33, 35)},
    {103,"ENC_CRS", SINGLE, new PulsedEncoder(39, 41)},
    {104,"ENC_ALT", SINGLE, new PulsedEncoder(45, 53)},
    {105,"ENC_RP", SINGLE, new PulsedEncoder(8, 16)}
};

vector<SpadLed> leds = {
    { 1, A8,"LED_XPDR", false },
    { 2, A10,"LED_NAV", false },
    { 3, A12,"LED_FMS", false },
    { 4, A14,"LED_COM", false }
};

vector<Mux> muxers = {
    Mux(Pin(23, INPUT_PULLUP, PinType::Digital), Pinset(31, 29, 27, 25))
};

SpadBacklight buttonBacklight = { 11, 10, "BACKLIGHT", 100, 125, 100 };

vector<SpadButton> * Gcu478::getButtons() const { return &buttons; }
vector<SpadEncoder> * Gcu478::getEncoders() const { return &rotaries; }
vector<SpadLed> * Gcu478::getLeds() const { return &leds; }
vector<Mux> * Gcu478::getMuxers() const { return &muxers; }
SpadBacklight * Gcu478::getButtonBacklight() const { return &buttonBacklight; }

#endif
