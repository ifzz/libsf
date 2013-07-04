#include <sf/sf.h>
#include <sf_test/sf_test.h>


static unsigned short const random_state[3] = { 31, 37, 41 };


SF_TEST_CASE(sf_array_shuffled_with_NULL_shuffled_NULL)
{
  sf_random_t random_in = sf_random_from_state(random_state);
  sf_random_t random_out = NULL;
  
  sf_array_t shuffled = sf_array_shuffled(NULL, random_in, &random_out);
  
  SF_ASSERT_NULL(shuffled);
  SF_ASSERT_PTR_EQ(random_out, random_in);
}


SF_TEST_CASE(sf_array_shuffled_with_one_item_returns_same_array)
{
  sf_random_t random_in = sf_random_from_state(random_state);
  sf_random_t random_out = NULL;
  sf_string_t item1 = sf_string("one");
  sf_array_t array = sf_array_from_items(item1);
  
  sf_array_t shuffled = sf_array_shuffled(array, random_in, &random_out);
  
  SF_ASSERT_PTR_EQ(shuffled, array);
  SF_ASSERT_PTR_EQ(random_out, random_in);
}


SF_TEST_CASE(sf_array_shuffled_with_two_items)
{
  sf_random_t random_in = sf_random_from_state(random_state);
  sf_random_t random_out = NULL;
  sf_string_t item1 = sf_string("one");
  sf_string_t item2 = sf_string("two");
  sf_array_t array = sf_array_from_items(item1, item2);
  
  sf_array_t shuffled = sf_array_shuffled(array, random_in, &random_out);
  
  SF_ASSERT_INT_EQ(sf_count(shuffled), 2);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(shuffled, 0), item2);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(shuffled, 1), item1);
  SF_ASSERT_NOT_NULL(random_out);
  SF_ASSERT_PTR_NOT_EQ(random_out, random_in);
}


SF_TEST_CASE(sf_array_shuffled_with_three_items)
{
  sf_random_t random_in = sf_random_from_state(random_state);
  sf_random_t random_out = NULL;
  sf_string_t item1 = sf_string("one");
  sf_string_t item2 = sf_string("two");
  sf_string_t item3 = sf_string("three");
  sf_array_t array = sf_array_from_items(item1, item2, item3);
  
  sf_array_t shuffled = sf_array_shuffled(array, random_in, &random_out);
  
  SF_ASSERT_INT_EQ(sf_count(shuffled), 3);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(shuffled, 0), item2);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(shuffled, 1), item3);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(shuffled, 2), item1);
  SF_ASSERT_NOT_NULL(random_out);
  SF_ASSERT_PTR_NOT_EQ(random_out, random_in);
}


SF_TEST_CASE(sf_array_shuffled_with_100_items)
{
  int count = 100;
  sf_random_t random_in = sf_random_from_state(random_state);
  sf_random_t random_out = NULL;
  sf_list_t list = NULL;
  for (int i = 0; i < count; ++i) {
    list = sf_list(sf_int(i), list);
  }
  sf_array_t array = sf_array_from_collection(list);
  
  sf_array_t shuffled = sf_array_shuffled(array, random_in, &random_out);
  
  SF_ASSERT_INT_EQ(sf_count(shuffled), count);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(shuffled, 0), sf_int(71));
  SF_ASSERT_IS_EQ(sf_array_item_at_index(shuffled, 1), sf_int(31));
  SF_ASSERT_IS_EQ(sf_array_item_at_index(shuffled, 2), sf_int(60));
  // ...
  SF_ASSERT_IS_EQ(sf_array_item_at_index(shuffled, 97), sf_int(43));
  SF_ASSERT_IS_EQ(sf_array_item_at_index(shuffled, 98), sf_int(11));
  SF_ASSERT_IS_EQ(sf_array_item_at_index(shuffled, 99), sf_int(87));
  SF_ASSERT_PTR_NOT_EQ(random_out, random_in);
}


SF_TEST_CASE(sf_array_shuffled_with_1000_items)
{
  int count = 1000;
  sf_random_t random_in = sf_random_from_state(random_state);
  sf_random_t random_out = NULL;
  sf_list_t list = NULL;
  for (int i = 0; i < count; ++i) {
    list = sf_list(sf_int(i), list);
  }
  sf_array_t array = sf_array_from_collection(list);
  
  sf_array_t shuffled = sf_array_shuffled(array, random_in, &random_out);
  
  SF_ASSERT_INT_EQ(sf_count(shuffled), count);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(shuffled, 0), sf_int(212));
  SF_ASSERT_IS_EQ(sf_array_item_at_index(shuffled, 1), sf_int(18));
  SF_ASSERT_IS_EQ(sf_array_item_at_index(shuffled, 2), sf_int(870));
  // ...
  SF_ASSERT_IS_EQ(sf_array_item_at_index(shuffled, 997), sf_int(879));
  SF_ASSERT_IS_EQ(sf_array_item_at_index(shuffled, 998), sf_int(344));
  SF_ASSERT_IS_EQ(sf_array_item_at_index(shuffled, 999), sf_int(887));
  SF_ASSERT_PTR_NOT_EQ(random_out, random_in);
}


SF_TEST_SUITE(sf_array_shuffled_tests,
              sf_array_shuffled_with_NULL_shuffled_NULL,
              sf_array_shuffled_with_one_item_returns_same_array,
              sf_array_shuffled_with_two_items,
              sf_array_shuffled_with_three_items,
              sf_array_shuffled_with_100_items,
              sf_array_shuffled_with_1000_items
              );
