#include "p44_fsm_usb.h"
/* TODO: encode legal transitions as a 2D table transition[state][event]=new_state.
 * -1 in table means illegal. usb_dev_event looks up table, updates state. */
void usb_dev_init(UsbDev *d) {}
int  usb_dev_event(UsbDev *d, UsbEvent ev) { return -1; }
bool usb_dev_is_ready(const UsbDev *d) { return false; }
const char *usb_state_name(UsbState s) { return "unknown"; }