#include <stdlib.h>
#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_TEST_CASE(sf_hash_for_1k_items)
{
  int count = 1000;
  sf_any_t *items = sf_calloc(count, sizeof(sf_any_t));
  for (int i = 0; i < count; ++i) {
    items[i] = sf_string_from_format("%i", i);
  }
  sf_array_t keys = sf_array(items, count);
  sf_free(items);

  items = sf_calloc(count, sizeof(sf_any_t));
  for (int i = 0; i < count; ++i) {
    items[i] = sf_int(i);
  }
  sf_array_t values = sf_array(items, count);
  sf_free(items);

  sf_hash_t hash = sf_hash_from_keys_and_values(keys, values);
  
  for (int i = 0; i < count; ++i) {
    sf_string_t key = sf_string_from_format("%i", i);;
    SF_ASSERT_TRUE(sf_hash_contains_key(hash, key));

    sf_int_t value = sf_hash_value_for_key(hash, key);
    sf_int_t expected_value = sf_int(i);
    SF_ASSERT_IS_EQ(value, expected_value);
  }
}


SF_TEST_CASE(sf_hash_for_10k_items)
{
  int count = 10000;
  sf_any_t *items = sf_calloc(count, sizeof(sf_any_t));
  for (int i = 0; i < count; ++i) {
    items[i] = sf_string_from_format("%i", i);
  }
  sf_array_t keys = sf_array(items, count);
  sf_free(items);

  items = sf_calloc(count, sizeof(sf_any_t));
  for (int i = 0; i < count; ++i) {
    items[i] = sf_int(i);
  }
  sf_array_t values = sf_array(items, count);
  sf_free(items);

  sf_hash_t hash = sf_hash_from_keys_and_values(keys, values);
  
  for (int i = 0; i < count; ++i) {
    sf_string_t key = sf_string_from_format("%i", i);;
    SF_ASSERT_TRUE(sf_hash_contains_key(hash, key));

    sf_int_t value = sf_hash_value_for_key(hash, key);
    sf_int_t expected_value = sf_int(i);
    SF_ASSERT_IS_EQ(value, expected_value);
  }
}


SF_TEST_CASE(sf_hash_for_100k_items)
{
  int count = 100000;
  sf_any_t *items = sf_calloc(count, sizeof(sf_any_t));
  for (int i = 0; i < count; ++i) {
    items[i] = sf_string_from_format("%i", i);
  }
  sf_array_t keys = sf_array(items, count);
  sf_free(items);

  items = sf_calloc(count, sizeof(sf_any_t));
  for (int i = 0; i < count; ++i) {
    items[i] = sf_int(i);
  }
  sf_array_t values = sf_array(items, count);
  sf_free(items);

  sf_hash_t hash = sf_hash_from_keys_and_values(keys, values);
  
  for (int i = 0; i < count; ++i) {
    sf_string_t key = sf_string_from_format("%i", i);;
    SF_ASSERT_TRUE(sf_hash_contains_key(hash, key));

    sf_int_t value = sf_hash_value_for_key(hash, key);
    sf_int_t expected_value = sf_int(i);
    SF_ASSERT_IS_EQ(value, expected_value);
  }
}


SF_TEST_CASE(sf_hash_for_1M_items)
{
  int count = 1000000;
  sf_any_t *items = sf_calloc(count, sizeof(sf_any_t));
  for (int i = 0; i < count; ++i) {
    items[i] = sf_string_from_format("%i", i);
  }
  sf_array_t keys = sf_array(items, count);
  sf_free(items);

  items = sf_calloc(count, sizeof(sf_any_t));
  for (int i = 0; i < count; ++i) {
    items[i] = sf_int(i);
  }
  sf_array_t values = sf_array(items, count);
  sf_free(items);

  sf_hash_t hash = sf_hash_from_keys_and_values(keys, values);
  
  for (int i = 0; i < count; ++i) {
    sf_string_t key = sf_string_from_format("%i", i);;
    SF_ASSERT_TRUE(sf_hash_contains_key(hash, key));

    sf_int_t value = sf_hash_value_for_key(hash, key);
    sf_int_t expected_value = sf_int(i);
    SF_ASSERT_IS_EQ(value, expected_value);
  }
}


SF_TEST_SUITE(sf_hash_stress_tests,
              sf_hash_for_1k_items,
              sf_hash_for_10k_items,
              sf_hash_for_100k_items,
              sf_hash_for_1M_items
              );
