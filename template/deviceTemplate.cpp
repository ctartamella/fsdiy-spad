
#ifdef FSDIY_DEVICENAME

#include <vector>
#include "deviceTemplate.h"

#include "components/PulsedEncoder.h"

using namespace std;

// Use this space to define your hardware arrays

vector<SpadButton> buttons = {
    { 1, "BTN_DUMMY", 2 }
};

vector<SpadEncoder> encoders = {
    { 101, "ENC_DUAL", OUTER, new PulsedEncoder(3, 5), },
    { 101, "ENC_DUAL", INNER, new PulsedEncoder(7, 9), },
    { 102, "ENC_SINGLE", SINGLE, new PulsedEncoder(11, 13) }
};

std::vector<SpadButton> * DeviceTemplate::getButtons() const { return &buttons; }
std::vector<SpadEncoder> * DeviceTemplate::getEncoders() const { return &rotaries; }

#endif