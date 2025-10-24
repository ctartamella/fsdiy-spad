#ifdef FSDIY_G1000

#include <devices/G1000nxi.h>
#include <components/PulsedEncoder.h>

using namespace admux;
using namespace std;

const String BACKLIGHT_VARIABLE = "Backlight";

vector<SpadButton> buttons = {
// LEFT SIDE
    {1, "BTN_G1000_NAV_VOL_CLICK", 0, 0 },
    {2, "BTN_G1000_NAV_FF", 1, 0 },
    {3, "BTN_G1000_NAV_TOG", 2, 0 },
    {4, "BTN_G1000_HDG_SYNC", 58 },
    {5, "BTN_G1000_AP", 60 },
    {6, "BTN_G1000_FD",40 },
    {7, "BTN_G1000_HDG", 62 },
    {8, "BTN_G1000_ALT", 42 },
    {9, "BTN_G1000_NAV", 32 },
    {10, "BTN_G1000_VNV", 44 },
    {11, "BTN_G1000_APR", 34 },
    {12, "BTN_G1000_BC", 46 },
    {13, "BTN_G1000_VS", 36 },
    {14, "BTN_G1000_NOSE_UP", 47 },
    {15, "BTN_G1000_FLC", 38 },
    {16, "BTN_G1000_NOSE_DN", 48 },
    {17, "BTN_G1000_ALT_SEL", 3, 0 },
// RIGHT SIDE
    {18, "BTN_G1000_COM_VOL_CLICK", 23 },
    {19, "BTN_G1000_COM_FF", 25 },
    {20, "BTN_G1000_COM_TOG", 28 },
    {21, "BTN_G1000_CRS_SYNC", 18 },
    {22, "BTN_G1000_PAN_SYNC", 3 },
    {23, "BTN_G1000_PAN_LEFT", 9 },
    {24, "BTN_G1000_PAN_UP", 11 },
    {25, "BTN_G1000_PAN_RIGHT", 5 },
    {26, "BTN_G1000_PAN_DN", 7 },
    {27, "BTN_G1000_DIRECT", 16 },
    {28, "BTN_G1000_MENU", 69 },
    {29, "BTN_G1000_FPL", 14 },
    {30, "BTN_G1000_PROC", 8 },
    {31, "BTN_G1000_CLR", 12 },
    {32, "BTN_G1000_ENT", 67 },
    {33, "BTN_G1000_FMS", 49 },
// BOTTOM
    {34, "BTN_G1000_SOFT_1", 4, 0 },
    {35, "BTN_G1000_SOFT_2", 5, 0 },
    {36, "BTN_G1000_SOFT_3", 6, 0 },
    {37, "BTN_G1000_SOFT_4", 7, 0 },
    {38, "BTN_G1000_SOFT_5", 8, 0 },
    {39, "BTN_G1000_SOFT_6", 9, 0 },
    {40, "BTN_G1000_SOFT_7", 10, 0 },
    {41, "BTN_G1000_SOFT_8", 11, 0 },
    {42, "BTN_G1000_SOFT_9", 12, 0 },
    {43, "BTN_G1000_SOFT_10", 13, 0 },
    {44, "BTN_G1000_SOFT_11", 14, 0 },
    {45, "BTN_G1000_SOFT_12", 15, 0 }
};

vector<SpadEncoder> rotaries = {
    {101,"ENC_G1000_NAV_VOL", SINGLE, new PulsedEncoder(65, 63)},
    {102,"ENC_G1000_NAV", OUTER, new PulsedEncoder(55, 57)},
    {102,"ENC_G1000_NAV", INNER, new PulsedEncoder(59, 61)},
    {103,"ENC_G1000_HDG", SINGLE, new PulsedEncoder(54, 56)},
    {104,"ENC_G1000_ALT", OUTER, new PulsedEncoder(51, 53)},
    {104,"ENC_G1000_ALT", INNER, new PulsedEncoder(52, 50)},
    {105,"ENC_G1000_COM_VOL", SINGLE, new PulsedEncoder(19, 21)},
    {106,"ENC_G1000_COM", OUTER, new PulsedEncoder(30, 31)},
    {106,"ENC_G1000_COM", INNER, new PulsedEncoder(29, 27)},
    {107,"ENC_G1000_CRS_BARO", OUTER, new PulsedEncoder(20, 22)},
    {107,"ENC_G1000_CRS_BARO", INNER, new PulsedEncoder(24, 26)},
    {108,"ENC_G1000_RANGE", SINGLE, new PulsedEncoder(17, 15)},
    {109,"ENC_G1000_FMS", OUTER, new PulsedEncoder(45, 43)},
    {109,"ENC_G1000_FMS", INNER, new PulsedEncoder(2, 4)}
};

vector<Mux> muxers = {
    Mux(Pin(33, INPUT_PULLUP, PinType::Digital), Pinset(41, 39, 37, 35))
};

SpadBacklight buttonBacklight = { 11, 6, "BTN_BACKLIGHT", 100, 125, 150 };
SpadBacklight ledBacklight = { 12, 10, "LED_BACKLIGHT", 0, 255, 0 };

vector<SpadButton> * G1000Nxi::getButtons() const { return &buttons; }
vector<SpadEncoder> * G1000Nxi::getEncoders() const { return &rotaries; }
vector<Mux> * G1000Nxi::getMuxers() const { return &muxers; }
SpadBacklight * G1000Nxi::getButtonBacklight() const { return &buttonBacklight; }
SpadBacklight * G1000Nxi::getLedBacklight() const { return &ledBacklight; }

#endif
