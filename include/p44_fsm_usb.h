#ifndef P44_FSM_USB_H
#define P44_FSM_USB_H
#include <stdbool.h>
/*
 * P44 - USB device enumeration state machine
 * Models the USB device state machine from USB 2.0 spec:
 * Attached -> Powered -> Default -> Address -> Configured -> Suspended
 * Implement legal transitions and violation detection.
 */
typedef enum {
    USB_ATTACHED=0, USB_POWERED, USB_DEFAULT,
    USB_ADDRESS, USB_CONFIGURED, USB_SUSPENDED, USB_STATE_COUNT
} UsbState;
typedef enum {
    USB_EV_POWER_ON, USB_EV_RESET, USB_EV_ADDRESS_SET,
    USB_EV_CONFIG_SET, USB_EV_SUSPEND, USB_EV_RESUME, USB_EV_DISCONNECT
} UsbEvent;
typedef struct { UsbState state; int transition_count; int error_count; } UsbDev;
void usb_dev_init(UsbDev *d);
int  usb_dev_event(UsbDev *d, UsbEvent ev);  /* 0=ok, -1=illegal transition */
bool usb_dev_is_ready(const UsbDev *d);       /* true if CONFIGURED */
const char *usb_state_name(UsbState s);
#endif