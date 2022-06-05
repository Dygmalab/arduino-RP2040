#ifndef __USB_RP2040_H__
#define __USB_RP2040_H__

#include <stdint.h> // uint32_t, etc.
#include "Arduino.h"
extern "C"
{
    /*
        Para utilizar las funciones de la librería TinyUSB de pico-sdk 
        en Documents\Arduino\hardware\wiredDefy\rp2040\pico-sdk\lib\
        tinyusb\src\class\hid\hid_device.h
    */
    #include "class/hid/hid_device.h"
}

class Usb_rp2040
{
public:
    Usb_rp2040();

    int32_t send(uint8_t ep, const void *data, int32_t len);    // blocking
    int32_t sendControl(uint8_t flags, const void *d, int32_t len);

    int32_t recv(uint8_t ep, void *data, int32_t len);  // non-blocking
    int32_t recv(uint8_t ep);                           // non-blocking
    int32_t recvControl(void *data, int32_t len);
    int32_t recvControlLong(void *data, int32_t len);
};

#endif