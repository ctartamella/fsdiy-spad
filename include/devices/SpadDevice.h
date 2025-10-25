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

#pragma once

#include <vector>
#include <ComponentDefs.h>

#ifndef SPAD_FIRMWAREVERSION
  #error "SPAD_FIRMWAREVERSION is not defined! Please define it in platformio.ini or copy example override file."
#endif

#ifndef SPAD_AUTHKEY
  #error "SPAD_AUTHKEY is not defined! Please define it in platformio.ini or copy example override file."
#endif

#ifndef SPAD_DEVICEID
  #error "SPAD_DEVICEID is not defined! Please define it in platformio.ini or copy example override file."
#endif

#ifndef SPAD_DEVICENAME
  #error "SPAD_DEVICENAME is not defined! Please define it in platformio.ini or copy example override file."
#endif

class SpadDevice {
    friend class SpadProtocol;

    // State
    bool batteryState = true;
    bool isReady = false;
    bool isStarted = false;

    SpadProtocol *_protocol;

    void checkAllButtons() const;
    void checkAllEncoders() const;

protected:
    // SPAD.Next identifiers.
    // See https://docs.spadnext.com/extending-and-apis/serial-connection/device-communication-flow/device-init-phase
    virtual String getAuthKey() const { return {SPAD_AUTHKEY}; }
    virtual String getDeviceId() const { return {SPAD_DEVICEID}; }
    virtual String getDeviceName() const { return {SPAD_DEVICENAME}; }
    virtual String getDeviceVersion() const { return {SPAD_FIRMWAREVERSION}; }

    // Hardware Definitions
    virtual std::vector<SpadButton> * getButtons() const;
    virtual std::vector<SpadLed> * getLeds() const;
    virtual std::vector<SpadEncoder> * getEncoders() const;
    virtual std::vector<admux::Mux> * getMuxers() const;
    virtual SpadBacklight * getButtonBacklight() const;
    virtual SpadBacklight * getLedBacklight() const;

    // Power and backlight
    virtual bool hasVirtualPower() const { return false; }
    virtual bool getInitialLedValue() const { return false; }

public:
    explicit SpadDevice();
    virtual ~SpadDevice();

    void setup() const;
    void loop() const;

    void setIsSpadStarted(const bool value) { isStarted = value; }
    bool getIsSpadStarted() const { return isStarted; }
    void setPowerState(const bool value) { batteryState = value; }
    bool getPowerState() const { return batteryState; }

    // Callbacks
    void onVirtualPowerChanged(bool powerState);
    void onInputCreation() const;
    void onButtonBacklightChanged(int16_t backlightValue) const;
    void onLedBacklightChanged(int16_t backlightValue) const;
    void onDeviceLedChanged(byte id, bool value) const;
};

