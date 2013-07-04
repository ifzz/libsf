#ifndef SF_SF_RANDOM_H_INCLUDED
#define SF_SF_RANDOM_H_INCLUDED


#include <sf/sf_defs.h>


#define SF_RANDOM_MAX (SF_RANDOM_RANGE - 1)
#define SF_RANDOM_MIN (0l)
#define SF_RANDOM_RANGE (1l << 31)


extern sf_type_t sf_random_type;


sf_random_t 
sf_random_from_random_state(void);

sf_random_t 
sf_random_from_random_state_and_range(long range);

sf_random_t
sf_random_from_state(unsigned short const state[3]);

sf_random_t 
sf_random_from_state_and_range(unsigned short const state[3], long range);

sf_random_t 
sf_random_from_state_range_and_value(unsigned short const state[3], long range, int value);

sf_random_t
sf_random_next(sf_random_t random);

sf_random_t
sf_random_next_from_range(sf_random_t random, long range);

long
sf_random_range(sf_random_t random);

unsigned short const *
sf_random_state(sf_random_t random);

int
sf_random_value(sf_random_t random);


#endif
