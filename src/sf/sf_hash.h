#ifndef SF_SF_HASH_H_INCLUDED
#define SF_SF_HASH_H_INCLUDED


#include <sf/sf_defs.h>


extern sf_type_t sf_hash_type;


bool
sf_hash_contains_key(sf_hash_t hash, sf_any_t key);

sf_hash_t
sf_hash_from_keys_and_values(sf_any_t keys, sf_any_t values);

sf_any_t
sf_hash_value_for_key(sf_hash_t hash, sf_any_t key);


#endif
