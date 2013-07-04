#include "sf_error.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>


void
sf_fatal_error(char const *function, char const *file, int line, char const *format, ...)
{
  if (file) fprintf(stderr, "%s:%i: ", file, line);
  fprintf(stderr, "FATAL ERROR");
  if (function) fprintf(stderr, " in %s", function);
  fprintf(stderr, ": ");
  
  va_list arguments;
  va_start(arguments, format);
  vfprintf(stderr, format, arguments);
  va_end(arguments);
  
  fprintf(stderr, "\n");
  fflush(stderr);
  
  exit(EXIT_FAILURE);
}
