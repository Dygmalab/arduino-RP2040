#include "Usb_rp2040.h"
//#include "C:/Users/Juan Hauara/Documents/Arduino/hardware/wiredDefy/rp2040/libraries/Keyboard/src/Keyboard.h"
//#include "C:/Users/Juan Hauara/Documents/Arduino/hardware/wiredDefy/rp2040/libraries/Mouse/src/Mouse.h"


Usb_rp2040 usb_rp2040;


Usb_rp2040::Usb_rp2040() {}

uint8_t Usb_rp2040::map_endPoint_to_reportId(uint8_t ep)
{
    // Mappings from ep (endpoints) to rep (report ids)

    if ((ep == 0) || (ep == 1)) // Control endpoint or keyboard endpoint.
    {
        return 1;               // REPORT_ID_KEYBOARD = 1;
    }
    else if (ep == 2)           // Mouse endpoint.
    {
        return 2;               // REPORT_ID_MOUSE = 2;
    }
    
    return 0;
}

// Send
////////////////////////////////////////////////////////////////////////
// Blocking send of data to an endpoint. Returns the number of octets
// sent, or -1 on error.
int32_t Usb_rp2040::send(uint8_t ep, const void *data, int32_t len)
{
    /*
        bool tud_hid_n_report(uint8_t instance, uint8_t report_id, void const* report, uint8_t len)

        Declared in Documents\Arduino\hardware\wiredDefy\rp2040\pico-sdk\lib\tinyusb\src\class\hid\hid_device.c

		El parámetro instance hace referencia a la instancia de interface o número de interface. 
		instance = 0 -> Keyboard.
		instance = 1 -> Mouse.

        report_id:
        ----------
        REPORT_ID_KEYBOARD = 1
        REPORT_ID_MOUSE = 2
        REPORT_ID_CONSUMER_CONTROL = 3
        REPORT_ID_GAMEPAD = 4
        REPORT_ID_COUNT = 5
    */

    uint8_t repId = this->map_endPoint_to_reportId(ep);
    bool ret = tud_hid_n_report(0, repId, data, (uint8_t)len);

    // DEBUG
    /*gpio_put(PICO_DEFAULT_LED_PIN, 1);
    sleep_ms(125);
    gpio_put(PICO_DEFAULT_LED_PIN, 0);*/

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
    (void) flags;
    
    /*
        bool tud_hid_n_report(uint8_t instance, uint8_t report_id, void const* report, uint8_t len)

        Declared in Documents\Arduino\hardware\wiredDefy\rp2040\pico-sdk\lib\tinyusb\src\class\hid\hid_device.c

		El parámetro instance hace referencia a la instancia de interface o número de interface. 
		instance = 0 -> Keyboard.
		instance = 1 -> Mouse.
		
		report_id:
		----------
		REPORT_ID_KEYBOARD = 1
		REPORT_ID_MOUSE = 2
		REPORT_ID_CONSUMER_CONTROL = 3
		REPORT_ID_GAMEPAD = 4
		REPORT_ID_COUNT = 5
    */
    bool ret = tud_hid_n_report(0, 1, d, (uint8_t)len);

    // DEBUG
	/*digitalWrite(LED_BUILTIN, HIGH);
	delay(150);
	digitalWrite(LED_BUILTIN, LOW);*/

    return ret;
}


/*
    Kaleidoscope neds overloading for this two functions although the parameter 'uint8_t x' -> 
    'flags' (TRANSFER_PGM) is ignored.

    USB_SendControl(0, &hidInterface, sizeof(hidInterface))
    USB_SendControl(TRANSFER_PGM, node->data, node->length)

    For SAMD, TRANSFER_PGM parameter in 'int USB_SendControl(uint8_t x, const void* y, uint8_t z)'
    function is ignored. 
    See: Documents\Arduino\hardware\wiredDefy\rp2040\libraries\KeyboardioHID\src\arch\samd.cpp
*/
int USB_SendControl(void* y, uint8_t z)
{
    // Send ‘len’ octets of ‘d’ through the control pipe (endpoint 0).
    // Blocks until ‘len’ octets are sent. Returns the number of octets
    // sent, or -1 on error.
    return usb_rp2040.sendControl(0, y, z);    // The parameter 'flags' (TRANSFER_PGM) is ignored
}

