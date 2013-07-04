#ifndef SF_SF_TEMP_POOL_H_INCLUDED
#define SF_SF_TEMP_POOL_H_INCLUDED


#include <sf/sf_defs.h>


#ifdef DEBUG
#define SF_TEMP_POOL_LOG
#endif


sf_any_t
sf_copy_to_temp_pool(sf_any_t any);

sf_any_t
sf_move_to_temp_pool(sf_any_t any);

void
sf_temp_pool(void);

void
sf_temp_pool_release(void);


#endif
