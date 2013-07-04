#include <stdio.h>
#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_EXTERN_TEST_SUITE(sf_array_tests);
SF_EXTERN_TEST_SUITE(sf_assert_tests);
SF_EXTERN_TEST_SUITE(sf_collection_tests);
SF_EXTERN_TEST_SUITE(sf_ensemble_tests);
SF_EXTERN_TEST_SUITE(sf_hash_tests);
SF_EXTERN_TEST_SUITE(sf_int_tests);
SF_EXTERN_TEST_SUITE(sf_list_tests);
SF_EXTERN_TEST_SUITE(sf_long_tests);
SF_EXTERN_TEST_SUITE(sf_pair_tests);
SF_EXTERN_TEST_SUITE(sf_random_tests);
SF_EXTERN_TEST_SUITE(sf_string_tests);


int main(int argc, char const **argv)
{
  sf_test_init();
  
  struct sf_stdio_test_monitor_options options = {
    .test_case_output = sf_stdio_test_monitor_test_case_output_brief,
  };
  struct sf_test_monitor *test_monitor = sf_stdio_test_monitor_from_options(&options);
  
  sf_test_sequence_t test_sequence = sf_test_sequence(sf_array_tests,
                                                      sf_assert_tests,
                                                      sf_collection_tests,
                                                      sf_ensemble_tests,
                                                      sf_hash_tests,
                                                      sf_int_tests,
                                                      sf_list_tests,
                                                      sf_long_tests,
                                                      sf_pair_tests,
                                                      sf_random_tests,
                                                      sf_string_tests
                                                      );
  sf_random_t random = sf_random_from_state((unsigned short[3]) { 37, 41, 43 });
  sf_test_sequence_t shuffled_test_sequence = sf_test_sequence_shuffled(test_sequence, random, NULL);
  
  sf_test_sequence_run_test_cases(shuffled_test_sequence, test_monitor);
  int exit_code = sf_stdio_test_monitor_failed_test_case_count(test_monitor);
  
  sf_test_fin();
  return exit_code;
}
