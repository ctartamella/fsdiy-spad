#include <map>
#include <SpadProtocol.h>
#include <devices/SpadDevice.h>

#define INIT_COMMAND "INIT"
#define SCANSTATE_COMMAND "SCANSTATE"
#define PING_COMMAND "PING"
#define CONFIG_COMMAND "CONFIG"
#define START_COMMAND "START"
#define END_COMMAND "END"
#define VIRTUALPOWER_COMMAND "VIRTUALPOWER"
#define CONNECT_COMMAND "CONNECT"
#define DISCONNECT_COMMAND "DISCONNECT"

SpadProtocol * s_instance = nullptr;

static void onProtocolCommandWrapper() { s_instance->onProtocolCommand(); }
static void onSpadEventWrapper() { s_instance->onSpadEvent(); }
static void onDeviceLedWrapper() { s_instance->onDeviceLed(); }
static void onButtonBacklightChangedWrapper() { s_instance->onButtonBacklightChanged(); }
static void onLedBacklightChangedWrapper() { s_instance->onLedBacklightChanged(); }

SpadProtocol::SpadProtocol(SpadDevice *device)
    : _messenger(new CmdMessenger(Serial)), _device(device) {
    s_instance = this;

    _messenger->attach(0, &onProtocolCommandWrapper);
    _messenger->attach(2, &onSpadEventWrapper);
    _messenger->attach(6, &onDeviceLedWrapper);
}

void SpadProtocol::setVirtualPowerCallback(const VirtualPowerCallback callback) {
    _virtualPowerCallback = callback;
}

void SpadProtocol::setSpadStateCallback(const SpadStateCallback callback) {
    _spadStateCallback = callback;
}

void SpadProtocol::setInputCreationCallback(const InputCreationCallback callback) {
    _inputCreationCallback = callback;
}

void SpadProtocol::setDeviceLedCallback(const DeviceLedCallback callback) {
    _deviceLedCallback = callback;
}

void SpadProtocol::setButtonBacklightCallback(const int channelId, const DeviceDataCallback callback) {
    _buttonBacklightCallback = callback;
    _messenger->attach(channelId, &onButtonBacklightChangedWrapper);
}

void SpadProtocol::setLedBacklightCallback(const int channelId, const DeviceDataCallback callback) {
    _ledBacklightCallback = callback;
    _messenger->attach(channelId, &onLedBacklightChangedWrapper);
}

void SpadProtocol::feedInSerialData() const {
    _messenger->feedinSerialData();
}

void SpadProtocol::sendCommand(const int commandId, const String &command) const {
    _messenger->sendCmd(commandId, command);
}

void SpadProtocol::onProtocolCommand() const
{
    const char *szRequest = readString();

    if (strcmp(szRequest, INIT_COMMAND) == 0) {
        sendInitResponse();
        return;
    }

    if (strcmp(szRequest, SCANSTATE_COMMAND) == 0) {
        sendScanResponse();
        return;
    }

    if (strcmp(szRequest, PING_COMMAND) == 0) {
        sendPingResponse();
        return;
    }

    if (strcmp(szRequest, CONFIG_COMMAND) == 0) {
        sendConfigResponse();
    }
}

void SpadProtocol::onSpadEvent() const
{
    const char *szEvent = readString();

    // SPAD tells the device, it's ok to send input now
    if (strcmp(szEvent, START_COMMAND) == 0) {
        _spadStateCallback(true);
        return;
    }

    // SPAD tells the device it will exit now
    if (strcmp(szEvent, END_COMMAND) == 0) {
        _spadStateCallback(false);
        return;
    }

    if (strcmp(szEvent, VIRTUALPOWER_COMMAND) == 0 && _virtualPowerCallback != nullptr) {
        const auto powerState = readBoolean();
        _virtualPowerCallback(powerState);
        return;
    }

    if (strcmp(szEvent, CONNECT_COMMAND) == 0) {
        _virtualPowerCallback(true);
        return;
    }

    if (strcmp(szEvent, DISCONNECT_COMMAND) == 0) {
        _virtualPowerCallback(false);
        return;
    }
}

void SpadProtocol::onDeviceLed() const {
    const auto ledID = readInt32();       // Led ID
    const auto ledVal = readBoolean();     // Led value

    if (_deviceLedCallback != nullptr) {
        _deviceLedCallback(ledID, ledVal);
    }
}

void SpadProtocol::onButtonBacklightChanged() const {
    const auto backlightValue = readInt16();
    if (_buttonBacklightCallback != nullptr) {
        _buttonBacklightCallback(backlightValue);
    }
}

void SpadProtocol::onLedBacklightChanged() const {
    const auto backlightValue = readInt16();
    if (_ledBacklightCallback != nullptr) {
        _ledBacklightCallback(backlightValue);
    }
}

void SpadProtocol::sendInitResponse() const {
    _messenger->sendCmdStart(0);
    _messenger->sendCmdArg("SPAD");
    _messenger->sendCmdArg(_device->getDeviceId());                    // GUID
    _messenger->sendCmdArg(_device->getDeviceName());                  // DEVICE NAME
    _messenger->sendCmdArg(PROTOCOL_VERSION);                          // SPAD SERIAL INTERFACE VERSION
    _messenger->sendCmdArg(_device->getDeviceVersion());               // FIRMWARE VERSION NUMBER
    _messenger->sendCmdArg("AUTHOR=" + _device->getAuthKey());   // AUTHOR ID
    _messenger->sendCmdArg("ALLOWLOCAL=0");
    _messenger->sendCmdEnd();
}

void SpadProtocol::sendScanResponse() const {
    _messenger->sendCmdStart(0);
    _messenger->sendCmdArg(F("STATESCAN"));
    _messenger->sendCmdEnd();
}

