#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_TEST_CASE(sf_array_reversed_with_NULL_returns_NULL)
{
  sf_array_t reversed = sf_array_reversed(NULL);
  SF_ASSERT_NULL(reversed);
}


SF_TEST_CASE(sf_array_reversed_with_one_item_returns_same_array)
{
  sf_string_t item1 = sf_string("one");
  sf_array_t array = sf_array_from_items(item1);
  sf_array_t reversed = sf_array_reversed(array);
  SF_ASSERT_PTR_EQ(reversed, array);
}


SF_TEST_CASE(sf_array_reversed_with_two_items)
{
  sf_string_t item1 = sf_string("one");
  sf_int_t item2 = sf_int(2);
  
  sf_array_t array = sf_array_from_items(item1, item2);
  sf_array_t reversed = sf_array_reversed(array);
  
  SF_ASSERT_INT_EQ(sf_count(reversed), 2);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(reversed, 0), item2);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(reversed, 1), item1);
}


SF_TEST_CASE(sf_array_reversed_with_three_items)
{
  sf_string_t item1 = sf_string("one");
  sf_int_t item2 = sf_int(2);
  sf_type_t item3 = sf_random_type;
  
  sf_array_t array = sf_array_from_items(item1, item2, item3);
  sf_array_t reversed = sf_array_reversed(array);
  
  SF_ASSERT_INT_EQ(sf_count(reversed), 3);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(reversed, 0), item3);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(reversed, 1), item2);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(reversed, 2), item1);
}


SF_TEST_CASE(sf_array_reversed_from_list)
{
  sf_string_t item1 = sf_string("one");
  sf_int_t item2 = sf_int(2);
  sf_type_t item3 = sf_random_type;
  sf_list_t list = sf_list_from_items(item1, item2, item3);
  
  sf_array_t reversed = sf_array_reversed(list);
  
  SF_ASSERT_INT_EQ(sf_count(reversed), 3);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(reversed, 0), item3);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(reversed, 1), item2);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(reversed, 2), item1);
}


SF_TEST_CASE(sf_array_reversed_from_list_with_one_item)
{
  sf_string_t item1 = sf_string("one");
  sf_list_t list = sf_list_from_items(item1);
  
  sf_array_t reversed = sf_array_reversed(list);
  
  SF_ASSERT_PTR_NOT_EQ(reversed, list);
  SF_ASSERT_INT_EQ(sf_count(reversed), 1);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(reversed, 0), item1);
}


SF_TEST_SUITE(sf_array_reversed_tests,
              sf_array_reversed_with_NULL_returns_NULL,
              sf_array_reversed_with_one_item_returns_same_array,
              sf_array_reversed_with_two_items,
              sf_array_reversed_with_three_items,
              sf_array_reversed_from_list,
              sf_array_reversed_from_list_with_one_item
              );
