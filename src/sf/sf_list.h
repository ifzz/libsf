#ifndef SF_SF_LIST_H_INCLUDED
#define SF_SF_LIST_H_INCLUDED


#include <sf/sf_array.h>


extern sf_type_t sf_list_type;


sf_list_t 
sf_list(sf_any_t head, sf_list_t tail);

sf_list_t
sf_list_from_collection(sf_any_t collection);

#define sf_list_from_items(...) \
        sf_list_from_collection(sf_array_from_items(__VA_ARGS__))

sf_any_t
sf_list_head(sf_list_t list);

sf_list_t
sf_list_reversed(sf_list_t list);

sf_list_t
sf_list_tail(sf_list_t list);


#endif
