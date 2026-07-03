#ifndef P27_MOUNT_PARSER_H
#define P27_MOUNT_PARSER_H
/*
 * P27 - /proc/mounts parser
 * Format: "device mountpoint fstype options dump pass\n"
 * Build a searchable table of mount entries.
 */
#define MOUNT_MAX 32
typedef struct {
    char device[64];
    char mountpoint[128];
    char fstype[32];
    char options[256];
} MountEntry;
typedef struct { MountEntry entries[MOUNT_MAX]; int count; } MountTable;
int          mt_parse(const char *buf, MountTable *out);
MountEntry  *mt_find_by_mountpoint(MountTable *t, const char *mp);
MountEntry  *mt_find_by_device(MountTable *t, const char *dev);
int          mt_count_fstype(const MountTable *t, const char *fstype);
#endif