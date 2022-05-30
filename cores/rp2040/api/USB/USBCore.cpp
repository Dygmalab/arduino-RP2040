/*
  Copyright (c) 2016 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#include "Arduino.h"

#include "api/USBAPI.h"
#include "C:/Users/Juan Hauara/Documents/Arduino/hardware/wiredDefy/rp2040/libraries/Keyboard/src/Keyboard.h"
#include "C:/Users/Juan Hauara/Documents/Arduino/hardware/wiredDefy/rp2040/libraries/Mouse/src/Mouse.h"

extern "C" {
	// RP2040 USB C libra
}

/*
 * Descriptor for storing an endpoint’s direction, type, and max
 * packet length.
 */
union EPDesc {
    struct {
        uint8_t maxlen;
        unsigned int type:3;
        unsigned int dir:5;
    } parts;
    unsigned int val;

    // Default descriptor, in case, I dunno, you need to initialize an
    // array or something.
    constexpr EPDesc() : EPDesc(USB_TRX_OUT, USB_EP_ATTR_CTL, USB_EP_SIZE) {}

    // Encode a direction, type, and max packet length in an endpoint
    // descriptor.
    constexpr EPDesc(uint8_t dir, uint8_t type) : EPDesc(dir, type, USB_EP_SIZE) {}

    // Encode a direction and type in an endpoint descriptor, using
    // the device’s max packet length as the endpoint’s.
    constexpr EPDesc(uint8_t dir, uint8_t type, uint8_t maxlen) : val((dir|type) << 8 | maxlen) {}

    // Extract the direction from an endpoint descriptor.
    constexpr uint8_t dir() {
        return this->parts.dir << 3;
    }

    // Extract the type from an endpoint descriptor.
    constexpr uint8_t type() {
        return this->parts.type;
    }

    // Extract the max packet length from an endpoint descriptor.
    constexpr uint8_t maxlen() {
        return this->parts.maxlen;
    }
};

/*
 * Mappings from Arduino USB API to USBCore singleton functions.
 */
/*#define TRANSFER_PGM     0x80
#define TRANSFER_ZERO    0x20
#define TRANSFER_RELEASE 0x40*/

#define USB_SendControl     USBCore().sendControl
#define USB_RecvControl     USBCore().recvControl
#define USB_RecvControlLong USBCore().recvControlLong
#define USB_Available       USBCore().available
#define USB_SendSpace       USBCore().sendSpace
#define USB_Send            USBCore().send
#define USB_Recv            USBCore().recv
#define USB_Flush           USBCore().flush