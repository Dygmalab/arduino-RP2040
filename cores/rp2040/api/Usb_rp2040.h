#ifndef __USB_RP2040_H__
#define __USB_RP2040_H__

#include <stdint.h> // uint32_t, etc.
#include "class/hid/hid_device.h"	// Para utilizar las funciones de la librería Adafruit_TinyUSB_Arduino
#include "Arduino.h"

class Usb_rp2040
{
public:
    Usb_rp2040();

    uint32_t send(uint32_t ep, const void *data, uint32_t len);
};

#endif