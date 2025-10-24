#include <ComponentDefs.h>

#include "SpadProtocol.h"
#include "components/PulsedEncoder.h"

using namespace admux;
using namespace std;

void SpadButton::initializePin() const {
    pinMode(pin, INPUT_PULLUP);
}

void SpadButton::update(const SpadProtocol * protocol, const vector<Mux> * muxers) {
    int pinValue;

    if (muxIndex >= 0) {
        auto muxer = (*muxers)[muxIndex];
        pinValue = muxer.read(pin);
    }
    else {
        pinValue = digitalRead(pin);
    }

    if (pinValue != last)
    {
        String s;
        s += id;
        s += ",";
        if(invert==0){s += last;} else {s += !last;}
        last = !last;

        protocol->sendCommand(8, s);
        delay(25);
    }
}

void SpadEncoder::update(const SpadProtocol * protocol) const {
    const auto newState = encoder->update();
    int offset;

    if (newState == 0) {
        return;
    }

    switch (type) {
        case SINGLE:
        case INNER:
            offset = 1;
            break;
        case OUTER:
            offset = 100;
            break;
        default:
            offset = 0;
    }

    String s;
    s += id;
    s += ",";
    s += String(offset * newState);

    protocol->sendCommand(8, s);
    delay(10);
}

void SpadLed::initializePin() {
    pinMode(pin, OUTPUT);
    setValue(initialValue);
}

void SpadLed::setValue(const bool value) {
    const auto newValue = value ? HIGH : LOW;
    digitalWrite(pin, newValue);
    last = value;
}

void SpadBacklight::initializePin() {
    pinMode(pin, OUTPUT);
    setValue(initialValue, true);
}

void SpadBacklight::setValue(const uint8_t newValue, const bool shouldChange) {
    constexpr int inputRange = 255;
    const auto outputRange = maxValue - minValue;
    const auto scaledValue = static_cast<uint8_t>(static_cast<float>(outputRange)/inputRange * newValue + minValue);

    if (shouldChange) {
        analogWrite(pin, scaledValue);
    }

    value = scaledValue;
}