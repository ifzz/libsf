#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_EXTERN_TEST_SUITE(sf_string_from_prefix_and_collection_tests);
SF_EXTERN_TEST_SUITE(sf_string_from_separator_and_collection_tests);
SF_EXTERN_TEST_SUITE(sf_string_from_suffix_and_collection_tests);
SF_EXTERN_TEST_SUITE(sf_string_initializer_tests);


SF_TEST_CASE(NULL_sf_string)
{
  sf_string_t string = NULL;
  SF_ASSERT_NOT_NULL(sf_string_chars(string));
  SF_ASSERT_C_STR_EQ(sf_string_chars(string), "");
  SF_ASSERT_INT_EQ(sf_string_length(string), 0);
}


SF_TEST_SUITE(sf_string_tests,
              NULL_sf_string,
              sf_string_initializer_tests,
              sf_string_from_prefix_and_collection_tests,
              sf_string_from_separator_and_collection_tests,
              sf_string_from_suffix_and_collection_tests
              );
