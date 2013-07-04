#ifndef SF_SF_TYPE_H_INCLUDED
#define SF_SF_TYPE_H_INCLUDED


#include <sf/sf_defs.h>
#include <sf/sf_string.h>


extern sf_type_t sf_type_type;


sf_type_t
sf_type(char const *name,
        sf_method_dealloc dealloc,
        sf_method_string_from string_from,
        sf_method_is_equal is_equal,
        sf_method_hash_code hash_code,
        sf_method_count count,
        sf_method_each each);

bool
sf_type_is_collection_type(sf_type_t type);

bool
sf_type_is_key_type(sf_type_t type);

sf_method_count
sf_type_method_count(sf_type_t type);

sf_method_dealloc
sf_type_method_dealloc(sf_type_t type);

sf_method_each
sf_type_method_each(sf_type_t type);

sf_method_hash_code
sf_type_method_hash_code(sf_type_t type);

sf_method_is_equal
sf_type_method_is_equal(sf_type_t type);

sf_method_string_from
sf_type_method_string_from(sf_type_t type);

sf_string_t
sf_type_name(sf_type_t type);


#endif
