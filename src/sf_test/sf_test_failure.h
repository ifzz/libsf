#ifndef SF_TEST_SF_TEST_FAILURE_H_INCLUDED
#define SF_TEST_SF_TEST_FAILURE_H_INCLUDED


#include <sf_test/sf_test_defs.h>


extern sf_type_t sf_test_failure_type;


sf_test_failure_t
sf_test_failure(char const *file, int line, sf_string_t description);

sf_string_t
sf_test_failure_description(sf_test_failure_t test_failure);

sf_string_t
sf_test_failure_file(sf_test_failure_t test_failure);

int
sf_test_failure_line(sf_test_failure_t test_failure);


#endif
