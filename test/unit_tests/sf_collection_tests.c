#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_EXTERN_TEST_SUITE(sf_collection_collect_tests);
SF_EXTERN_TEST_SUITE(sf_collection_each_tests);
SF_EXTERN_TEST_SUITE(sf_collection_filter_tests);


SF_TEST_SUITE(sf_collection_tests,
              sf_collection_collect_tests,
              sf_collection_each_tests,
              sf_collection_filter_tests
              );
