#include "sf.h"


void
_sf_array_init(void);

void
_sf_ensemble_init(void);

void
_sf_hash_init(void);

void
_sf_int_init(void);

void
_sf_list_init(void);

void
_sf_long_init(void);

void
_sf_memory_fin(void);

void
_sf_pair_init(void);

void
_sf_random_init(void);

void
_sf_string_init(void);

void
_sf_temp_pool_init(void);

void
_sf_temp_pool_fin(void);

void
_sf_type_init(void);


void
sf_init(void)
{
  _sf_temp_pool_init(); // init temp pool first
  _sf_type_init(); // init sf_type_t before other object types
  
  _sf_array_init();
  _sf_ensemble_init();
  _sf_hash_init();
  _sf_int_init();
  _sf_list_init();
  _sf_long_init();
  _sf_pair_init();
  _sf_random_init();
  _sf_string_init();
}


void
sf_fin(void)
{
  _sf_temp_pool_fin();
  _sf_memory_fin();
}
