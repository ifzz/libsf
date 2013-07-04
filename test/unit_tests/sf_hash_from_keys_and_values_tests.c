#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_TEST_CASE(sf_hash_from_keys_and_values_for_NULL_keys_and_values)
{
  sf_hash_t hash = sf_hash_from_keys_and_values(NULL, NULL);
  SF_ASSERT_INT_EQ(sf_count(hash), 0);
  SF_ASSERT_FALSE(sf_hash_contains_key(hash, sf_string("foobar")));
  SF_ASSERT_NULL(sf_hash_value_for_key(hash, sf_string("foobar")));
}


SF_TEST_CASE(sf_hash_from_keys_and_values_for_one_key_and_value)
{
  sf_string_t key1 = sf_string("one");
  sf_int_t value1 = sf_int(1);
  
  sf_hash_t hash = sf_hash_from_keys_and_values(sf_array_from_items(key1),
      sf_array_from_items(value1));
  
  SF_ASSERT_INT_EQ(sf_count(hash), 1);
  SF_ASSERT_TRUE(sf_hash_contains_key(hash, key1));
  SF_ASSERT_IS_EQ(sf_hash_value_for_key(hash, key1), value1);
  
  SF_ASSERT_FALSE(sf_hash_contains_key(hash, sf_string("foobar")));
  SF_ASSERT_NULL(sf_hash_value_for_key(hash, sf_string("foobar")));
}


SF_TEST_CASE(sf_hash_from_keys_and_values_for_two_keys_with_different_hash_codes)
{
  sf_string_t key1 = sf_string("one");
  sf_int_t value1 = sf_int(1);
  
  sf_string_t key2 = sf_string("two");
  sf_int_t value2 = sf_int(2);
  SF_ASSERT_INT_NOT_EQ(sf_hash_code(key1), sf_hash_code(key2));
  
  sf_hash_t hash = sf_hash_from_keys_and_values(sf_array_from_items(key1, key2),
      sf_array_from_items(value1, value2));
  
  SF_ASSERT_INT_EQ(sf_count(hash), 2);
  SF_ASSERT_TRUE(sf_hash_contains_key(hash, key1));
  SF_ASSERT_IS_EQ(sf_hash_value_for_key(hash, key1), value1);
  
  SF_ASSERT_TRUE(sf_hash_contains_key(hash, key2));
  SF_ASSERT_IS_EQ(sf_hash_value_for_key(hash, key2), value2);
  
  SF_ASSERT_FALSE(sf_hash_contains_key(hash, sf_string("foobar")));
  SF_ASSERT_NULL(sf_hash_value_for_key(hash, sf_string("foobar")));
}


SF_TEST_CASE(sf_hash_from_keys_and_values_for_two_keys_with_same_hash_code)
{
  sf_string_t key1 = sf_string("A");
  sf_int_t value1 = sf_int(1);

  sf_int_t key2 = sf_int(2692);
  sf_int_t value2 = sf_int(2);
  SF_ASSERT_INT_EQ(sf_hash_code(key1), sf_hash_code(key2));
  
  sf_hash_t hash = sf_hash_from_keys_and_values(sf_array_from_items(key1, key2),
      sf_array_from_items(value1, value2));
  
  SF_ASSERT_INT_EQ(sf_count(hash), 2);
  SF_ASSERT_TRUE(sf_hash_contains_key(hash, key1));
  SF_ASSERT_IS_EQ(sf_hash_value_for_key(hash, key1), value1);

  SF_ASSERT_TRUE(sf_hash_contains_key(hash, key2));
  SF_ASSERT_IS_EQ(sf_hash_value_for_key(hash, key2), value2);
  
  SF_ASSERT_FALSE(sf_hash_contains_key(hash, sf_string("foobar")));
  SF_ASSERT_NULL(sf_hash_value_for_key(hash, sf_string("foobar")));
}


SF_TEST_CASE(sf_hash_from_keys_and_values_for_three)
{
  sf_string_t key1 = sf_string("one");
  sf_int_t value1 = sf_int(1);
  
  sf_string_t key2 = sf_string("two");
  sf_int_t value2 = sf_int(2);
  
  sf_string_t key3 = sf_string("three");
  sf_int_t value3 = sf_int(3);
  
  sf_hash_t hash = sf_hash_from_keys_and_values(sf_array_from_items(key1, key2, key3),
      sf_array_from_items(value1, value2, value3));
  
  SF_ASSERT_INT_EQ(sf_count(hash), 3);
  SF_ASSERT_TRUE(sf_hash_contains_key(hash, key1));
  SF_ASSERT_IS_EQ(sf_hash_value_for_key(hash, key1), value1);
  
  SF_ASSERT_TRUE(sf_hash_contains_key(hash, key2));
  SF_ASSERT_IS_EQ(sf_hash_value_for_key(hash, key2), value2);
  
  SF_ASSERT_TRUE(sf_hash_contains_key(hash, key3));
  SF_ASSERT_IS_EQ(sf_hash_value_for_key(hash, key3), value3);
  
  SF_ASSERT_FALSE(sf_hash_contains_key(hash, sf_string("foobar")));
  SF_ASSERT_NULL(sf_hash_value_for_key(hash, sf_string("foobar")));
}


