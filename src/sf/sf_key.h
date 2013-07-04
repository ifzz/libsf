#ifndef SF_SF_KEY_H_INCLUDED
#define SF_SF_KEY_H_INCLUDED


#include <sf/sf_defs.h>


#define SF_HASH_INT(VALUE) (VALUE)


#if INT_MAX == LONG_MAX

#define SF_HASH_LONG(VALUE) ((int) (VALUE))

#else

#define SF_HASH_LONG(VALUE) ((int) ((VALUE) ^ ((VALUE) >> (sizeof(int) * 8))))

#endif


int
sf_default_method_hash_code(sf_any_t key);

bool
sf_default_method_is_equal(sf_any_t key, sf_any_t other_key);

int
sf_hash_code(sf_any_t key);

bool
sf_is_equal(sf_any_t key, sf_any_t other_key);

bool
sf_is_key_type(sf_any_t any);


#endif
