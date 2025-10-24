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

#include <vector>
#include <Arduino.h>
#include <Mux.h>

#include "CmdMessenger.h"


class PulsedEncoder;
class SpadProtocol;

enum EncoderType {
    SINGLE,
    INNER,
    OUTER
};

enum ButtonType {
    PUSHBUTTON,
    SWITCH
};

//------------------------- BUTTON PINOUT AND SPAD DEFINITIONS -----------------------------------------------------
// Setup your pushbutton and switches into the button array below. Each button should have a unique ID number between 1 and 100.
// Followed by arduino pin, button label to show in Spad, and input type. Use invert value at the end to quickly invert on off states per button.
// Supported input types are PUSHBUTTON and SWITCH
// Last entry of the array should be {0,0,"END"," ",0,0,0,0},
struct SpadButton {
    byte id;
    String label;
    int8_t pin;
    ButtonType type = PUSHBUTTON;
    bool invert = false;
    int muxIndex = -1;
    int last = 0;

    SpadButton(const byte id, const String&  label, const int8_t pin) : id(id), label(label), pin(pin) {}
    SpadButton(const byte id, const String& label, const int8_t pin, const int muxIndex) : id(id), label(label), pin(pin), muxIndex(muxIndex) {}

    void initializePin() const;
    void update(const SpadProtocol *protocol, const std::vector<admux::Mux> *muxers);
};

//------------------------- ENCODER PINOUT AND SPAD DEFINITIONS -----------------------------------------------------
// Setup your rotary encoders in the rotaries array below. Each encoder should have a unique ID number starting from 101.
// Followed by two arduino pins, encoder is connected to, label for the encoder, and encoder type.
// use type SINGLE for single encoders, OUTER and INNER for dual encoders. For dual encoder entries use same ID number.
// Last entry of the array should be {0, 0, 0, "END", " ", 0},
struct SpadEncoder {
    using StepTable = const unsigned char (*)[4];

    byte id;
    String label;
    EncoderType type;
    PulsedEncoder *encoder;

    void update(const SpadProtocol * protocol) const;
};

struct SpadLed {
    byte id;
    byte pin;
    String label;
    bool initialValue = false;

    SpadLed(const byte id, const byte pin, const String &label)
        : SpadLed(id, pin, label, false) {}

    SpadLed(const byte id, const byte pin, const String &label, const bool initialValue)
        : id(id), pin(pin), label(label), initialValue(initialValue) {}

    void initializePin();
    bool getValue() const { return last; }
    void setValue(bool value);

private:
    bool last = false;
};

struct SpadBacklight {
    byte channelId;
    byte pin;
    String label;
    uint8_t minValue;
    uint8_t maxValue;
    uint8_t initialValue;

    SpadBacklight(
        const byte channelId,
        const byte pin,
        const String & label,
        const uint8_t minValue,
        const uint8_t maxValue,
        const uint8_t initialValue
        ) : channelId(channelId),
          pin(pin),
          label(label),
          minValue(minValue),
          maxValue(maxValue),
          initialValue(initialValue) {}

    void initializePin();
    uint8_t getValue() const { return value; }
    void setValue(uint8_t newValue, bool shouldChange);
    void update() { setValue(value, true); }

private:
    uint8_t value = 0;
};