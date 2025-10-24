#pragma once

#include <HardwareSerial.h>

#ifndef GIT_VERSION
#define GIT_VERSION "unknown"
#endif

#ifndef GIT_COMMIT
#define GIT_COMMIT "unknown"
#endif

#ifndef GIT_BRANCH
#define GIT_BRANCH "unknown"
#endif

inline void printVersion() {
    Serial.println(F("Firmware Version Info:"));
    Serial.print(F("  Version: "));
    Serial.println(F(GIT_VERSION));
    Serial.print(F("  Commit: "));
    Serial.println(F(GIT_COMMIT));
    Serial.print(F("  Branch: "));
    Serial.println(F(GIT_BRANCH));
}
