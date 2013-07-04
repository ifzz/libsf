#include "sf_key.h"

#include "sf_object.h"
#include "sf_type.h"


int
sf_default_method_hash_code(sf_any_t key)
{
  return 0;
}


bool
sf_default_method_is_equal(sf_any_t key, sf_any_t other_key)
{
  return false;
}


int
sf_hash_code(sf_any_t key)
{
  if ( ! key) return 0;
  sf_type_t type = sf_type_of(key);
  return sf_type_method_hash_code(type)(key);
}


bool
sf_is_equal(sf_any_t key, sf_any_t other_key)
{
  if (key == other_key) return true;
  if (not key) return false;
  if (not other_key) return false;
  
  sf_type_t type = sf_type_of(key);
  sf_type_t other_type = sf_type_of(other_key);
  if (type != other_type) return false;
  
  return sf_type_method_is_equal(type)(key, other_key);
}


bool
sf_is_key_type(sf_any_t any)
{
  sf_type_t type = sf_type_of(any);
  return sf_type_is_key_type(type);
}
