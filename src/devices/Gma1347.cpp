#ifdef FSDIY_GMA1347

#include <vector>
#include <devices/Gma1347.h>
#include <components/PulsedEncoder.h>

using namespace std;

vector<SpadButton> buttons = {
  {1, "BTN_MIC1", 18 },
  {2, "BTN_COM1", 16 },
  {3, "BTN_MIC2", 14 },
  {4, "BTN_COM2", 12 },
  {5, "BTN_MIC3", 10 },
  {6, "BTN_COM3", 8 },
  {7, "BTN_COM_TOG", 6 },
  {8, "BTN_TEL", 35 },
  {9, "BTN_PA", 2 },
  {10, "BTN_SPKR", 39 },
  {11, "BTN_MKR", 33 },
  {12, "BTN_SENS", 43 },
  {13, "BTN_DME", 37 },
  {14, "BTN_NAV1", 49 },
  {15, "BTN_ADF", 41 },
  {16, "BTN_NAV2", 47 },
  {17, "BTN_AUX", 45 },
  {18, "BTN_MANSQ", 48},
  {19, "BTN_PLAY", 44 },
  {20, "BTN_PILOT", 46 },
  {21, "BTN_COPLT", 40 },
  {22, "BTN_REVERSION", 42 },
  {23, "BTN_ENCODER", 36}
};

vector<SpadEncoder> rotaries = {
  {101,"ENC_PASS", OUTER, new PulsedEncoder(A14,32, 2) },
  {101,"ENC_PILOT", INNER, new PulsedEncoder(34, 38, 2) }
};

vector<SpadLed> leds = {
  {1, 3,  "LED_MIC1"},
  {2, 5,  "LED_COM1" },
  {3, 7, "LED_MIC2" },
  {4, 9, "LED_COM2" },
  {5, 11, "LED_MIC3" },
  {6, 13, "LED_COM3" },
  {7, 15, "LED_COM_TOG" },
  {8, 17, "LED_TEL" },
  {9, 19, "LED_PA" },
  {10,21, "LED_SPKR" },
  {11,23,  "LED_MKR" },
  {12,25,  "LED_SENS" },
  {13,31, "LED_DME" },
  {14,28, "LED_NAV1" },
  {15,29, "LED_ADF" },
  {16,26, "LED_NAV2" },
  {17,27, "LED_AUX" },
  {18,30, "LED_MANSQ" },
  {19,24, "LED_PLAY" },
  {20,20, "LED_PILOT" },
  {21,22, "LED_COPLT" }
};

vector<SpadButton> * Gma1347::getButtons() const { return &buttons; }
vector<SpadEncoder> * Gma1347::getEncoders() const { return &rotaries; }
vector<SpadLed> * Gma1347::getLeds() const { return &leds; }

#endif