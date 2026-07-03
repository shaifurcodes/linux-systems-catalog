#include "p06_device_registry.h"
#include <string.h>
/* TODO: linear scan registry. dr_register calls probe(); dr_remove calls remove(). */
void         dr_init(DeviceRegistry *r) {}
int          dr_register(DeviceRegistry *r, uint8_t bus, uint32_t devnum, const char *name, probe_fn p, remove_fn rm) { return -1; }
DeviceEntry *dr_lookup(DeviceRegistry *r, uint8_t bus, uint32_t devnum) { return NULL; }
int          dr_remove(DeviceRegistry *r, uint8_t bus, uint32_t devnum) { return -1; }
int          dr_count_active(const DeviceRegistry *r) { return 0; }