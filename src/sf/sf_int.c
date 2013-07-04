#include "sf_int.h"

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


struct _sf_int
{
  SF_OBJECT_FIELDS;
  int value;
};


sf_type_t sf_int_type;


void
_sf_int_init(void)
{
  sf_int_type = sf_type("sf_int_t", NULL, string_from, is_equal, hash_code, NULL, NULL);
}


static int
hash_code(sf_any_t self)
{
  sf_int_t integer = self;
  return SF_HASH_INT(integer->value);
}


static bool
is_equal(sf_any_t self, sf_any_t other)
{
  sf_int_t integer = self;
  sf_int_t other_integer = other;
  return integer->value == other_integer->value;
}


sf_int_t
sf_int(int value)
{
  struct _sf_int *integer = sf_object_calloc(sizeof(struct _sf_int), sf_int_type);
  if ( ! integer) return NULL;
  
  integer->value = value;
  
  return sf_move_to_temp_pool(integer);
}


int
sf_int_value(sf_int_t integer)
{
  return integer ? integer->value : 0;
}


static sf_string_t 
string_from(sf_any_t self)
{
  sf_int_t integer = self;
  return sf_string_from_format("%i", integer->value);
}
