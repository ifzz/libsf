#include <stdlib.h>
#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_TEST_CASE(sf_list_for_1k_items)
{
  int count = 1000;
  sf_list_t list = NULL;
  for (int i = 0; i < count; ++i) {
    sf_int_t integer = sf_int(i);
    list = sf_list(integer, list);
  }
  for (int i = count - 1; i >= 0; --i) {
    sf_int_t integer = sf_list_head(list);
    SF_ASSERT_INT_EQ(sf_int_value(integer), i);
    list = sf_list_tail(list);
  }
}


SF_TEST_CASE(sf_list_for_10k_items)
{
  int count = 10000;
  sf_list_t list = NULL;
  for (int i = 0; i < count; ++i) {
    sf_int_t integer = sf_int(i);
    list = sf_list(integer, list);
  }
  for (int i = count - 1; i >= 0; --i) {
    sf_int_t integer = sf_list_head(list);
    SF_ASSERT_INT_EQ(sf_int_value(integer), i);
    list = sf_list_tail(list);
  }
}


SF_TEST_CASE(sf_list_for_100k_items)
{
  int count = 100000;
  sf_list_t list = NULL;
  for (int i = 0; i < count; ++i) {
    sf_int_t integer = sf_int(i);
    list = sf_list(integer, list);
  }
  for (int i = count - 1; i >= 0; --i) {
    sf_int_t integer = sf_list_head(list);
    SF_ASSERT_INT_EQ(sf_int_value(integer), i);
    list = sf_list_tail(list);
  }
}


SF_TEST_CASE(sf_list_for_1M_items)
{
  int count = 1000000;
  sf_list_t list = NULL;
  for (int i = 0; i < count; ++i) {
    sf_int_t integer = sf_int(i);
    list = sf_list(integer, list);
  }
  for (int i = count - 1; i >= 0; --i) {
    sf_int_t integer = sf_list_head(list);
    SF_ASSERT_INT_EQ(sf_int_value(integer), i);
    list = sf_list_tail(list);
  }
}


SF_TEST_CASE(sf_list_for_10M_items)
{
  int count = 10000000;
  sf_list_t list = NULL;
  for (int i = 0; i < count; ++i) {
    sf_int_t integer = sf_int(i);
    list = sf_list(integer, list);
  }
  for (int i = count - 1; i >= 0; --i) {
    sf_int_t integer = sf_list_head(list);
    SF_ASSERT_INT_EQ(sf_int_value(integer), i);
    list = sf_list_tail(list);
  }
}


SF_TEST_SUITE(sf_list_stress_tests,
              sf_list_for_1k_items,
              sf_list_for_10k_items,
              sf_list_for_100k_items,
              sf_list_for_1M_items,
              sf_list_for_10M_items
              );
