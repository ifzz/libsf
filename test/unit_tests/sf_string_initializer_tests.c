#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_TEST_CASE(sf_string_with_NULL)
{
  sf_string_t string = sf_string(NULL);
  SF_ASSERT_NULL(string);
}


SF_TEST_CASE(sf_string_with_empty_string)
{
  sf_string_t string = sf_string("");
  SF_ASSERT_NOT_NULL(string);
  SF_ASSERT_C_STR_EQ(sf_string_chars(string), "");
  SF_ASSERT_INT_EQ(sf_string_length(string), 0);
}


SF_TEST_CASE(sf_string_with_one_ascii_character)
{
  sf_string_t string = sf_string("x");
  SF_ASSERT_NOT_NULL(string);
  SF_ASSERT_C_STR_EQ(sf_string_chars(string), "x");
  SF_ASSERT_INT_EQ(sf_string_length(string), 1);
}


SF_TEST_CASE(sf_string_with_many_ascii_characters)
{
  sf_string_t string = sf_string("foobar");
  SF_ASSERT_NOT_NULL(string);
  SF_ASSERT_C_STR_EQ(sf_string_chars(string), "foobar");
  SF_ASSERT_INT_EQ(sf_string_length(string), 6);
}


SF_TEST_SUITE(sf_string_initializer_tests,
              sf_string_with_NULL,
              sf_string_with_empty_string,
              sf_string_with_one_ascii_character,
              sf_string_with_many_ascii_characters
              );
