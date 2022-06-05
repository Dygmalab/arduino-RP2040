#include "Usb_rp2040.h"
//#include "C:/Users/Juan Hauara/Documents/Arduino/hardware/wiredDefy/rp2040/libraries/Keyboard/src/Keyboard.h"
//#include "C:/Users/Juan Hauara/Documents/Arduino/hardware/wiredDefy/rp2040/libraries/Mouse/src/Mouse.h"


Usb_rp2040::Usb_rp2040() {}


// Send
////////////////////////////////////////////////////////////////////////
// Blocking send of data to an endpoint. Returns the number of octets
// sent, or -1 on error.
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

    if (ret)
    {
        return len;
    }
    else
    {
        return -1;
    }
}

// Send ‘len’ octets of ‘d’ through the control pipe (endpoint 0).
// Blocks until ‘len’ octets are sent. Returns the number of octets
// sent, or -1 on error.
int32_t Usb_rp2040::sendControl(uint8_t flags, const void *d, int32_t len)
{
    (void)flags;
    
    int32_t ret = this->send(0, d, len);

    // DEBUG
	/*digitalWrite(LED_BUILTIN, HIGH);
	delay(150);
	digitalWrite(LED_BUILTIN, LOW);*/

    return ret;
}
////////////////////////////////////////////////////////////////////////


// Receive
////////////////////////////////////////////////////////////////////////
// Non-blocking receive. Returns the number of octets read, or -1 on
// error.
int32_t Usb_rp2040::recv(uint8_t ep, void *data, int32_t len)   // non-blocking
{
    uint8_t *d = (uint8_t *)data;

    //return EPBuffers().buf(ep).pop(d, len);
    /*
        Invoked when received SET_REPORT control request or
        received data on OUT endpoint ( Report ID = 0, Type = 0 )
        void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize)
    */

    return 0;
}

// Receive one octet from OUT endpoint ‘ep’. Return the received 
// octet or -1 if no bytes available.
int32_t Usb_rp2040::recv(uint8_t ep)
{
    uint8_t c;

    auto rc = this->recv(ep, &c, sizeof(c));

    if (rc < 0)
    {
        return rc;
    }
    else if (rc == 0)
    {
        return -1;
    }

    return c;            // No error, received octet returned.
}

// Non-blocking receive. Does not timeout or cross fifo boundaries.
// Returns the number of octets read, or -1 on error.
int32_t Usb_rp2040::recvControl(void *data, int32_t len)
{
    return this->recv(0, data, len);
}

// TODO: no idea? this isn’t in the avr 1.8.2 library, although it has
// the function prototype.
int32_t Usb_rp2040::recvControlLong(void *data, int32_t len)
{
    (void)data;
    (void)len;

    return -1;
}
////////////////////////////////////////////////////////////////////////