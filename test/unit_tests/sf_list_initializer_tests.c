#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_TEST_CASE(sf_list_with_NULLs)
{
  sf_list_t list = sf_list(NULL, NULL);
  SF_ASSERT_NULL(sf_list_head(list));
  SF_ASSERT_NULL(sf_list_tail(list));
  SF_ASSERT_INT_EQ(sf_count(list), 1);
}


SF_TEST_CASE(sf_list_with_one_item)
{
  sf_string_t item1 = sf_string("foo");
  sf_list_t list = sf_list(item1, NULL);
  SF_ASSERT_IS_EQ(sf_list_head(list), item1);
  SF_ASSERT_NULL(sf_list_tail(list));
  SF_ASSERT_INT_EQ(sf_count(list), 1);
}


SF_TEST_CASE(sf_list_with_two_items)
{
  sf_string_t item1 = sf_string("one");
  sf_string_t item2 = sf_string("two");
  
  sf_list_t list1 = sf_list(item1, NULL);
  sf_list_t list2 = sf_list(item2, list1);
  
  SF_ASSERT_IS_EQ(sf_list_head(list1), item1);
  SF_ASSERT_NULL(sf_list_tail(list1));
  SF_ASSERT_INT_EQ(sf_count(list1), 1);
  
  SF_ASSERT_IS_EQ(sf_list_head(list2), item2);
  SF_ASSERT_IS_EQ(sf_list_tail(list2), list1);  
  SF_ASSERT_INT_EQ(sf_count(list2), 2);
}


SF_TEST_CASE(sf_list_with_three_items)
{
  sf_string_t item1 = sf_string("one");
  sf_int_t item2 = sf_int(2);
  sf_type_t item3 = sf_random_type;
  
  sf_list_t list1 = sf_list(item1, NULL);
  sf_list_t list2 = sf_list(item2, list1);
  sf_list_t list3 = sf_list(item3, list2);
  
  SF_ASSERT_IS_EQ(sf_list_head(list1), item1);
  SF_ASSERT_NULL(sf_list_tail(list1));
  SF_ASSERT_INT_EQ(sf_count(list1), 1);
  
  SF_ASSERT_IS_EQ(sf_list_head(list2), item2);
  SF_ASSERT_IS_EQ(sf_list_tail(list2), list1);
  SF_ASSERT_INT_EQ(sf_count(list2), 2);
  
  SF_ASSERT_IS_EQ(sf_list_head(list3), item3);
  SF_ASSERT_IS_EQ(sf_list_tail(list3), list2);
  SF_ASSERT_INT_EQ(sf_count(list3), 3);
}


SF_TEST_CASE(sf_list_with_same_tail)
{
  sf_string_t item1 = sf_string("one");
  sf_int_t item2 = sf_int(2);
  sf_type_t item_b = sf_random_type;
  
  sf_list_t list1 = sf_list(item1, NULL);
  sf_list_t list2 = sf_list(item2, list1);
  sf_list_t list_b = sf_list(item_b, list1);
  
  SF_ASSERT_IS_EQ(sf_list_head(list1), item1);
  SF_ASSERT_NULL(sf_list_tail(list1));
  SF_ASSERT_INT_EQ(sf_count(list1), 1);
  
  SF_ASSERT_IS_EQ(sf_list_head(list2), item2);
  SF_ASSERT_IS_EQ(sf_list_tail(list2), list1);
  SF_ASSERT_INT_EQ(sf_count(list2), 2);
  
  SF_ASSERT_IS_EQ(sf_list_head(list_b), item_b);
  SF_ASSERT_IS_EQ(sf_list_tail(list_b), list1);
  SF_ASSERT_INT_EQ(sf_count(list_b), 2);
}


SF_TEST_CASE(sf_list_with_three_items_including_NULL)
{
  sf_string_t item1 = sf_string("one");
  sf_int_t item2 = NULL;
  sf_type_t item3 = sf_random_type;
  
  sf_list_t list1 = sf_list(item1, NULL);
  sf_list_t list2 = sf_list(item2, list1);
  sf_list_t list3 = sf_list(item3, list2);
  
  SF_ASSERT_IS_EQ(sf_list_head(list1), item1);
  SF_ASSERT_NULL(sf_list_tail(list1));
  SF_ASSERT_INT_EQ(sf_count(list1), 1);
  
  SF_ASSERT_NULL(sf_list_head(list2));
  SF_ASSERT_IS_EQ(sf_list_tail(list2), list1);
  SF_ASSERT_INT_EQ(sf_count(list2), 2);
  
  SF_ASSERT_IS_EQ(sf_list_head(list3), item3);
  SF_ASSERT_IS_EQ(sf_list_tail(list3), list2);
  SF_ASSERT_INT_EQ(sf_count(list3), 3);
}


SF_TEST_CASE(sf_list_with_many_items)
{
  int count = 1000;
  sf_list_t list = NULL;
  for (int i = 0; i < count; ++i) {
    list = sf_list(sf_int(i), list);
  }
  
  SF_ASSERT_INT_EQ(sf_count(list), count);
  int i = count - 1;
  while (list) {
    SF_ASSERT_IS_EQ(sf_list_head(list), sf_int(i));
    list = sf_list_tail(list);
    --i;
  }
}


SF_TEST_SUITE(sf_list_initializer_tests,
              sf_list_with_NULLs,
              sf_list_with_one_item,
              sf_list_with_two_items,
              sf_list_with_three_items,
              sf_list_with_same_tail,
              sf_list_with_three_items_including_NULL,
              sf_list_with_many_items
              );
