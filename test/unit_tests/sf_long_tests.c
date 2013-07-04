#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_TEST_CASE(NULL_sf_long)
{
  sf_long_t long_int = NULL;
  SF_ASSERT_LONG_EQ(sf_long_value(long_int), 0);
}


SF_TEST_CASE(sf_long_initializer)
{
  sf_long_t long_int1 = sf_long(42);
  SF_ASSERT_LONG_EQ(sf_long_value(long_int1), 42);
  
  sf_long_t long_int2 = sf_long(-3);
  SF_ASSERT_LONG_EQ(sf_long_value(long_int2), -3);
}


SF_TEST_CASE(sf_longs_as_keys)
{
  sf_long_t long_int1 = sf_long(42);
  sf_long_t long_int2 = sf_long(41);
  sf_long_t long_int3 = sf_long(42);
  
  SF_ASSERT_IS_NOT_EQ(long_int1, long_int2);
  SF_ASSERT_INT_NOT_EQ(sf_hash_code(long_int1), sf_hash_code(long_int2));
  
  SF_ASSERT_IS_EQ(long_int1, long_int3);
  SF_ASSERT_INT_EQ(sf_hash_code(long_int1), sf_hash_code(long_int3));
  
  SF_ASSERT_TRUE(sf_is_key_type(long_int1));
}


SF_TEST_CASE(string_from_sf_long)
{
  sf_long_t long_int1 = sf_long(42);
  sf_long_t long_int2 = sf_long(-3);
  
  SF_ASSERT_IS_EQ(sf_string_from(long_int1), sf_string("42L"));
  SF_ASSERT_IS_EQ(sf_string_from(long_int2), sf_string("-3L"));
}


SF_TEST_SUITE(sf_long_tests,
              NULL_sf_long,
              sf_long_initializer,
              sf_longs_as_keys,
              string_from_sf_long
              );
