#include "sf_test.h"


void
_sf_test_case_init(void);

void
_sf_test_failure_init(void);

void
_sf_test_sequence_init(void);

void
_sf_test_suite_init(void);

void
_sf_test_time_init(void);


void
sf_test_init(void)
{
  sf_init();
  _sf_test_case_init();
  _sf_test_failure_init();
  _sf_test_sequence_init();
  _sf_test_suite_init();
  _sf_test_time_init();
}


void
sf_test_fin(void)
{
  sf_fin();
}
