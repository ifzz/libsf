#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_EXTERN_TEST_SUITE(sf_array_stress_tests);
SF_EXTERN_TEST_SUITE(sf_hash_stress_tests);
SF_EXTERN_TEST_SUITE(sf_list_stress_tests);


int main(int argc, char const **argv)
{
  sf_test_init();
  
  struct sf_stdio_test_monitor_options options = {
    .test_case_output = sf_stdio_test_monitor_test_case_output_full,
  };
  struct sf_test_monitor *test_monitor = sf_stdio_test_monitor_from_options(&options);
  
  sf_test_sequence_t test_sequence = sf_test_sequence(sf_array_stress_tests,
                                                      sf_hash_stress_tests,
                                                      sf_list_stress_tests
                                                      );
  sf_test_sequence_run_test_cases(test_sequence, test_monitor);
  int exit_code = sf_stdio_test_monitor_failed_test_case_count(test_monitor);
  
  sf_test_fin();
  return exit_code;
}
