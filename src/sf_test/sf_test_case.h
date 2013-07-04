#ifndef SF_TEST_SF_TEST_CASE_H_INCLUDED
#define SF_TEST_SF_TEST_CASE_H_INCLUDED


#include <sf_test/sf_test_defs.h>


#define SF_TEST_CASE(IDENTIFIER) \
    static void _sf_test_case_##IDENTIFIER(sf_list_t *_sf_test_failures); \
    static struct sf_test_item const *IDENTIFIER = &( \
      (struct sf_test_item const) { \
        .type = sf_test_item_type_test_case, \
        .identifier = #IDENTIFIER, \
        .test_function = _sf_test_case_##IDENTIFIER, \
      } \
    ); \
    static void _sf_test_case_##IDENTIFIER(sf_list_t *_sf_test_failures)


extern sf_type_t sf_test_case_type;


sf_test_case_t
sf_test_case(struct sf_test_item const *test_item);

sf_string_t
sf_test_case_identifier(sf_test_case_t test_case);

sf_list_t
sf_test_case_run(sf_test_case_t test_case);


#endif
