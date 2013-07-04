#ifndef SF_SF_OBJECT_H_INCLUDED
#define SF_SF_OBJECT_H_INCLUDED


#include <sf/sf_defs.h>


#define SF_OBJECT_FIELDS \
    sf_type_t _sf_object_type; \
    int _sf_object_ref_count


char const *
sf_c_string_from(sf_any_t any);

void
sf_default_method_dealloc(sf_any_t any);

sf_string_t
sf_default_method_string_from(sf_any_t any);

void *
sf_object_calloc(size_t size, sf_type_t type);

void
sf_object_free(sf_any_t any);

void *
sf_object_malloc(size_t size, sf_type_t type);

int
sf_ref_count(sf_any_t any);

void
sf_release(sf_any_t any);

sf_any_t
sf_retain(sf_any_t any);

sf_string_t
sf_string_from(sf_any_t any);

sf_type_t
sf_type_of(sf_any_t any);


#endif
