#include <stdlib.h>
#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_TEST_CASE(sf_array_for_1k_items)
{
  int count = 1000;
  sf_any_t *items = sf_calloc(count, sizeof(sf_any_t));
  for (int i = 0; i < count; ++i) {
    items[i] = sf_int(i);
  }
  sf_array_t array = sf_array(items, count);
  sf_free(items);

  for (int i = 0; i < count; ++i) {
    SF_ASSERT_INT_EQ(sf_int_value(sf_array_item_at_index(array, i)), i);
  }
}


SF_TEST_CASE(sf_array_for_10k_items)
{
  int count = 10000;
  sf_any_t *items = sf_calloc(count, sizeof(sf_any_t));
  for (int i = 0; i < count; ++i) {
    items[i] = sf_int(i);
  }
  sf_array_t array = sf_array(items, count);
  sf_free(items);

  for (int i = 0; i < count; ++i) {
    SF_ASSERT_INT_EQ(sf_int_value(sf_array_item_at_index(array, i)), i);
  }
}


SF_TEST_CASE(sf_array_for_100k_items)
{
  int count = 100000;
  sf_any_t *items = sf_calloc(count, sizeof(sf_any_t));
  for (int i = 0; i < count; ++i) {
    items[i] = sf_int(i);
  }
  sf_array_t array = sf_array(items, count);
  sf_free(items);

  for (int i = 0; i < count; ++i) {
    SF_ASSERT_INT_EQ(sf_int_value(sf_array_item_at_index(array, i)), i);
  }
}


SF_TEST_CASE(sf_array_for_1M_items)
{
  int count = 1000000;
  sf_any_t *items = sf_calloc(count, sizeof(sf_any_t));
  for (int i = 0; i < count; ++i) {
    items[i] = sf_int(i);
  }
  sf_array_t array = sf_array(items, count);
  sf_free(items);

  for (int i = 0; i < count; ++i) {
    SF_ASSERT_INT_EQ(sf_int_value(sf_array_item_at_index(array, i)), i);
  }
}


SF_TEST_SUITE(sf_array_stress_tests,
              sf_array_for_1k_items,
              sf_array_for_10k_items,
              sf_array_for_100k_items,
              sf_array_for_1M_items
              );
