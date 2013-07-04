#ifndef SF_SF_ARRAY_H_INCLUDED
#define SF_SF_ARRAY_H_INCLUDED


#include <sf/sf_defs.h>


extern sf_type_t sf_array_type;


sf_array_t
sf_array(sf_any_t *items, int count);

sf_array_t
sf_array_from_collection(sf_any_t collection);

#define sf_array_from_items(...) \
        sf_array((sf_any_t[]) { __VA_ARGS__ }, SF_VA_ARGS_COUNT(__VA_ARGS__))

sf_any_t
sf_array_item_at_index(sf_array_t array, int index);

sf_any_t const*
sf_array_items(sf_array_t array);

sf_array_t
sf_array_reversed(sf_array_t array);

// A Fisher-Yates shuffle as described in
// http://en.wikipedia.org/wiki/Fisher-Yates_shuffle .
// TODO: Investigate using random numbers larger than 32 bits when shuffling
// arrays longer than 12 items (12! or 479,001,600 permutations).
sf_array_t
sf_array_shuffled(sf_array_t array, sf_random_t random_in, sf_random_t *random_out);


#endif
