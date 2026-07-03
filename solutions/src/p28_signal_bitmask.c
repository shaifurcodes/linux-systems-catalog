#include "p28_signal_bitmask.h"
#include <string.h>
/* TODO: signo 1-64; word index = (signo-1)/64; bit = (signo-1)%64.
 * sigset_count: popcount both words (__builtin_popcountll). */
void sigset_empty(SigSet *s) {}
void sigset_fill(SigSet *s) {}
void sigset_add(SigSet *s, int signo) {}
void sigset_del(SigSet *s, int signo) {}
bool sigset_has(const SigSet *s, int signo) { return false; }
void sigset_or(SigSet *dst, const SigSet *a, const SigSet *b) {}
void sigset_and(SigSet *dst, const SigSet *a, const SigSet *b) {}
void sigset_not(SigSet *dst, const SigSet *src) {}
int  sigset_count(const SigSet *s) { return 0; }