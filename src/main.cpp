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

#include <Arduino.h>

#include "Version.h"
#include "devices/G1000nxi.h"
#include "devices/Gma1347.h"
#include "devices/Gcu478.h"
#include "devices/SpadDevice.h"

// Compile-time check
#ifndef SPAD_AUTHKEY
#error "Please copy platformio_override.example.ini to platformio_override.ini and configure your secrets"
#endif

#ifndef SPAD_DEVICEID
#error "Please copy platformio_override.example.ini to platformio_override.ini and configure your secrets"
#endif

#ifndef SPAD_DEVICENAME
#error "Please copy platformio_override.example.ini to platformio_override.ini and configure your secrets"
#endif

SpadDevice * device;

SpadDevice* GetDeviceSingleton() {
  printVersion();

#if defined(FSDIY_G1000_PFD1)
  static G1000Nxi inst;
  return &inst;
#elif defined(FSDIY_G1000_MFD)
  static G1000Nxi inst;
  return &inst;
#elif defined(FSDIY_G1000_PFD2)
  static G1000Nxi inst;
  return &inst;
#elif defined(FSDIY_GMA1347)
  static Gma1347 inst;
  return &inst;
#elif defined(FSDIY_GCU478)
  static Gcu478 inst;
  return &inst;
#else
  static_assert(false, "No device type macro defined");
#endif
}

void setup() {
  Serial.begin(115200);

  device = GetDeviceSingleton();
  device->setup();
}

void loop() {
  device->loop();
}