#include <sf/sf.h>
#include <sf_test/sf_test.h>


extern sf_test_suite_t sf_assert_bool_tests;
extern sf_test_suite_t sf_assert_c_string_tests;


SF_TEST_CASE(sf_assert_failure_value_not_shown_when_same_as_expression)
{
  sf_list_t failures = NULL;
  
  bool result = sf_assert_int_equals("/test/file", 42, "71", 71, "73", 73, &failures);
  
  SF_ASSERT_FALSE(result);
  SF_ASSERT_NOT_NULL(failures);
  SF_ASSERT_INT_EQ(sf_count(failures), 1);
  sf_test_failure_t failure = sf_list_head(failures);
  SF_ASSERT_IS_EQ(sf_test_failure_file(failure), sf_string("/test/file"));
  SF_ASSERT_INT_EQ(sf_test_failure_line(failure), 42);
  SF_ASSERT_IS_EQ(sf_test_failure_description(failure), sf_string("expected (71) to equal (73)"));
}


SF_TEST_CASE(sf_assert_failure_actual_value_shown_when_different_from_expression)
{
  sf_list_t failures = NULL;
  
  bool result = sf_assert_int_equals("/test/file", 42, "x", 71, "73", 73, &failures);
  
  SF_ASSERT_FALSE(result);
  SF_ASSERT_NOT_NULL(failures);
  SF_ASSERT_INT_EQ(sf_count(failures), 1);
  sf_test_failure_t failure = sf_list_head(failures);
  SF_ASSERT_IS_EQ(sf_test_failure_file(failure), sf_string("/test/file"));
  SF_ASSERT_INT_EQ(sf_test_failure_line(failure), 42);
  SF_ASSERT_IS_EQ(sf_test_failure_description(failure), sf_string("expected (x) { 71 } to equal (73)"));
}


SF_TEST_CASE(sf_assert_failure_expected_value_shown_when_different_from_expression)
{
  sf_list_t failures = NULL;
  
  bool result = sf_assert_int_equals("/test/file", 42, "71", 71, "count", 73, &failures);
  
  SF_ASSERT_FALSE(result);
  SF_ASSERT_NOT_NULL(failures);
  SF_ASSERT_INT_EQ(sf_count(failures), 1);
  sf_test_failure_t failure = sf_list_head(failures);
  SF_ASSERT_IS_EQ(sf_test_failure_file(failure), sf_string("/test/file"));
  SF_ASSERT_INT_EQ(sf_test_failure_line(failure), 42);
  SF_ASSERT_IS_EQ(sf_test_failure_description(failure), sf_string("expected (71) to equal (count) { 73 }"));
}


SF_TEST_SUITE(sf_assert_tests,
              sf_assert_failure_value_not_shown_when_same_as_expression,
              sf_assert_failure_actual_value_shown_when_different_from_expression,
              sf_assert_failure_expected_value_shown_when_different_from_expression
              );
