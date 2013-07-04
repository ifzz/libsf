#include "sf_long.h"

#include <stdarg.h>
#include "sf_error.h"
#include "sf_key.h"
#include "sf_object.h"
#include "sf_string.h"
#include "sf_temp_pool.h"
#include "sf_type.h"


static int
hash_code(sf_any_t self);

static bool
is_equal(sf_any_t self, sf_any_t other);

static sf_string_t 
string_from(sf_any_t self);


struct _sf_long
{
  SF_OBJECT_FIELDS;
  long value;
};


sf_type_t sf_long_type;


void
_sf_long_init(void)
{
  sf_long_type = sf_type("sf_long_t", NULL, string_from, is_equal, hash_code, NULL, NULL);
}


static int
hash_code(sf_any_t self)
{
  sf_long_t long_int = self;
  return SF_HASH_LONG(long_int->value);
}


static bool
is_equal(sf_any_t self, sf_any_t other)
{
  sf_long_t long_int = self;
  sf_long_t other_long_int = other;
  return long_int->value == other_long_int->value;
}


sf_long_t
sf_long(long value)
{
  struct _sf_long *long_int = sf_object_calloc(sizeof(struct _sf_long), sf_long_type);
  if ( ! long_int) return NULL;
  
  long_int->value = value;
  
  return sf_move_to_temp_pool(long_int);
}


long
sf_long_value(sf_long_t long_int)
{
  return long_int ? long_int->value : 0;
}


static sf_string_t 
string_from(sf_any_t self)
{
  sf_long_t long_int = self;
  return sf_string_from_format("%liL", long_int->value);
}
