#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_TEST_CASE(NULL_sf_random)
{
  sf_random_t random = NULL;
  SF_ASSERT_INT_EQ(sf_random_value(random), 0);
}


SF_TEST_SUITE(sf_random_tests,
              NULL_sf_random
              );
