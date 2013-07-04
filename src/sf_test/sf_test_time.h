#ifndef SF_TEST_SF_TEST_TIME_H_INCLUDED
#define SF_TEST_SF_TEST_TIME_H_INCLUDED


#include <sf_test/sf_test_defs.h>
#include <time.h>


extern sf_type_t sf_test_time_type;


clock_t
sf_test_time_clocks(sf_test_time_t test_time);

double
sf_test_time_elapsed_seconds(sf_test_time_t test_time1, sf_test_time_t test_time2);

sf_test_time_t
sf_test_time_now(void);

time_t
sf_test_time_value(sf_test_time_t test_time);


#endif
