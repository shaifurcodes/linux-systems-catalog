#include "p26_pid_lookup.h"
#include <string.h>
/* TODO: bitmap where bit=1 means "in use". alloc scans words for first 0-bit
 * using __builtin_ctz or manual shift. pid_free clears the bit. */
void pid_map_init(PidMap *pm) {}
int  pid_alloc(PidMap *pm) { return -1; }
void pid_free(PidMap *pm, int pid) {}
int  pid_in_use(const PidMap *pm, int pid) { return 0; }
int  pid_count_free(const PidMap *pm) { return 0; }