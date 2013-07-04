#ifndef SF_TEST_SF_STDIO_TEST_MONITOR_H_INCLUDED
#define SF_TEST_SF_STDIO_TEST_MONITOR_H_INCLUDED


#include <sf_test/sf_test_defs.h>


enum sf_stdio_test_monitor_test_case_output
{
  sf_stdio_test_monitor_test_case_output_default = 0,
  sf_stdio_test_monitor_test_case_output_brief = 0,
  sf_stdio_test_monitor_test_case_output_none,
  sf_stdio_test_monitor_test_case_output_full,
};


struct sf_stdio_test_monitor_options
{
  enum sf_stdio_test_monitor_test_case_output test_case_output;
};


struct sf_test_monitor *
sf_stdio_test_monitor(void);

int
sf_stdio_test_monitor_failed_test_case_count(struct sf_test_monitor *test_monitor);

struct sf_test_monitor *
sf_stdio_test_monitor_from_options(struct sf_stdio_test_monitor_options const *options);


#endif
