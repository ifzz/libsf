#ifndef SF_SF_COLLECTION_H_INCLUDED
#define SF_SF_COLLECTION_H_INCLUDED


#include <sf/sf_array.h>


sf_list_t
sf_collect(sf_any_t collection, sf_collect_from collect_from, void *context);

sf_list_t
sf_collect_strings(sf_any_t collection);

int
sf_count(sf_any_t collection);

int
sf_default_method_count(sf_any_t collection);

bool
sf_default_method_each(sf_any_t item, sf_act_on act_on, void *context);

bool
sf_each(sf_any_t collection, sf_act_on act_on, void *context);

sf_list_t
sf_filter(sf_any_t collection, sf_is_included is_included, void *context);

bool
sf_is_collection_type(sf_any_t any);


#endif