int USB_SendControl(uint8_t x, const void* y, uint8_t z)
{
    (void)x;

    // Send ‘len’ octets of ‘d’ through the control pipe (endpoint 0).
    // Blocks until ‘len’ octets are sent. Returns the number of octets
    // sent, or -1 on error.
    return usb_rp2040.sendControl(0, y, z);    // The parameter 'flags' (TRANSFER_PGM) is ignored
}

// kaleidoscope needs this function being defined.
void USB_PackMessages(bool pack)  // nop
{
    (void)pack;
}
////////////////////////////////////////////////////////////////////////


// Receive
////////////////////////////////////////////////////////////////////////
// // Invoked when received SET_REPORT control request or
// // received data on OUT endpoint
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, 
                           uint8_t const *buffer, uint16_t bufsize)
{
    // DEBUG
    //  gpio_put(PICO_DEFAULT_LED_PIN, 1);
    //  sleep_ms(125);
    //  gpio_put(PICO_DEFAULT_LED_PIN, 0);

	// DEBUG
	// flag_rx = 1;	// para imprimir en pantalla
	// interface_num = instance;
	// g_report_id = report_id;
	// g_report_type = report_type;
	// g_buffer = buffer;
	// g_bufsize = bufsize;

	// LED indicator is output report with only 1 byte length
	//if (report_type != 2) return;

	// The LED bit map is as follows: (also defined by KEYBOARD_LED_* )
	// Kana (4) | Compose (3) | ScrollLock (2) | CapsLock (1) | Numlock (0)
	//uint8_t ledIndicator = buffer[0];
	
	// turn on LED if capslock is set
	//digitalWrite(LED_BUILTIN, ledIndicator & KEYBOARD_LED_CAPSLOCK);
	//digitalWrite(LED_BUILTIN, ledIndicator & KEYBOARD_LED_NUMLOCK);

    if (report_type == TUSB_TUSB_HID_REPORT_TYPE_OUTPUT)    // OUTPUT_REPORT: PC to periferal
    {
        memcpy(usb_rp2040.usb.keyboard_itf.out_ep, buffer, bufsize);  // Output Endpoint: PC to Periferal.
        usb_rp2040.dataLen = bufsize;
        usb_rp2040.flag_rx = 1;
    }
}

// Return the number of octets available on OUT endpoint.
uint16_t Usb_rp2040::available(uint8_t ep)
{
    (void)ep;

    return dataLen;
}

// Non-blocking receive. Returns the number of octets read, or -1 on
// error.
int32_t Usb_rp2040::recv(uint8_t ep, void *data, int32_t len)   // non-blocking
{
    uint8_t *_data = (uint8_t *)data;

    memcpy(_data, usb.keyboard_itf.out_ep, dataLen);  // Output Endpoint: PC to Periferal.

    return dataLen;
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

// kaleidoscope needs this function being defined.
// Returns a pointer to the Nth element of the EP buffer structure.
// void * epBuffer(unsigned int n)
// {
//     if (n == 1)
//     {
//         return (void *)&usb_rp2040.usb.keyboard_itf.in_ep;  // Input Endpoint: Periferal to PC.
//     }
//     else if (n == 2)
//     {
//         return (void *)&usb_rp2040.usb.mouse_itf.in_ep;     // Input Endpoint: Periferal to PC.
//     }

//     return nullptr;
// }
////////////////////////////////////////////////////////////////////////


// kaleidoscope needs this array being defined.
uint32_t EndPoints[] =
{
	USB_ENDPOINT_TYPE_CONTROL,

#ifdef CDC_ENABLED
	USB_ENDPOINT_TYPE_INTERRUPT | USB_ENDPOINT_IN(0),           // CDC_ENDPOINT_ACM
	USB_ENDPOINT_TYPE_BULK      | USB_ENDPOINT_OUT(0),               // CDC_ENDPOINT_OUT
	USB_ENDPOINT_TYPE_BULK | USB_ENDPOINT_IN(0),                // CDC_ENDPOINT_IN
#endif

#ifdef PLUGGABLE_USB_ENABLED
	//allocate 6 endpoints and remove const so they can be changed by the user
	0,
	0,
	0,
	0,
	0,
	0,
#endif
};