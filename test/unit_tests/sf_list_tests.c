#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_EXTERN_TEST_SUITE(sf_list_from_collections_tests);
SF_EXTERN_TEST_SUITE(sf_list_from_items_tests);
SF_EXTERN_TEST_SUITE(sf_list_initializer_tests);
SF_EXTERN_TEST_SUITE(sf_list_reversed_tests);


SF_TEST_CASE(NULL_sf_list)
{
  sf_list_t list = NULL;
  SF_ASSERT_NULL(sf_list_head(list));
  SF_ASSERT_NULL(sf_list_tail(list));
  SF_ASSERT_INT_EQ(sf_count(list), 0);
}


SF_TEST_CASE(sf_string_from_list)
{
  sf_string_t string = sf_string_from(sf_list_from_items(sf_string("one"), sf_int(42), sf_array_type));
  SF_ASSERT_IS_EQ(string, sf_string("(one,42,sf_array_t)"));
}


SF_TEST_SUITE(sf_list_tests,
              NULL_sf_list,
              sf_string_from_list,
              
              sf_list_from_collections_tests,
              sf_list_from_items_tests,
              sf_list_initializer_tests,
              sf_list_reversed_tests
              );