void SpadProtocol::sendPingResponse() const {
    _messenger->sendCmdStart(0);
    _messenger->sendCmdArg("PONG");
    _messenger->sendCmdArg(_messenger->readInt32Arg());
    _messenger->sendCmdEnd();
}

void SpadProtocol::sendConfigResponse() const {
    _messenger->sendCmdStart(0);
    _messenger->sendCmdArg(F("OPTION"));
    _messenger->sendCmdArg(F("ISGENERIC=1"));
    _messenger->sendCmdArg(F("PAGESUPPORT=1"));
    _messenger->sendCmdArg(F("NO_DISPLAY_CLEAR=1"));
    if (_device->hasVirtualPower()) {
        _messenger->sendCmdArg(F("VPSUPPORT=1"));
    }
    _messenger->sendCmdEnd();

    if (_inputCreationCallback != nullptr) {
        _inputCreationCallback();
    }

    _messenger->sendCmd(0, "CONFIG");
}

void SpadProtocol::createVirtualPower() const {
    _messenger->sendCmdStart(0);
    _messenger->sendCmdArg(F("INPUT"));
    _messenger->sendCmdArg(0);
    _messenger->sendCmdArg(F("CONFIGURE_PANEL_STATUS"));
    _messenger->sendCmdArg(F("SYSTEM"));
    _messenger->sendCmdArg(F("SPAD_VIRTUAL_POWER"));
    _messenger->sendCmdArg(F("UI_TYPE=3"));
    _messenger->sendCmdArg(F("CUSTOM_TYPE=POWER"));
    _messenger->sendCmdEnd();
}

void SpadProtocol::createLED(const SpadLed * led) const {
    _messenger->sendCmdStart(0);
    _messenger->sendCmdArg(F("OUTPUT"));
    _messenger->sendCmdArg(led->id);             // This is the LED ID
    _messenger->sendCmdArg(led->label);
    _messenger->sendCmdArg(F("LED"));
    _messenger->sendCmdArg(F("SPAD_LED"));
    _messenger->sendCmdArg(F("UI_FACE=1"));
    _messenger->sendCmdArg(F("COL_1=#FFFFFFFF"));
    _messenger->sendCmdEnd();
}

void SpadProtocol::createButton(const SpadButton * button) const {
    _messenger->sendCmdStart(0);
    _messenger->sendCmdArg(F("INPUT"));
    _messenger->sendCmdArg(button->id);              // This is the button ID
    _messenger->sendCmdArg(button->label);

    switch (button->type) {
        case PUSHBUTTON:
            _messenger->sendCmdArg(F("PUSHBUTTON"));
            _messenger->sendCmdArg(F("SPAD_PUSHBUTTON"));
            break;
        case SWITCH:
            _messenger->sendCmdArg(F("SWITCH"));
            _messenger->sendCmdArg(F("SPAD_SWITCH"));
            break;
    }

    _messenger->sendCmdArg(F("UI_TYPE=1"));
    _messenger->sendCmdArg(F("UI_STYLE=0"));
    _messenger->sendCmdEnd();
}

void SpadProtocol::createEncoder(const SpadEncoder * encoder) const {
    if (encoder->type == INNER) {
        // Only want to process double encoders once.
        return;
    }

    String type;
    switch (encoder->type) {
        case OUTER:
            type = F("SPAD_DOUBLE_ENCODER");
            break;
        case SINGLE:
        default:
            type = F("SPAD_ENCODER");
            break;
    }

    _messenger->sendCmdStart(0);
    _messenger->sendCmdArg(F("INPUT"));
    _messenger->sendCmdArg(encoder->id);             // This is the Encoder ID
    _messenger->sendCmdArg(encoder->label);
    _messenger->sendCmdArg(F("ENCODER"));
    _messenger->sendCmdArg(type);
    _messenger->sendCmdEnd();
}

void SpadProtocol::createBacklight() const {
    sendDebugMessage(F("Trying to create backlights"));

    const auto buttonBacklight = _device->getButtonBacklight();
    if (buttonBacklight != nullptr) {
        sendDebugMessage(F("Creating button backlight...."));

        _messenger->sendCmdStart(1);
        _messenger->sendCmdArg("ADD");
        _messenger->sendCmdArg(buttonBacklight->channelId);
        _messenger->sendCmdArg(buttonBacklight->label);
        _messenger->sendCmdArg("U8");
        _messenger->sendCmdArg("RW");
        _messenger->sendCmdArg("Backlight");
        _messenger->sendCmdArg("Value");
        _messenger->sendCmdArg("PERSIST=1");
        _messenger->sendCmdEnd();
    }

    const auto ledBacklight = _device->getLedBacklight();
    if (ledBacklight != nullptr) {
        sendDebugMessage(F("Creating LED backlight...."));

        _messenger->sendCmdStart(1);
        _messenger->sendCmdArg("ADD");
        _messenger->sendCmdArg(ledBacklight->channelId);
        _messenger->sendCmdArg(ledBacklight->label);
        _messenger->sendCmdArg("U8");
        _messenger->sendCmdArg("RW");
        _messenger->sendCmdArg("Backlight");
        _messenger->sendCmdArg("Value");
        _messenger->sendCmdArg("PERSIST=1");
        _messenger->sendCmdEnd();
    }

    sendDebugMessage(F("Backlight variable is set"));
    sendDebugMessage(F("Creating backlight"));
}

bool SpadProtocol::readBoolean() const {
    return _messenger->readBoolArg();
}

int16_t SpadProtocol::readInt16() const {
    return _messenger->readInt16Arg();
}

int32_t SpadProtocol::readInt32() const {
    return _messenger->readInt32Arg();
}

char * SpadProtocol::readString() const {
    return _messenger->readStringArg();
}
