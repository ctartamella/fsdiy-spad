#pragma once

#include <Encoder.h>

class PulsedEncoder {
protected:
    ~PulsedEncoder() = default;

private:
    Encoder* enc;
    long state = 0;
    int pulseCount = 2;

public:
    PulsedEncoder(const int pin1, const int pin2) {
        enc = new Encoder(pin1, pin2);
    }

    PulsedEncoder(const int pin1, const int pin2, const int pulseCount) {
        enc = new Encoder(pin1, pin2);
        this->pulseCount = pulseCount;
    }

    int update() {
        const long new_state = enc->read()/pulseCount;
        if (new_state > state){ // CW
            state = new_state;
            return 1;
        } if (new_state < state) { // CCW
            state = new_state;
            return -1;
        }
        return 0;
    }
};
