#include "sf_type.h"

#include <stdlib.h>
#include <string.h>
#include "sf_collection.h"
#include "sf_key.h"
#include "sf_memory.h"
#include "sf_object.h"
#include "sf_temp_pool.h"


static void
dealloc(sf_any_t self);

static int
hash_code(sf_any_t self);

static bool
is_equal(sf_any_t self, sf_any_t other);

static sf_string_t
string_from(sf_any_t self);

static sf_type_t
type(bool is_type_type,
     char const *name,
     sf_method_dealloc dealloc,
     sf_method_string_from string_from,
     sf_method_is_equal is_equal,
     sf_method_hash_code hash_code,
     sf_method_count count,
     sf_method_each each);


struct _sf_type
{
  SF_OBJECT_FIELDS;
  char *name;
  
  // object methods
  void (*dealloc)(sf_any_t self);
  sf_string_t (*string_from)(sf_any_t self);
  
  // key methods
  bool (*is_equal)(sf_any_t self, sf_any_t other);
  int (*hash_code)(sf_any_t self);
  
  // collection methods
  int (*count)(sf_any_t self);
  bool (*each)(sf_any_t self, sf_act_on act_on, void *context);
};


sf_type_t sf_type_type;


void
_sf_type_init(void)
{
  sf_type_type = type(true, "sf_type_t", dealloc, string_from, is_equal, hash_code, NULL, NULL);
}


static void
dealloc(sf_any_t self)
{
  sf_type_t type = self;
  sf_free(type->name);
}


static int
hash_code(sf_any_t self)
{
  sf_type_t type = self;
  return sf_hash_code(type->name);
}


static bool
is_equal(sf_any_t self, sf_any_t other)
{
  return false;
}


sf_type_t
sf_type(char const *name,
        sf_method_dealloc dealloc,
        sf_method_string_from string_from,
        sf_method_is_equal is_equal,
        sf_method_hash_code hash_code,
        sf_method_count count,
        sf_method_each each)
{
  return type(false, name, dealloc, string_from, is_equal, hash_code, count, each);
}


bool
sf_type_is_collection_type(sf_type_t type)
{
  return type and type->count and type->each;
}


bool
sf_type_is_key_type(sf_type_t type)
{
  return type and type->hash_code and type->is_equal;
}


sf_method_count
sf_type_method_count(sf_type_t type)
{
  return type and type->count ? type->count : sf_default_method_count;
}


sf_method_dealloc
sf_type_method_dealloc(sf_type_t type)
{
  return type and type->dealloc ? type->dealloc : sf_default_method_dealloc;
}


sf_method_each
sf_type_method_each(sf_type_t type)
{
  return type and type->each ? type->each : sf_default_method_each;
}


sf_method_hash_code
sf_type_method_hash_code(sf_type_t type)
{
  return type and type->hash_code ? type->hash_code : sf_default_method_hash_code;
}


sf_method_is_equal
sf_type_method_is_equal(sf_type_t type)
{
  return type and type->is_equal ? type->is_equal : sf_default_method_is_equal;
}


sf_method_string_from
sf_type_method_string_from(sf_type_t type)
{
  return type and type->string_from ? type->string_from : sf_default_method_string_from;
}


sf_string_t
sf_type_name(sf_type_t type)
{
  return type ? sf_copy_to_temp_pool(type->name) : NULL;
}


static sf_string_t
string_from(sf_any_t self)
{
  sf_type_t type = self;
  return sf_string(type->name);
}


static sf_type_t
type(bool is_type_type,
     char const *name,
     sf_method_dealloc dealloc,
     sf_method_string_from string_from,
     sf_method_is_equal is_equal,
     sf_method_hash_code hash_code,
     sf_method_count count,
     sf_method_each each)
{
  struct _sf_type *type = sf_object_calloc(sizeof(struct _sf_type), sf_type_type);
  if ( ! type) return NULL;
  
  if (is_type_type) type->_sf_object_type = type;
  
  type->name = sf_strdup(name);
  type->dealloc = dealloc;
  type->string_from = string_from;
  type->is_equal = is_equal;
  type->hash_code = hash_code;
  type->count = count;
  type->each = each;
  
  return sf_move_to_temp_pool(type);
}
