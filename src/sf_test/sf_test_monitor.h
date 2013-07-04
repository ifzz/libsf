#ifndef SF_TEST_SF_TEST_MONITOR_H_INCLUDED
#define SF_TEST_SF_TEST_MONITOR_H_INCLUDED


#include <sf_test/sf_test_defs.h>


struct sf_test_monitor
{
  void *context;
  void (*test_sequence_will_start)(sf_test_time_t test_time, sf_test_sequence_t test_sequence, void *context);
  void (*test_case_will_start)(sf_test_time_t test_time, sf_test_case_t test_case, sf_list_t test_suites, void *context);
  void (*test_case_did_stop)(sf_test_time_t test_time, sf_test_case_t test_case, sf_list_t test_suites, sf_list_t test_failures, void *context);
  void (*test_sequence_did_stop)(sf_test_time_t test_time, sf_test_sequence_t test_sequence, void *context);
};


#endif
