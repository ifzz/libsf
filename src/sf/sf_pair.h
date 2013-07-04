#ifndef SF_SF_PAIR_H_INCLUDED
#define SF_SF_PAIR_H_INCLUDED


#include <sf/sf_defs.h>


extern sf_type_t sf_pair_type;


sf_pair_t
sf_pair(sf_any_t left, sf_any_t right);

sf_any_t
sf_pair_left(sf_pair_t pair);

sf_pair_t
sf_pair_reversed(sf_pair_t pair);

sf_any_t
sf_pair_right(sf_pair_t pair);


#endif
