#include "Usb_rp2040.h"
//#include "C:/Users/Juan Hauara/Documents/Arduino/hardware/wiredDefy/rp2040/libraries/Keyboard/src/Keyboard.h"
//#include "C:/Users/Juan Hauara/Documents/Arduino/hardware/wiredDefy/rp2040/libraries/Mouse/src/Mouse.h"


Usb_rp2040::Usb_rp2040() {}

uint32_t Usb_rp2040::send(uint32_t ep, const void *data, uint32_t len)
{
    /*
        bool tud_hid_n_report(uint8_t instance, uint8_t report_id, void const* report, uint8_t len)

        Declared in Documents\Arduino\hardware\wiredDefy\rp2040\pico-sdk\lib\tinyusb\src\class\hid\hid_device.c
    */
    tud_hid_n_report(0, 1, data, (uint8_t)len);
	digitalWrite(LED_BUILTIN, HIGH);
	delay(100);
	digitalWrite(LED_BUILTIN, LOW);

    return 0;
}