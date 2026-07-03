#ifndef P28_SIGNAL_BITMASK_H
#define P28_SIGNAL_BITMASK_H
#include <stdint.h>
#include <stdbool.h>
/*
 * P28 - Signal set / bitmask (sigset_t-lite)
 * Linux signals 1..64 stored in a two-word bitmask.
 * Implement the full sigset_t API subset.
 */
typedef struct { uint64_t words[2]; } SigSet;
void sigset_empty(SigSet *s);
void sigset_fill(SigSet *s);
void sigset_add(SigSet *s, int signo);   /* signo 1..64 */
void sigset_del(SigSet *s, int signo);
bool sigset_has(const SigSet *s, int signo);
void sigset_or(SigSet *dst, const SigSet *a, const SigSet *b);
void sigset_and(SigSet *dst, const SigSet *a, const SigSet *b);
void sigset_not(SigSet *dst, const SigSet *src);
int  sigset_count(const SigSet *s);
#endif