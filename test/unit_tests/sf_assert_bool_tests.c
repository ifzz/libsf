#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_TEST_CASE(sf_assert_bool_pass_for_expected_true)
{
  sf_list_t failures = NULL;
  
  bool result = sf_assert_bool("/test/file", 42, "(true)", true, true, &failures);
  
  SF_ASSERT_TRUE(result);
  SF_ASSERT_NULL(failures);
}


SF_TEST_CASE(sf_assert_bool_fail_for_expected_true)
{
  sf_list_t failures = NULL;
  
  bool result = sf_assert_bool("/test/file", 42, "(true)", true, false, &failures);
  
  SF_ASSERT_FALSE(result);
  SF_ASSERT_NOT_NULL(failures);
  SF_ASSERT_INT_EQ(sf_count(failures), 1);
  sf_test_failure_t failure = sf_list_head(failures);
  SF_ASSERT_IS_EQ(sf_test_failure_file(failure), sf_string("/test/file"));
  SF_ASSERT_INT_EQ(sf_test_failure_line(failure), 42);
  SF_ASSERT_IS_EQ(sf_test_failure_description(failure), sf_string("((true)) expected to be false"));
}


SF_TEST_CASE(sf_assert_bool_pass_for_expected_false)
{
  sf_list_t failures = NULL;
  
  bool result = sf_assert_bool("/test/file", 42, "(false)", false, false, &failures);
  
  SF_ASSERT_TRUE(result);
  SF_ASSERT_NULL(failures);
}


SF_TEST_CASE(sf_assert_bool_fail_for_expected_false)
{
  sf_list_t failures = NULL;
  
  bool result = sf_assert_bool("/test/file", 42, "(false)", false, true, &failures);
  
  SF_ASSERT_FALSE(result);
  SF_ASSERT_NOT_NULL(failures);
  SF_ASSERT_INT_EQ(sf_count(failures), 1);
  sf_test_failure_t failure = sf_list_head(failures);
  SF_ASSERT_IS_EQ(sf_test_failure_file(failure), sf_string("/test/file"));
  SF_ASSERT_INT_EQ(sf_test_failure_line(failure), 42);
  SF_ASSERT_IS_EQ(sf_test_failure_description(failure), sf_string("((false)) expected to be true"));
}


SF_TEST_SUITE(sf_assert_bool_tests,
              sf_assert_bool_pass_for_expected_true,
              sf_assert_bool_fail_for_expected_true,
              sf_assert_bool_pass_for_expected_false,
              sf_assert_bool_fail_for_expected_false
              );
