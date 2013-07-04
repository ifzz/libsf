#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_TEST_CASE(sf_assert_c_string_equals_passes)
{
  sf_list_t failures = NULL;
  
  bool result = sf_assert_c_string_equals("/test/file", 42, "string", "foobar", "foobar", "foobar", &failures);
  
  SF_ASSERT_TRUE(result);
  SF_ASSERT_NULL(failures);
}


SF_TEST_CASE(sf_assert_c_string_equals_fails)
{
  sf_list_t failures = NULL;
  
  bool result = sf_assert_c_string_equals("/test/file", 42, "string", "foobar", "fnord", "fnord", &failures);
  
  SF_ASSERT_FALSE(result);
  SF_ASSERT_NOT_NULL(failures);
  SF_ASSERT_INT_EQ(sf_count(failures), 1);
  sf_test_failure_t failure = sf_list_head(failures);
  SF_ASSERT_IS_EQ(sf_test_failure_file(failure), sf_string("/test/file"));
  SF_ASSERT_INT_EQ(sf_test_failure_line(failure), 42);
  SF_ASSERT_IS_EQ(sf_test_failure_description(failure), sf_string("(string) { \"foobar\" } expected to equal (\"fnord\")"));
}


SF_TEST_CASE(sf_assert_c_string_equals_fails_for_NULL_actual_value)
{
  sf_list_t failures = NULL;
  
  bool result = sf_assert_c_string_equals("/test/file", 42, "string", NULL, "fnord", "fnord", &failures);
  
  SF_ASSERT_FALSE(result);
  SF_ASSERT_NOT_NULL(failures);
  SF_ASSERT_INT_EQ(sf_count(failures), 1);
  sf_test_failure_t failure = sf_list_head(failures);
  SF_ASSERT_IS_EQ(sf_test_failure_file(failure), sf_string("/test/file"));
  SF_ASSERT_INT_EQ(sf_test_failure_line(failure), 42);
  SF_ASSERT_IS_EQ(sf_test_failure_description(failure), sf_string("(string) { NULL } expected to equal (\"fnord\")"));
}


SF_TEST_CASE(sf_assert_c_string_equals_fails_for_NULL_expected_value)
{
  sf_list_t failures = NULL;
  
  bool result = sf_assert_c_string_equals("/test/file", 42, "string", "foobar", "NULL", NULL, &failures);
  
  SF_ASSERT_FALSE(result);
  SF_ASSERT_NOT_NULL(failures);
  SF_ASSERT_INT_EQ(sf_count(failures), 1);
  sf_test_failure_t failure = sf_list_head(failures);
  SF_ASSERT_IS_EQ(sf_test_failure_file(failure), sf_string("/test/file"));
  SF_ASSERT_INT_EQ(sf_test_failure_line(failure), 42);
  SF_ASSERT_IS_EQ(sf_test_failure_description(failure), sf_string("(string) { \"foobar\" } expected to equal (NULL)"));
}


SF_TEST_CASE(sf_assert_c_string_not_equals_passes)
{
  sf_list_t failures = NULL;
  
  bool result = sf_assert_c_string_not_equals("/test/file", 42, "string", "foobar", "fnord", "fnord", &failures);
  
  SF_ASSERT_TRUE(result);
  SF_ASSERT_NULL(failures);
}


SF_TEST_CASE(sf_assert_c_string_not_equals_passes_when_actual_is_NULL)
{
  sf_list_t failures = NULL;
  
  bool result = sf_assert_c_string_not_equals("/test/file", 42, "string", NULL, "fnord", "fnord", &failures);
  
  SF_ASSERT_TRUE(result);
  SF_ASSERT_NULL(failures);
}


SF_TEST_CASE(sf_assert_c_string_not_equals_passes_when_expected_is_NULL)
{
  sf_list_t failures = NULL;
  
  bool result = sf_assert_c_string_not_equals("/test/file", 42, "string", "foobar", "NULL", NULL, &failures);
  
  SF_ASSERT_TRUE(result);
  SF_ASSERT_NULL(failures);
}


SF_TEST_CASE(sf_assert_c_string_not_equals_fails)
{
  sf_list_t failures = NULL;
  
  bool result = sf_assert_c_string_not_equals("/test/file", 42, "string", "foobar", "foobar", "foobar", &failures);
  
  SF_ASSERT_FALSE(result);
  SF_ASSERT_NOT_NULL(failures);
  SF_ASSERT_INT_EQ(sf_count(failures), 1);
  sf_test_failure_t failure = sf_list_head(failures);
  SF_ASSERT_IS_EQ(sf_test_failure_file(failure), sf_string("/test/file"));
  SF_ASSERT_INT_EQ(sf_test_failure_line(failure), 42);
  SF_ASSERT_IS_EQ(sf_test_failure_description(failure), sf_string("(string) { \"foobar\" } expected to NOT equal (\"foobar\")"));
}


SF_TEST_CASE(sf_assert_c_string_not_equals_fails_when_both_are_NULL)
{
  sf_list_t failures = NULL;
  
  bool result = sf_assert_c_string_not_equals("/test/file", 42, "string", NULL, "NULL", NULL, &failures);
  
  SF_ASSERT_FALSE(result);
  SF_ASSERT_NOT_NULL(failures);
  SF_ASSERT_INT_EQ(sf_count(failures), 1);
  sf_test_failure_t failure = sf_list_head(failures);
  SF_ASSERT_IS_EQ(sf_test_failure_file(failure), sf_string("/test/file"));
  SF_ASSERT_INT_EQ(sf_test_failure_line(failure), 42);
  SF_ASSERT_IS_EQ(sf_test_failure_description(failure), sf_string("(string) { NULL } expected to NOT equal (NULL)"));
}


SF_TEST_SUITE(sf_assert_c_string_tests,
              sf_assert_c_string_equals_passes,
              sf_assert_c_string_equals_fails,
              sf_assert_c_string_equals_fails_for_NULL_actual_value,
              sf_assert_c_string_equals_fails_for_NULL_expected_value,
              sf_assert_c_string_not_equals_passes,
              sf_assert_c_string_not_equals_passes_when_actual_is_NULL,
              sf_assert_c_string_not_equals_passes_when_expected_is_NULL,
              sf_assert_c_string_not_equals_fails,
              sf_assert_c_string_not_equals_fails_when_both_are_NULL
              );
