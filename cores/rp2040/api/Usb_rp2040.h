#ifndef __USB_RP2040_H__
#define __USB_RP2040_H__

#include <stdint.h> // uint32_t, etc.
#include "class/hid/hid_device.h"	// Para utilizar las funciones de la librería Adafruit_TinyUSB_Arduino
#include "Arduino.h"

class Usb_rp2040
{
public:
    Usb_rp2040();

    int32_t send(uint8_t ep, const void *data, int32_t len);
    int32_t sendControl(uint8_t flags, const void *d, int32_t len);
};

#endif