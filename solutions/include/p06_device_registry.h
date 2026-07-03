#ifndef P06_DEVICE_REGISTRY_H
#define P06_DEVICE_REGISTRY_H
#include <stdint.h>
#include <stdbool.h>
/*
 * P06 - Device registry (udev-style)
 * Register devices by (bus, devnum). Lookup by either.
 * Supports probe/remove lifecycle callbacks (function pointers).
 * Max 32 devices.
 */
#define DEV_REG_MAX 32
typedef void (*probe_fn)(uint32_t devnum);
typedef void (*remove_fn)(uint32_t devnum);
typedef struct {
    uint8_t  bus;
    uint32_t devnum;
    char     name[32];
    probe_fn  probe;
    remove_fn remove;
    bool     active;
} DeviceEntry;
typedef struct { DeviceEntry devs[DEV_REG_MAX]; int count; } DeviceRegistry;
void         dr_init(DeviceRegistry *r);
int          dr_register(DeviceRegistry *r, uint8_t bus, uint32_t devnum, const char *name, probe_fn p, remove_fn rm);
DeviceEntry *dr_lookup(DeviceRegistry *r, uint8_t bus, uint32_t devnum);
int          dr_remove(DeviceRegistry *r, uint8_t bus, uint32_t devnum);
int          dr_count_active(const DeviceRegistry *r);
#endif