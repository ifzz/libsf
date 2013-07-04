#include <stdlib.h>
#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_TEST_CASE(sf_array_with_NULL_items_returns_NULL)
{
  sf_array_t array = sf_array(NULL, 1);
  SF_ASSERT_NULL(array);
}


SF_TEST_CASE(sf_array_with_zero_count_returns_NULL)
{
  sf_any_t items[] = { sf_string("one") };
  sf_array_t array = sf_array(items, 0);
  SF_ASSERT_NULL(array);
}


SF_TEST_CASE(sf_array_with_one_item)
{
  sf_any_t items[] = { sf_string("one") };
  sf_array_t array = sf_array(items, 1);
  SF_ASSERT_NOT_NULL(array);
  SF_ASSERT_INT_EQ(sf_count(array), 1);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(array, 0), items[0]);
  SF_ASSERT_PTR_NOT_EQ(sf_array_items(array), items);
}


SF_TEST_CASE(sf_array_retains_items)
{
  sf_string_t item1 = sf_string("one");
  sf_any_t items[] = { item1 };
  SF_ASSERT_INT_EQ(sf_ref_count(item1), 1);
  
  sf_array_t array = sf_array(items, 1);
  
  SF_ASSERT_NOT_NULL(array);
  SF_ASSERT_INT_EQ(sf_count(array), 1);
  SF_ASSERT_INT_EQ(sf_ref_count(item1), 2);
  
  SF_ASSERT_IS_EQ(sf_array_item_at_index(array, 0), item1);
}


SF_TEST_CASE(sf_array_with_many_items)
{
  int count = 1000;
  sf_any_t *items = sf_calloc(count, sizeof(sf_any_t));
  for (int i = 0; i < count; ++i) {
    items[i] = sf_int(i);
  }
  
  sf_array_t array = sf_array(items, count);
  sf_free(items);

  SF_ASSERT_INT_EQ(sf_count(array), count);
  for (int i = 0; i < count; ++i) {
    SF_ASSERT_IS_EQ(sf_array_item_at_index(array, i), sf_int(i));
  }
}


SF_TEST_SUITE(sf_array_initializer_tests,
              sf_array_with_NULL_items_returns_NULL,
              sf_array_with_zero_count_returns_NULL,
              sf_array_with_one_item,
              sf_array_retains_items,
              sf_array_with_many_items
              );
