#include "sf_object.h"

#include <assert.h>
#include <stdlib.h>
#include "sf_memory.h"
#include "sf_string.h"
#include "sf_type.h"


struct _sf_object
{
  SF_OBJECT_FIELDS;
};


char const *
sf_c_string_from(sf_any_t any)
{
  return sf_string_chars(sf_string_from(any));
}


void
sf_default_method_dealloc(sf_any_t any)
{
  // nop
}


sf_string_t
sf_default_method_string_from(sf_any_t any)
{
  sf_type_t type = sf_type_of(any);
  sf_string_t type_name = sf_type_name(type);
  return sf_string_from_format("<%s:%p>", sf_string_chars(type_name), any);
}


void *
sf_object_calloc(size_t size, sf_type_t type)
{
  struct _sf_object *object = sf_calloc(1, size);
  if ( ! object) return NULL;
  
  object->_sf_object_type = sf_retain(type);
  object->_sf_object_ref_count = 1;
  
  return object;
}


void
sf_object_free(sf_any_t any)
{
  sf_object_t object = any;
  
  sf_type_t type = sf_type_of(object);
  sf_type_method_dealloc(type)(object);
  
  if (object != (sf_object_t) object->_sf_object_type) sf_release(object->_sf_object_type);
  
  sf_free((void *) object);
}


void *
sf_object_malloc(size_t size, sf_type_t type)
{
  struct _sf_object *object = sf_malloc(size);
  if ( ! object) return NULL;

  object->_sf_object_type = sf_retain(type);
  object->_sf_object_ref_count = 1;

  return object;
}


int
sf_ref_count(sf_any_t any)
{
  sf_object_t object = any;
  return object ? object->_sf_object_ref_count : 0;
}


void
sf_release(sf_any_t any)
{
  if (not any) return;
  struct _sf_object *object = (void *) any;
  assert(object->_sf_object_ref_count > 0);
  --object->_sf_object_ref_count;
  if ( ! object->_sf_object_ref_count) sf_object_free(object);
}


sf_any_t
sf_retain(sf_any_t any)
{
  if (not any) return any;
  struct _sf_object *object = (void *) any;
  assert(object->_sf_object_ref_count > 0);
  ++object->_sf_object_ref_count;
  return object;    
}


sf_string_t
sf_string_from(sf_any_t any)
{
  if ( ! any) return NULL;
  sf_type_t type = sf_type_of(any);
  return sf_type_method_string_from(type)(any);
}


sf_type_t
sf_type_of(sf_any_t any)
{
  if ( ! any) return NULL;
  sf_object_t object = any;
  return object->_sf_object_type;
}