SF_TEST_CASE(sf_hash_from_keys_and_values_for_too_many_keys)
{
  sf_string_t key1 = sf_string("one");
  sf_int_t value1 = sf_int(1);
  
  sf_string_t key2 = sf_string("two");
  sf_int_t value2 = sf_int(2);
  
  sf_string_t key3 = sf_string("three");
  
  sf_hash_t hash = sf_hash_from_keys_and_values(sf_array_from_items(key1, key2, key3),
      sf_array_from_items(value1, value2));
  
  SF_ASSERT_INT_EQ(sf_count(hash), 2);
  SF_ASSERT_TRUE(sf_hash_contains_key(hash, key1));
  SF_ASSERT_IS_EQ(sf_hash_value_for_key(hash, key1), value1);
  
  SF_ASSERT_TRUE(sf_hash_contains_key(hash, key2));
  SF_ASSERT_IS_EQ(sf_hash_value_for_key(hash, key2), value2);
  
  SF_ASSERT_FALSE(sf_hash_contains_key(hash, key3));
  SF_ASSERT_NULL(sf_hash_value_for_key(hash, key3));
  
  SF_ASSERT_FALSE(sf_hash_contains_key(hash, sf_string("foobar")));
  SF_ASSERT_NULL(sf_hash_value_for_key(hash, sf_string("foobar")));
}


SF_TEST_CASE(sf_hash_from_keys_and_values_for_too_many_values)
{
  sf_string_t key1 = sf_string("one");
  sf_int_t value1 = sf_int(1);
  
  sf_string_t key2 = sf_string("two");
  sf_int_t value2 = sf_int(2);

  sf_int_t value3 = sf_int(3);
  
  sf_hash_t hash = sf_hash_from_keys_and_values(sf_array_from_items(key1, key2),
      sf_array_from_items(value1, value2, value3));
  
  SF_ASSERT_INT_EQ(sf_count(hash), 2);
  SF_ASSERT_TRUE(sf_hash_contains_key(hash, key1));
  SF_ASSERT_IS_EQ(sf_hash_value_for_key(hash, key1), value1);
  
  SF_ASSERT_TRUE(sf_hash_contains_key(hash, key2));
  SF_ASSERT_IS_EQ(sf_hash_value_for_key(hash, key2), value2);
  
  SF_ASSERT_FALSE(sf_hash_contains_key(hash, sf_string("foobar")));
  SF_ASSERT_NULL(sf_hash_value_for_key(hash, sf_string("foobar")));
}


SF_TEST_CASE(sf_hash_from_keys_and_values_for_many_pairs)
{
  int count = 1000;
  sf_list_t keys = NULL;
  sf_list_t values = NULL;
  for (int i = 0; i < count; ++i) {
    keys = sf_list(sf_int(i), keys);
    values = sf_list(sf_int(i * i), values);
  }
  
  sf_hash_t hash = sf_hash_from_keys_and_values(keys, values);
  
  SF_ASSERT_INT_EQ(sf_count(hash), count);
  for (int i = 0; i < count; ++i) {
    sf_int_t key = sf_int(i);
    sf_int_t value = sf_int(i * i);
    SF_ASSERT_TRUE(sf_hash_contains_key(hash, key));
    SF_ASSERT_IS_EQ(sf_hash_value_for_key(hash, key), value);
  }
}


SF_TEST_SUITE(sf_hash_from_keys_and_values_tests,
              sf_hash_from_keys_and_values_for_NULL_keys_and_values,
              sf_hash_from_keys_and_values_for_one_key_and_value,
              sf_hash_from_keys_and_values_for_two_keys_with_different_hash_codes,
              sf_hash_from_keys_and_values_for_two_keys_with_same_hash_code,
              sf_hash_from_keys_and_values_for_three,
              sf_hash_from_keys_and_values_for_too_many_keys,
              sf_hash_from_keys_and_values_for_too_many_values,
              sf_hash_from_keys_and_values_for_many_pairs
              );
