#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_TEST_CASE(sf_list_from_collection_with_NULL_returns_NULL)
{
  sf_list_t list = sf_list_from_collection(NULL);
  SF_ASSERT_NULL(list);
}


SF_TEST_CASE(sf_list_from_collection_for_list_returns_list)
{
  sf_string_t item1 = sf_string("A");
  sf_int_t item2 = sf_int(42);
  sf_list_t list_in = sf_list_from_items(item1, item2);
  
  sf_list_t list_out = sf_list_from_collection(list_in);
  
  SF_ASSERT_INT_EQ(sf_count(list_out), 2);
  SF_ASSERT_IS_EQ(sf_list_head(list_out), item1);
  sf_list_t tail = sf_list_tail(list_out);
  SF_ASSERT_IS_EQ(sf_list_head(tail), item2);
}


SF_TEST_CASE(sf_list_from_collection_for_array_returns_list)
{
  sf_string_t item1 = sf_string("A");
  sf_int_t item2 = sf_int(42);
  sf_array_t array_in = sf_array_from_items(item1, item2);
  
  sf_list_t list_out = sf_list_from_collection(array_in);
  
  SF_ASSERT_INT_EQ(sf_count(list_out), 2);
  SF_ASSERT_IS_EQ(sf_list_head(list_out), item1);
  sf_list_t tail = sf_list_tail(list_out);
  SF_ASSERT_IS_EQ(sf_list_head(tail), item2);
}


SF_TEST_SUITE(sf_list_from_collections_tests,
              sf_list_from_collection_with_NULL_returns_NULL,
              sf_list_from_collection_for_list_returns_list,
              sf_list_from_collection_for_array_returns_list
              );
