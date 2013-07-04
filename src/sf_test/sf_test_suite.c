#include "sf_test_suite.h"

#include "sf_collection.h"
#include "sf_object.h"
#include "sf_temp_pool.h"
#include "sf_test_item.h"
#include "sf_type.h"


static int
count(sf_any_t self);

static void
dealloc(sf_any_t self);

static bool
each(sf_any_t self, void *context, bool (*act_on)(sf_any_t item, void *context));

static sf_string_t
string_from(sf_any_t self);


struct _sf_test_suite
{
  SF_OBJECT_FIELDS;
  sf_string_t identifier;
  sf_array_t items;
};


sf_type_t sf_test_suite_type;


void
_sf_test_suite_init(void)
{
  sf_test_suite_type = sf_type("sf_test_suite_t", dealloc, string_from, NULL, NULL, NULL, NULL);
}


static int
count(sf_any_t self)
{
  sf_test_suite_t test_suite = self;
  return sf_count(test_suite->items);
}


static void
dealloc(sf_any_t self)
{
  sf_test_suite_t test_suite = self;
  sf_release(test_suite->identifier);
  sf_release(test_suite->items);
}


static bool
each(sf_any_t self, void *context, bool (*act_on)(sf_any_t item, void *context))
{
  sf_test_suite_t test_suite = self;
  return sf_each(test_suite->items, act_on, context);
}


sf_test_suite_t
sf_test_suite(struct sf_test_item const *test_item)
{
  struct _sf_test_suite *test_suite = sf_object_calloc(sizeof(struct _sf_test_suite), sf_test_suite_type);
  if (not test_suite) return NULL;
  
  test_suite->identifier = sf_retain(sf_string(test_item->identifier));
  test_suite->items = sf_retain(test_item->generate_items());
  
  return sf_move_to_temp_pool(test_suite);
}


sf_string_t
sf_test_suite_identifier(sf_test_suite_t test_suite)
{
  return test_suite ? sf_copy_to_temp_pool(test_suite->identifier) : NULL;
}


sf_array_t
sf_test_suite_items(sf_test_suite_t test_suite)
{
  return test_suite ? sf_copy_to_temp_pool(test_suite->items) : NULL;
}


static sf_string_t
string_from(sf_any_t self)
{
  sf_test_suite_t test_suite = self;
  return sf_copy_to_temp_pool(test_suite->identifier);
}
