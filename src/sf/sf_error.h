#ifndef SF_SF_ERROR_H_INCLUDED
#define SF_SF_ERROR_H_INCLUDED


#include <sf/sf_defs.h>


#ifdef DEBUG

#define SF_FATAL_ERROR(...) \
    sf_fatal_error(__FUNCTION__, __FILE__, __LINE__, __VA_ARGS__)

#else

#define SF_FATAL_ERROR(...) \
    sf_fatal_error(NULL, NULL, 0, __VA_ARGS__)

#endif


void
sf_fatal_error(char const *function, char const *file, int line, char const *format, ...) SF_FORMAT_FUNCTION(4, 5);


#endif
