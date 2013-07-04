#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_EXTERN_TEST_SUITE(sf_hash_from_keys_and_values_tests);


SF_TEST_CASE(NULL_sf_hash)
{
  sf_hash_t hash = NULL;
  SF_ASSERT_INT_EQ(sf_count(hash), 0);
  SF_ASSERT_FALSE(sf_hash_contains_key(hash, sf_string("one")));
  SF_ASSERT_NULL(sf_hash_value_for_key(hash, sf_string("one")));
}


SF_TEST_SUITE(sf_hash_tests,
              NULL_sf_hash,
              
              sf_hash_from_keys_and_values_tests
              );
