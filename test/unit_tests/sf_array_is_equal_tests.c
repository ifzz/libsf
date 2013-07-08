#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_TEST_CASE(sf_array_empty_arrays_are_equal)
{
  sf_array_t array1 = sf_array(NULL, 0);
  sf_array_t array2 = sf_array(NULL, 0);
  SF_ASSERT_IS_EQ(array1, array2);
}


SF_TEST_CASE(sf_arrays_with_same_item_are_equal)
{
  sf_string_t item1 = sf_string("foobar");
  sf_array_t array1 = sf_array_from_items(item1);
  sf_array_t array2 = sf_array_from_items(item1);
  SF_ASSERT_IS_EQ(array1, array2);
}


SF_TEST_CASE(sf_arrays_with_different_item_are_not_equal)
{
  sf_string_t item1 = sf_string("foobar");
  sf_string_t item2 = sf_string("barf");
  sf_array_t array1 = sf_array_from_items(item1);
  sf_array_t array2 = sf_array_from_items(item2);
  SF_ASSERT_IS_NOT_EQ(array1, array2);
}


SF_TEST_CASE(sf_arrays_with_different_counts_are_not_equal)
{
  sf_string_t item1 = sf_string("foobar");
  sf_string_t item2 = sf_string("barf");
  sf_array_t array1 = sf_array_from_items(item1);
  sf_array_t array2 = sf_array_from_items(item1, item2);
  SF_ASSERT_IS_NOT_EQ(array1, array2);
}


SF_TEST_CASE(sf_arrays_with_different_order_are_not_equal)
{
  sf_string_t item1 = sf_string("foobar");
  sf_string_t item2 = sf_string("barf");
  sf_int_t item3 = sf_int(42);
  sf_array_t array1 = sf_array_from_items(item1, item2, item3);
  sf_array_t array2 = sf_array_from_items(item2, item1, item3);
  SF_ASSERT_IS_NOT_EQ(array1, array2);
}


SF_TEST_SUITE(sf_array_is_equal_tests,
              
              sf_array_empty_arrays_are_equal,
              sf_arrays_with_same_item_are_equal,
              sf_arrays_with_different_item_are_not_equal,
              sf_arrays_with_different_counts_are_not_equal,
              sf_arrays_with_different_order_are_not_equal
              );
