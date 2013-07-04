#ifndef SF_TEST_SF_TEST_SEQUENCE_H_INCLUDED
#define SF_TEST_SF_TEST_SEQUENCE_H_INCLUDED


#include <sf/sf_array.h>
#include <sf_test/sf_test_defs.h>


extern sf_type_t sf_test_sequence_type;


#define sf_test_sequence(...) \
        sf_test_sequence_from_array(sf_test_items(__VA_ARGS__))

sf_test_sequence_t
sf_test_sequence_from_array(sf_array_t array);

void
sf_test_sequence_run_test_cases(sf_test_sequence_t test_sequence, struct sf_test_monitor *test_monitor);

sf_test_sequence_t
sf_test_sequence_shuffled(sf_test_sequence_t test_sequence, sf_random_t random_in, sf_random_t *random_out);


#endif
