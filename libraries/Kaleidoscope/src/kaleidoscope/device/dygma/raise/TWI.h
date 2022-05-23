/* -*- mode: c++ -*-
 * kaleidoscope::device::dygma::Raise -- Kaleidoscope device plugin for Dygma Raise
 * Copyright (C) 2017-2019  Keyboard.io, Inc
 * Copyright (C) 2017-2019  Dygma Lab S.L.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifdef ARDUINO_SAMD_RAISE

#include <Arduino.h>

namespace kaleidoscope {
namespace device {
namespace dygma {
namespace raise {

class TWI {
 public:
  explicit TWI(int addr) : addr_(addr), crc_errors_(0) {}

  uint8_t writeTo(uint8_t *data, size_t length);
  uint8_t readFrom(uint8_t* data, size_t length);
  void recovery();
  void disable();
  void init(uint16_t clock_khz);
  uint8_t crc_errors() {
    return crc_errors_;
  }

 private:
  int addr_;
  uint8_t crc_errors_;
  uint16_t clock_khz_;
};

}
}
}
}
#endif
