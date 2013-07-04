#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_TEST_CASE(NULL_sf_int)
{
  sf_int_t integer = NULL;
  SF_ASSERT_LONG_EQ(sf_int_value(integer), 0);
}


SF_TEST_CASE(sf_int_initializer)
{
  sf_int_t integer1 = sf_int(42);
  SF_ASSERT_INT_EQ(sf_int_value(integer1), 42);
  
  sf_int_t integer2 = sf_int(-3);
  SF_ASSERT_INT_EQ(sf_int_value(integer2), -3);
}


SF_TEST_CASE(sf_ints_as_keys)
{
  sf_int_t integer1 = sf_int(42);
  sf_int_t integer2 = sf_int(41);
  sf_int_t integer3 = sf_int(42);
  
  SF_ASSERT_IS_NOT_EQ(integer1, integer2);
  SF_ASSERT_INT_NOT_EQ(sf_hash_code(integer1), sf_hash_code(integer2));
  
  SF_ASSERT_IS_EQ(integer1, integer3);
  SF_ASSERT_INT_EQ(sf_hash_code(integer1), sf_hash_code(integer3));
  
  SF_ASSERT_TRUE(sf_is_key_type(integer1));
}


SF_TEST_CASE(string_from_sf_int)
{
  sf_int_t integer1 = sf_int(42);
  sf_int_t integer2 = sf_int(-3);
  
  SF_ASSERT_IS_EQ(sf_string_from(integer1), sf_string("42"));
  SF_ASSERT_IS_EQ(sf_string_from(integer2), sf_string("-3"));
}


SF_TEST_SUITE(sf_int_tests,
              NULL_sf_int,
              sf_int_initializer,
              sf_ints_as_keys,
              string_from_sf_int
              );
