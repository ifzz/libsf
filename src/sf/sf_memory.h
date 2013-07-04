#ifndef SF_SF_MEMORY_H_INCLUDED
#define SF_SF_MEMORY_H_INCLUDED


#include <sf/sf_defs.h>


#ifdef DEBUG
#define SF_MEMORY_LOG
#endif


#ifdef SF_MEMORY_LOG

#define sf_calloc(COUNT, SIZE) sf_memory_log_alloc(__FUNCTION__, __FILE__, __LINE__, calloc((COUNT), (SIZE)))
#define sf_free(MEMORY) free(sf_memory_log_free((MEMORY)))
#define sf_malloc(SIZE) sf_memory_log_alloc(__FUNCTION__, __FILE__, __LINE__, malloc((SIZE)))
#define sf_realloc(MEMORY, SIZE) sf_memory_log_alloc(__FUNCTION__, __FILE__, __LINE__, realloc(sf_memory_log_free((MEMORY)), (SIZE)))
#define sf_strdup(STRING) sf_memory_log_alloc(__FUNCTION__, __FILE__, __LINE__, strdup((STRING)))

void *
sf_memory_log_alloc(char const *function, char const *file, int line, void *memory);

void *
sf_memory_log_free(void *memory);

#else

#define sf_calloc(COUNT, SIZE) calloc((COUNT), (SIZE))
#define sf_free(MEMORY) free((MEMORY))
#define sf_malloc(SIZE) malloc((SIZE))
#define sf_realloc(MEMORY, SIZE) realloc(sf_memory_log_free((MEMORY)), (SIZE))
#define sf_strdup(STRING) strdup((STRING))

#endif


#endif
