#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_TEST_CASE(sf_array_from_items_with_one_item)
{
  sf_string_t item1 = sf_string("foo");
  sf_array_t array = sf_array_from_items(item1);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(array, 0), item1);
  SF_ASSERT_INT_EQ(sf_count(array), 1);
}


SF_TEST_CASE(sf_array_from_items_with_two_items)
{
  sf_string_t item1 = sf_string("foo");
  sf_int_t item2 = sf_int(2);
  sf_array_t array = sf_array_from_items(item1, item2);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(array, 0), item1);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(array, 1), item2);
  SF_ASSERT_INT_EQ(sf_count(array), 2);
}


SF_TEST_CASE(sf_array_from_items_with_three_items)
{
  sf_string_t item1 = sf_string("foo");
  sf_int_t item2 = sf_int(2);
  sf_type_t item3 = sf_random_type;
  sf_array_t array = sf_array_from_items(item1, item2, item3);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(array, 0), item1);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(array, 1), item2);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(array, 2), item3);
  SF_ASSERT_INT_EQ(sf_count(array), 3);
}


SF_TEST_CASE(sf_array_from_items_with_null_item)
{
  sf_int_t item2 = sf_int(2);
  sf_type_t item3 = sf_random_type;
  sf_array_t array = sf_array_from_items(NULL, item2, item3);
  SF_ASSERT_NULL(sf_array_item_at_index(array, 0));
  SF_ASSERT_IS_EQ(sf_array_item_at_index(array, 1), item2);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(array, 2), item3);
  SF_ASSERT_INT_EQ(sf_count(array), 3);
}


SF_TEST_SUITE(sf_array_from_items_tests,
              sf_array_from_items_with_one_item,
              sf_array_from_items_with_two_items,
              sf_array_from_items_with_three_items,
              sf_array_from_items_with_null_item
              );
