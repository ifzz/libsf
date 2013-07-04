#include "sf_memory.h"

#include <stdio.h>
#include "sf_error.h"


#ifdef SF_MEMORY_LOG


static int alloc_count;
static int free_count;
static int live_alloc_count;
static int max_live_alloc_count;


void *
sf_memory_log_alloc(char const *function, char const *file, int line, void *memory)
{
  ++alloc_count;
  ++live_alloc_count;
  if (live_alloc_count > max_live_alloc_count) max_live_alloc_count = live_alloc_count;
  if ( ! memory) sf_fatal_error(function, file, line, "out of memory");
  return memory;
}


void *
sf_memory_log_free(void *memory)
{
  ++free_count;
  --live_alloc_count;
  return memory;
}


#endif


void
_sf_memory_fin(void)
{
#ifdef SF_MEMORY_LOG
  if (alloc_count != free_count) {
    fprintf(stderr, "\nWARNING: recorded %i allocations but %i deallocations\n", alloc_count, free_count);
    return;
  } else {
    fprintf(stdout, "\nsf_memory:\n");
    fprintf(stdout, "  allocation count: %i\n", alloc_count);
    fprintf(stdout, "  max live allocation count: %i\n", max_live_alloc_count);
  }
#endif
}
