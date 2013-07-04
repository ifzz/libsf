#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_TEST_CASE(sf_list_from_items_with_one_item)
{
  sf_list_t list = sf_list_from_items(sf_string("one"));
  SF_ASSERT_INT_EQ(sf_count(list), 1);
  SF_ASSERT_IS_EQ(sf_list_head(list), sf_string("one"));
}


SF_TEST_CASE(sf_list_from_items_with_two_items)
{
  sf_list_t list = sf_list_from_items(sf_string("one"), sf_int(2));
  SF_ASSERT_INT_EQ(sf_count(list), 2);
  SF_ASSERT_IS_EQ(sf_list_head(list), sf_string("one"));
  
  sf_list_t tail = sf_list_tail(list);
  SF_ASSERT_IS_EQ(sf_list_head(tail), sf_int(2));
}


SF_TEST_CASE(sf_list_from_items_with_three_items)
{
  sf_list_t list = sf_list_from_items(sf_string("one"), sf_int(2), sf_random_type);
  SF_ASSERT_INT_EQ(sf_count(list), 3);
  SF_ASSERT_IS_EQ(sf_list_head(list), sf_string("one"));
  
  sf_list_t tail1 = sf_list_tail(list);
  SF_ASSERT_IS_EQ(sf_list_head(tail1), sf_int(2));
  
  sf_list_t tail2 = sf_list_tail(tail1);
  SF_ASSERT_IS_EQ(sf_list_head(tail2), sf_random_type);
}


SF_TEST_CASE(sf_list_from_items_with_NULL_item)
{
  sf_list_t list = sf_list_from_items(NULL, sf_string("two"), sf_int(3));
  SF_ASSERT_INT_EQ(sf_count(list), 3);
  SF_ASSERT_NULL(sf_list_head(list));
}


SF_TEST_SUITE(sf_list_from_items_tests,
              sf_list_from_items_with_one_item,
              sf_list_from_items_with_two_items,
              sf_list_from_items_with_three_items,
              sf_list_from_items_with_NULL_item
              );
