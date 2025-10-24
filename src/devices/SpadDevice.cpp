#include <Mux.h>
#include <devices/SpadDevice.h>
#include <SpadProtocol.h>

using namespace admux;
using namespace std;

static SpadDevice * s_instance = nullptr;

static void onSpadStateCallbackWrapper(const bool state) { s_instance->setIsSpadStarted(state); }
static void onVirtualPowerChangedWrapper(const bool powerState) { s_instance->onVirtualPowerChanged(powerState); }
static void onInputCreationWrapper() { s_instance->onInputCreation(); }
static void onButtonBacklightChangedWrapper(const int16_t backlightValue) { s_instance->onButtonBacklightChanged(backlightValue); }
static void onLedBacklightChangedWrapper(const int16_t backlightValue) { s_instance->onLedBacklightChanged(backlightValue); }
static void onDeviceLedChangedWrapper(const byte id, const bool value) { s_instance->onDeviceLedChanged(id, value); }

SpadDevice::SpadDevice() : _protocol(new SpadProtocol(this)) { s_instance = this; }
SpadDevice::~SpadDevice() = default;

void SpadDevice::setup() const
{
  const auto buttons = getButtons();
  const auto leds = getLeds();
  const auto buttonBacklight = getButtonBacklight();
  const auto ledBacklight = getLedBacklight();

  for (const auto& button : *buttons) {
    button.initializePin();
  }

  for (auto& led: *leds) {
    led.initializePin();
  }

  if (buttonBacklight != nullptr) {
    buttonBacklight->initializePin();
    _protocol->setButtonBacklightCallback(buttonBacklight->channelId, &onButtonBacklightChangedWrapper);
  }

  if (ledBacklight != nullptr) {
    ledBacklight->initializePin();
    _protocol->setLedBacklightCallback(ledBacklight->channelId, &onLedBacklightChangedWrapper);
  }

  _protocol->setVirtualPowerCallback(&onVirtualPowerChangedWrapper);
  _protocol->setInputCreationCallback(&onInputCreationWrapper);
  _protocol->setDeviceLedCallback(&onDeviceLedChangedWrapper);
  _protocol->setSpadStateCallback(&onSpadStateCallbackWrapper);
}

void SpadDevice::loop() const {
  if (isStarted)
  {
    checkAllButtons();
    checkAllEncoders();
  }

  _protocol->feedInSerialData();
}

std::vector<SpadButton> * SpadDevice::getButtons() const {
  static std::vector<SpadButton> emptyButtons;
  return &emptyButtons;
}

std::vector<SpadLed> * SpadDevice::getLeds() const {
  static std::vector<SpadLed> emptyLeds;
  return &emptyLeds;
}

std::vector<SpadEncoder> * SpadDevice::getEncoders() const {
  static std::vector<SpadEncoder> emptyEncoders;
  return &emptyEncoders;
}

std::vector<Mux> * SpadDevice::getMuxers() const {
  static std::vector<Mux> emptyMux;
  return &emptyMux;
}

SpadBacklight * SpadDevice::getButtonBacklight() const {
  return nullptr;
}

SpadBacklight * SpadDevice::getLedBacklight() const {
  return nullptr;
}

// Component Processing
void SpadDevice::checkAllButtons() const {
  const auto buttons = getButtons();

  for (auto& button : *buttons) {
    button.update(_protocol, getMuxers());
  }
}

void SpadDevice::checkAllEncoders() const {
  const auto encoders = getEncoders();

  for (auto & encoder : *encoders) {
    encoder.update(_protocol);
  }
}

// Protocol Callbacks
void SpadDevice::onVirtualPowerChanged(const bool powerState) {
  if (powerState) {
    _protocol->sendDebugMessage(F("Powering On!"));
  } else {
    _protocol->sendDebugMessage(F("Powering off...."));
  }

  setPowerState(powerState);
  getButtonBacklight()->update();
  getLedBacklight()->update();
}

void SpadDevice::onInputCreation() const {
  if (hasVirtualPower()) {
    _protocol->createVirtualPower();
  }

  for (const auto& button : *getButtons()) {
    _protocol->createButton(&button);
  }

  for (const auto& encoder : *getEncoders()) {
    _protocol->createEncoder(&encoder);
  }

  for (const auto& led : *getLeds()) {
    _protocol->createLED(&led);
  }
}

void SpadDevice::onButtonBacklightChanged(const int16_t backlightValue) const {
  const auto buttonBacklight = getButtonBacklight();

  _protocol->sendDebugMessage(F("Button backlight changed"));

  if (buttonBacklight != nullptr) {
    buttonBacklight->setValue(backlightValue, getPowerState());
  }
}

void SpadDevice::onLedBacklightChanged(const int16_t backlightValue) const {
  const auto ledBacklight = getLedBacklight();

  _protocol->sendDebugMessage(F("Led backlight changed"));

  if (ledBacklight != nullptr) {
    ledBacklight->setValue(backlightValue, getPowerState());
  }
}

void SpadDevice::onDeviceLedChanged(const byte id, const bool value) const {
  const auto leds = getLeds();

  _protocol->sendDebugMessage(F("Device led changed"));

  for (auto &led : *leds) {
    if (led.id == id) {
      led.setValue(value);
      return;
    }
  }
}