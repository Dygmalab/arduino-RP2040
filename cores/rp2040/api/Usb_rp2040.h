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


// Interface and End Points structures
///////////////////////////////////////////////////////
#define USB_RP2040_END_POINT_SIZE 300
struct UsbInterface
{
    uint8_t in_ep[USB_RP2040_END_POINT_SIZE];   // Input Endpoint: Periferal to PC.
    uint8_t out_ep[USB_RP2040_END_POINT_SIZE];  // Output Endpoint: PC to Periferal.
};

struct UsbRp2040
{
    struct UsbInterface keyboard_itf;   // Keyboard interface.
    struct UsbInterface mouse_itf;      // Mouse interface.
};
///////////////////////////////////////////////////////

class Usb_rp2040
{
    public:
        Usb_rp2040();

        struct UsbRp2040 usb;
        uint16_t dataLen = 0;
        boolean flag_rx = 0;

        int32_t send(uint8_t ep, const void *data, int32_t len);    // blocking
        int32_t sendControl(uint8_t flags, const void *d, int32_t len);

        uint16_t available(uint8_t ep);
        int32_t recv(uint8_t ep, void *data, int32_t len);  // non-blocking
        int32_t recv(uint8_t ep);                           // non-blocking
        int32_t recvControl(void *data, int32_t len);
        int32_t recvControlLong(void *data, int32_t len);

    private:
        uint8_t map_endPoint_to_reportId(uint8_t ep);
};

extern Usb_rp2040 usb_rp2040;

/*
    Kaleidoscope neds overloading for this two functions although the parameter 'uint8_t x' -> 
    'flags' (TRANSFER_PGM) is ignored.

    USB_SendControl(0, &hidInterface, sizeof(hidInterface))
    USB_SendControl(TRANSFER_PGM, node->data, node->length)

    For SAMD, TRANSFER_PGM parameter in 'int USB_SendControl(uint8_t x, const void* y, uint8_t z)'
    function is ignored. 
    See: Documents\Arduino\hardware\wiredDefy\rp2040\libraries\KeyboardioHID\src\arch\samd.cpp
*/
int USB_SendControl(void* y, uint8_t z);
int USB_SendControl(uint8_t x, const void* y, uint8_t z);

#endif