#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_TEST_CASE(sf_array_from_collection_with_NULL_returns_NULL)
{
  sf_array_t array = sf_array_from_collection(NULL);
  SF_ASSERT_NULL(array);
}


SF_TEST_CASE(sf_array_from_collection_with_one_item)
{
  sf_string_t item1 = sf_string("foo");
  sf_list_t collection = sf_list_from_items(item1);
  sf_array_t array = sf_array_from_collection(collection);
  SF_ASSERT_IS_EQ(sf_array_item_at_index(array, 0), item1);
  SF_ASSERT_INT_EQ(sf_count(array), 1);
}


SF_TEST_SUITE(sf_array_from_collection_tests,
              sf_array_from_collection_with_NULL_returns_NULL,
              sf_array_from_collection_with_one_item
              );
