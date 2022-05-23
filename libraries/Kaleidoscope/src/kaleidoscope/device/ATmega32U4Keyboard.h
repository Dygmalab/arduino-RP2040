/* -*- mode: c++ -*-
 * device::ATmega32U4Keyboard -- Generic ATmega32U4 keyboard base class
 * Copyright (C) 2019  Keyboard.io, Inc
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#if defined(__AVR__) || defined(KALEIDOSCOPE_VIRTUAL_BUILD)

#include <Arduino.h>
#include "kaleidoscope/device/Base.h"

#include "kaleidoscope/driver/mcu/ATmega32U4.h"
#include "kaleidoscope/driver/keyscanner/ATmega.h"
#include "kaleidoscope/driver/storage/ATmega32U4EEPROMProps.h"
#include "kaleidoscope/driver/storage/AVREEPROM.h"

namespace kaleidoscope {
namespace device {

struct ATmega32U4KeyboardProps : kaleidoscope::device::BaseProps {
  typedef kaleidoscope::driver::mcu::ATmega32U4Props MCUProps;
  typedef kaleidoscope::driver::mcu::ATmega32U4<MCUProps> MCU;
  typedef kaleidoscope::driver::storage::ATmega32U4EEPROMProps StorageProps;
  typedef kaleidoscope::driver::storage::AVREEPROM<StorageProps> Storage;
};

#ifndef KALEIDOSCOPE_VIRTUAL_BUILD
template <typename _DeviceProps>
class ATmega32U4Keyboard : public kaleidoscope::device::Base<_DeviceProps> {
 public:
  auto serialPort() -> decltype(Serial) & {
    return Serial;
  }
};
#else // ifndef KALEIDOSCOPE_VIRTUAL_BUILD
template <typename _DeviceProps>
class ATmega32U4Keyboard;
#endif // ifndef KALEIDOSCOPE_VIRTUAL_BUILD

}
}

#endif
