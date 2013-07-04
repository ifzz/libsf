#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_TEST_CASE(sf_list_reversed_with_NULL_returns_NULL)
{
  sf_list_t reversed = sf_list_reversed(NULL);
  SF_ASSERT_NULL(reversed);
}


SF_TEST_CASE(sf_list_reversed_with_one_item_returns_same_list)
{
  sf_string_t item1 = sf_string("one");
  sf_list_t list = sf_list(item1, NULL);
  sf_list_t reversed = sf_list_reversed(list);
  SF_ASSERT_PTR_EQ(reversed, list);
}


SF_TEST_CASE(sf_list_reversed_with_two_items)
{
  sf_string_t item1 = sf_string("one");
  sf_int_t item2 = sf_int(2);
  
  sf_list_t list = sf_list_from_items(item1, item2);
  sf_list_t reversed = sf_list_reversed(list);
  
  SF_ASSERT_INT_EQ(sf_count(reversed), 2);
  SF_ASSERT_IS_EQ(sf_list_head(reversed), item2);
  
  sf_list_t reversed_tail = sf_list_tail(reversed);
  SF_ASSERT_IS_EQ(sf_list_head(reversed_tail), item1);
}


SF_TEST_CASE(sf_list_reversed_with_three_items)
{
  sf_string_t item1 = sf_string("one");
  sf_int_t item2 = sf_int(2);
  sf_type_t item3 = sf_random_type;
  
  sf_list_t list = sf_list_from_items(item1, item2, item3);
  sf_list_t reversed = sf_list_reversed(list);
  
  SF_ASSERT_INT_EQ(sf_count(reversed), 3);
  SF_ASSERT_IS_EQ(sf_list_head(reversed), item3);
  
  sf_list_t reversed_tail1 = sf_list_tail(reversed);
  SF_ASSERT_IS_EQ(sf_list_head(reversed_tail1), item2);
  
  sf_list_t reversed_tail2 = sf_list_tail(reversed_tail1);
  SF_ASSERT_IS_EQ(sf_list_head(reversed_tail2), item1);
}


SF_TEST_SUITE(sf_list_reversed_tests,
              sf_list_reversed_with_NULL_returns_NULL,
              sf_list_reversed_with_one_item_returns_same_list,
              sf_list_reversed_with_two_items,
              sf_list_reversed_with_three_items
              );
