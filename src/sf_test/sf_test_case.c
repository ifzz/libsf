#include "sf_test_case.h"

#include "sf_object.h"
#include "sf_temp_pool.h"
#include "sf_test_item.h"
#include "sf_type.h"


static void
dealloc(sf_any_t self);

static sf_string_t
string_from(sf_any_t self);


struct _sf_test_case
{
  SF_OBJECT_FIELDS;
  sf_string_t identifier;
  void (*test_function)(sf_list_t *_sf_test_failures);
};


sf_type_t sf_test_case_type;


void
_sf_test_case_init(void)
{
  sf_test_case_type = sf_type("sf_test_case_t", dealloc, string_from, NULL, NULL, NULL, NULL);
}


static void
dealloc(sf_any_t self)
{
  sf_test_case_t test_case = self;
  sf_release(test_case->identifier);
}


sf_test_case_t
sf_test_case(struct sf_test_item const *test_item)
{
  struct _sf_test_case *test_case = sf_object_calloc(sizeof(struct _sf_test_case), sf_test_case_type);
  if (not test_case) return NULL;
  
  test_case->identifier = sf_retain(sf_string(test_item->identifier));
  test_case->test_function = test_item->test_function;
  
  return sf_move_to_temp_pool(test_case);
}


sf_string_t
sf_test_case_identifier(sf_test_case_t test_case)
{
  return test_case ? sf_copy_to_temp_pool(test_case->identifier) : NULL;
}


sf_list_t
sf_test_case_run(sf_test_case_t test_case)
{
  if (test_case) {
    sf_list_t test_failures = NULL;
    test_case->test_function(&test_failures);
    return test_failures;
  } else {
    return NULL;
  }
}


static sf_string_t
string_from(sf_any_t self)
{
  sf_test_case_t test_case = self;
  return sf_string_from_format("%s", sf_c_string_from(test_case->identifier));
}
