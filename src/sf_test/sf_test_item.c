#include "sf_test_item.h"

#include <assert.h>
#include "sf_array.h"
#include "sf_error.h"
#include "sf_list.h"
#include "sf_test_case.h"
#include "sf_test_suite.h"


sf_any_t
sf_test_item(struct sf_test_item const *test_item)
{
  switch (test_item->type) {
    case sf_test_item_type_test_case: return sf_test_case(test_item);
    case sf_test_item_type_test_suite: return sf_test_suite(test_item);
    default:
      SF_FATAL_ERROR("unexpected value (%i) for enum sf_test_item_type", test_item->type);
      return NULL;
  }
}


sf_array_t
sf_test_items_array(struct sf_test_item const **test_items, int count)
{
  if (not count) return NULL;
  assert(test_items);
  
  sf_list_t list = NULL;
  for (int i = 0; i < count; ++i) {
    list = sf_list(sf_test_item(test_items[i]), list);
  }
  return sf_array_from_collection(list);
}
