/**
 * Tugas Besar 1 IF2230 Operating System
 */

#ifndef __PRNG_H__
#define __PRNG_H__ 1

extern unsigned prng_seed;

unsigned prng_gen (void);
unsigned prng_gen_range (unsigned a, unsigned b);

#endif
