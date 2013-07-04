#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_EXTERN_TEST_SUITE(sf_array_from_collection_tests);
SF_EXTERN_TEST_SUITE(sf_array_from_items_tests);
SF_EXTERN_TEST_SUITE(sf_array_initializer_tests);
SF_EXTERN_TEST_SUITE(sf_array_reversed_tests);
SF_EXTERN_TEST_SUITE(sf_array_shuffled_tests);


SF_TEST_CASE(NULL_sf_array)
{
  sf_array_t array = NULL;
  SF_ASSERT_NULL(sf_array_item_at_index(array, 0));
  SF_ASSERT_INT_EQ(sf_count(array), 0);
}


SF_TEST_CASE(sf_array_item_at_index_returns_NULL_for_invalid_index)
{
  sf_array_t array = sf_array_from_items(sf_string("foo"));
  SF_ASSERT_NOT_NULL(sf_array_item_at_index(array, 0));
  
  SF_ASSERT_NULL(sf_array_item_at_index(array, 1));
  SF_ASSERT_NULL(sf_array_item_at_index(array, 2));
  SF_ASSERT_NULL(sf_array_item_at_index(array, -1));
}


SF_TEST_CASE(sf_string_from_array)
{
  sf_string_t string = sf_string_from(sf_array_from_items(sf_string("one"), sf_int(42), sf_array_type));
  SF_ASSERT_IS_EQ(string, sf_string("[one,42,sf_array_t]"));
}


SF_TEST_SUITE(sf_array_tests,
              NULL_sf_array,
              sf_array_item_at_index_returns_NULL_for_invalid_index,
              sf_string_from_array,
              
              sf_array_from_collection_tests,
              sf_array_from_items_tests,
              sf_array_initializer_tests,
              sf_array_reversed_tests,
              sf_array_shuffled_tests
              );
