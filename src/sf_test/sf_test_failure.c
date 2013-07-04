#include "sf_test_failure.h"

#include "sf_object.h"
#include "sf_string.h"
#include "sf_temp_pool.h"
#include "sf_type.h"


static void
dealloc(sf_any_t self);

static sf_string_t
string_from(sf_any_t self);


struct _sf_test_failure
{
  SF_OBJECT_FIELDS;
  sf_string_t file;
  int line;
  sf_string_t description;
};


sf_type_t sf_test_failure_type;


void
_sf_test_failure_init(void)
{
  sf_test_failure_type = sf_type("sf_test_failure_t", dealloc, string_from, NULL, NULL, NULL, NULL);
}


static void
dealloc(sf_any_t self)
{
  sf_test_failure_t test_failure = self;
  
  sf_release(test_failure->file);
  sf_release(test_failure->description);
}


sf_string_t
sf_test_failure_description(sf_test_failure_t test_failure)
{
  return test_failure ? sf_copy_to_temp_pool(test_failure->description) : NULL;
}


sf_test_failure_t
sf_test_failure(char const *file, int line, sf_string_t description)
{
  struct _sf_test_failure *test_failure = sf_object_calloc(sizeof(struct _sf_test_failure), sf_test_failure_type);
  if ( ! test_failure) return NULL;
  
  test_failure->file = sf_retain(sf_string(file));
  test_failure->line = line;
  test_failure->description = sf_retain(description);
  
  return sf_move_to_temp_pool(test_failure);
}


sf_string_t
sf_test_failure_file(sf_test_failure_t test_failure)
{
  return test_failure ? sf_copy_to_temp_pool(test_failure->file) : NULL;
}


int
sf_test_failure_line(sf_test_failure_t test_failure)
{
  return test_failure ? test_failure->line : 0;
}


static sf_string_t
string_from(sf_any_t self)
{
  sf_test_failure_t test_failure = self;
  return sf_string_from_format("%s:%i: %s",
                               sf_c_string_from(test_failure->file),
                               test_failure->line,
                               sf_c_string_from(test_failure->description));
}
