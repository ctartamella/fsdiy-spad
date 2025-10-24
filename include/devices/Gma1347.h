#pragma once

#ifdef FSDIY_GMA1347

#include <devices/SpadDevice.h>

class Gma1347 final : public SpadDevice {

protected:
  std::vector<SpadButton> * getButtons() const override;
  std::vector<SpadEncoder> * getEncoders() const override;
  std::vector<SpadLed> * getLeds() const override;

  bool hasVirtualPower() const override { return true;}

public:
  explicit Gma1347() = default;
};

#endif