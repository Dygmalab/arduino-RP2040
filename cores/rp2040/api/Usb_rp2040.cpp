#include "Usb_rp2040.h"
//#include "C:/Users/Juan Hauara/Documents/Arduino/hardware/wiredDefy/rp2040/libraries/Keyboard/src/Keyboard.h"
//#include "C:/Users/Juan Hauara/Documents/Arduino/hardware/wiredDefy/rp2040/libraries/Mouse/src/Mouse.h"


Usb_rp2040::Usb_rp2040() {}

int32_t Usb_rp2040::send(uint8_t ep, const void *data, int32_t len)
{
    /*
        bool tud_hid_n_report(uint8_t instance, uint8_t report_id, void const* report, uint8_t len)

        Declared in Documents\Arduino\hardware\wiredDefy\rp2040\pico-sdk\lib\tinyusb\src\class\hid\hid_device.c
    */
    bool ret = tud_hid_n_report(0, 1, data, (uint8_t)len);

    // DEBUG
	/*digitalWrite(LED_BUILTIN, HIGH);
	delay(150);
	digitalWrite(LED_BUILTIN, LOW);*/

    return (int32_t)ret;
}

// Send ‘len’ octets of ‘d’ through the control pipe (endpoint 0).
// Blocks until ‘len’ octets are sent. Returns the number of octets
// sent, or -1 on error.
int32_t Usb_rp2040::sendControl(uint8_t flags, const void *d, int32_t len)
{
    int32_t ret = send(0, d, len);

    // DEBUG
	/*digitalWrite(LED_BUILTIN, HIGH);
	delay(150);
	digitalWrite(LED_BUILTIN, LOW);*/
    
    return ret;
}