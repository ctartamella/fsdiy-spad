#pragma once

///
/// 1. Copy this class and place the header and source file in the include and src
/// folders respectively.
///
/// 2. In platform.io copy one of the other device entries and rename it accordingly.
///     * Note the -D define name for the device
///
/// 3. In the source and header files, replace the #ifdef at the tops with your new define name
///
/// 4. In main.cpp, add an entry in getDeviceSingleton
///


#ifdef FSDIY_DEVICENAME
#include "devices/SpadDevice.h"


class DeviceTemplate : SpadDevice {

protected:
    // Define overrides from SpadDevice
    std::vector<SpadButton> * getButtons() const override;
    std::vector<SpadEncoder> * getEncoders() const override;

public:
    explicit DeviceTemplate() = default;

};


#endif