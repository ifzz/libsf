#ifndef SF_TEST_SF_TEST_SUITE_H_INCLUDED
#define SF_TEST_SF_TEST_SUITE_H_INCLUDED


#include <sf_test/sf_test_defs.h>


#define SF_EXTERN_TEST_SUITE(IDENTIFIER) \
    extern struct sf_test_item const *IDENTIFIER

#define SF_TEST_SUITE(IDENTIFIER, ...) \
    static sf_array_t _sf_test_suite_##IDENTIFIER(void) \
    { \
      return sf_test_items(__VA_ARGS__); \
    } \
    struct sf_test_item const *IDENTIFIER = &( \
      (struct sf_test_item const) { \
        .type = sf_test_item_type_test_suite, \
        .identifier = #IDENTIFIER, \
        .generate_items = _sf_test_suite_##IDENTIFIER, \
      } \
    )


extern sf_type_t sf_test_suite_type;


sf_test_suite_t
sf_test_suite(struct sf_test_item const *test_item);

sf_string_t
sf_test_suite_identifier(sf_test_suite_t test_suite);

sf_array_t
sf_test_suite_items(sf_test_suite_t test_suite);


#endif
