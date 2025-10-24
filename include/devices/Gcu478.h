#pragma once

#ifdef FSDIY_GCU478

#include <devices/SpadDevice.h>

class Gcu478 final : public SpadDevice {

protected:
    std::vector<SpadButton> * getButtons() const override;
    std::vector<SpadEncoder> * getEncoders() const override;
    std::vector<SpadLed> * getLeds() const override;
    std::vector<admux::Mux> * getMuxers() const override;
    SpadBacklight * getButtonBacklight() const override;

    bool hasVirtualPower() const override { return true;}

public:
    explicit Gcu478() = default;
};

#endif