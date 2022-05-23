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
#include "TWI.h"

struct cRGB {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

namespace kaleidoscope {
namespace device {
namespace dygma {
namespace raise {

#define LED_BANKS 9

#define LEDS_PER_HAND 72
#define LPH LEDS_PER_HAND
#define LEDS_PER_BANK 8
#define LED_BYTES_PER_BANK (sizeof(cRGB) * LEDS_PER_BANK)

#define LED_RED_CHANNEL_MAX 229

typedef union {
  cRGB leds[LEDS_PER_HAND];
  byte bytes[LED_BANKS][LED_BYTES_PER_BANK];
} LEDData_t;

// return what bank the led is in
#define LED_TO_BANK(led) (led / LEDS_PER_BANK)

typedef union {
  uint8_t rows[5];
  uint64_t all;
} keydata_t;

class Hand {
 public:
  explicit Hand(byte ad01) : ad01_(ad01), twi_(i2c_addr_base_ | ad01) {}

  int readVersion();
  int readSLEDVersion();
  int readSLEDCurrent();
  byte setSLEDCurrent(byte current);
  int readJoint();
  int readLayout();

  byte setKeyscanInterval(byte delay);
  int readKeyscanInterval();

  byte setLEDSPIFrequency(byte frequency);
  int readLEDSPIFrequency();

  bool moreKeysWaiting();
  void sendLEDData();
  void sendLEDBank(uint8_t bank);
  keydata_t getKeyData();
  bool readKeys();
  uint8_t controllerAddress();
  uint8_t crc_errors() {
    return twi_.crc_errors();
  }

  void setBrightness(uint8_t brightness) {
    brightness_adjustment_ = 255 - brightness;
  }
  uint8_t getBrightness() {
    return 255 - brightness_adjustment_;
  }

  LEDData_t led_data;
  bool online = false;

 private:
  uint8_t brightness_adjustment_ = 0;
  int ad01_;
  TWI twi_;
  keydata_t key_data_;
  uint8_t next_led_bank_ = 0;
  uint8_t red_max_fraction_ = (LED_RED_CHANNEL_MAX * 100) / 255;

  static constexpr uint8_t i2c_addr_base_ = 0x58;

  int readRegister(uint8_t cmd);
};

}
}
}
}

#endif
