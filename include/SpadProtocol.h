//
// Copyright (C) 2025 Chris Tartamella
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#pragma once

#include <CmdMessenger.h>

class SpadDevice;
struct SpadLed;
struct SpadButton;
struct SpadEncoder;

typedef void (*VirtualPowerCallback)(bool powerState);
typedef void (*SpadStateCallback)(bool spadState);
typedef void (*InputCreationCallback)();
typedef void (*DeviceDataCallback)(int16_t backlightValue);
typedef void (*DeviceLedCallback)(byte id, bool value);


class SpadProtocol {
    static constexpr int PROTOCOL_VERSION=2;

    CmdMessenger * _messenger;
    SpadDevice * _device;

    VirtualPowerCallback _virtualPowerCallback = nullptr;
    SpadStateCallback _spadStateCallback = nullptr;
    InputCreationCallback _inputCreationCallback = nullptr;
    DeviceLedCallback _deviceLedCallback = nullptr;
    DeviceDataCallback _buttonBacklightCallback = nullptr;
    DeviceDataCallback _ledBacklightCallback = nullptr;

    // Command Argument Getters
    bool readBoolean() const;
    int16_t readInt16() const;
    int32_t readInt32() const;
    char * readString() const;

    // Command Handlers
    void sendInitResponse() const;
    void sendScanResponse() const;
    void sendPingResponse() const;
    void sendConfigResponse() const;

public:
    explicit SpadProtocol(SpadDevice * device);

    void feedInSerialData() const;
    void sendCommand(int commandId, const String &command) const;
    void sendDebugMessage(const String & msg) const { _messenger->sendCmd(3, msg); }

    // Component Creation
    void createLED(const SpadLed * led) const;
    void createButton(const SpadButton * button) const;
    void createEncoder(const SpadEncoder * encoder) const;
    void createBacklight() const;
    void createVirtualPower() const;

    void setVirtualPowerCallback(VirtualPowerCallback callback);
    void setSpadStateCallback(SpadStateCallback callback);
    void setInputCreationCallback(InputCreationCallback callback);
    void setDeviceLedCallback(DeviceLedCallback callback);
    void setButtonBacklightCallback(int channelId, DeviceDataCallback callback);
    void setLedBacklightCallback(int channelId, DeviceDataCallback callback);

    // Callbacks meant for usage for global wrappers.
    void onProtocolCommand() const;
    void onSpadEvent() const;
    void onDeviceLed() const;
    void onButtonBacklightChanged() const;
    void onLedBacklightChanged() const;
};
