#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_TEST_CASE(sf_string_from_prefix_and_collection_for_NULL_returns_NULL)
{
  sf_string_t joined = sf_string_from_prefix_and_collection(NULL, NULL);
  SF_ASSERT_NULL(joined);
  
  joined = sf_string_from_prefix_and_collection(sf_string(" + "), NULL);
  SF_ASSERT_NULL(joined);
}


SF_TEST_CASE(sf_string_from_prefix_and_collection_for_list_containing_NULL_returns_prefix)
{
  sf_list_t list = sf_list(NULL, NULL);
  sf_string_t joined = sf_string_from_prefix_and_collection(sf_string(" + "), list);
  SF_ASSERT_IS_EQ(joined, sf_string(" + "));
}


SF_TEST_CASE(sf_string_from_prefix_and_collection_for_list_containing_empty_string_returns_prefix)
{
  sf_string_t empty = sf_string_from_format("");
  sf_list_t list = sf_list(empty, NULL);
  sf_string_t joined = sf_string_from_prefix_and_collection(sf_string(" + "), list);
  SF_ASSERT_IS_EQ(joined, sf_string(" + "));
}


SF_TEST_CASE(sf_string_from_prefix_and_collection_for_list_containing_one_item)
{
  sf_list_t list = sf_list(sf_string("foobar"), NULL);
  sf_string_t joined = sf_string_from_prefix_and_collection(sf_string(" + "), list);
  SF_ASSERT_IS_EQ(joined, sf_string(" + foobar"));
}


SF_TEST_CASE(sf_string_from_prefix_and_collection_for_list_containing_two_items)
{
  sf_list_t list = sf_list_from_items(sf_string("one"), sf_string("two"));
  sf_string_t joined = sf_string_from_prefix_and_collection(sf_string(" + "), list);
  SF_ASSERT_IS_EQ(joined, sf_string(" + one + two"));
}


SF_TEST_CASE(sf_string_from_prefix_and_collection_for_list_containing_three_items)
{
  sf_list_t list = sf_list_from_items(sf_string("one"), sf_int(2), sf_random_type);
  sf_string_t joined = sf_string_from_prefix_and_collection(sf_string(" + "), list);
  SF_ASSERT_IS_EQ(joined, sf_string(" + one + 2 + sf_random_t"));
}


SF_TEST_SUITE(sf_string_from_prefix_and_collection_tests,
              sf_string_from_prefix_and_collection_for_NULL_returns_NULL,
              sf_string_from_prefix_and_collection_for_list_containing_NULL_returns_prefix,
              sf_string_from_prefix_and_collection_for_list_containing_empty_string_returns_prefix,
              sf_string_from_prefix_and_collection_for_list_containing_one_item,
              sf_string_from_prefix_and_collection_for_list_containing_two_items,
              sf_string_from_prefix_and_collection_for_list_containing_three_items
              );
