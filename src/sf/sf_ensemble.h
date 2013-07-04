#ifndef SF_SF_ENSEMBLE_H_INCLUDED
#define SF_SF_ENSEMBLE_H_INCLUDED


#include <sf/sf_defs.h>


extern sf_type_t sf_ensemble_type;


#define sf_ensemble(...) \
        sf_ensemble_from_collections(sf_array_from_items(__VA_ARGS__))

sf_array_t
sf_ensemble_collections(sf_ensemble_t ensemble);

int
sf_ensemble_count(sf_ensemble_t ensemble);

sf_ensemble_t
sf_ensemble_from_collections(sf_array_t collections);


#endif
