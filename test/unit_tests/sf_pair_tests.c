#include <sf/sf.h>
#include <sf_test/sf_test.h>


SF_TEST_CASE(NULL_sf_pair)
{
  sf_pair_t pair = NULL;
  SF_ASSERT_NULL(sf_pair_left(pair));
  SF_ASSERT_NULL(sf_pair_right(pair));
  SF_ASSERT_INT_EQ(sf_count(pair), 0);
}


SF_TEST_CASE(sf_pair_with_both_sides_NULL)
{
  sf_string_t left = NULL;
  sf_int_t right = NULL;
  sf_pair_t pair = sf_pair(left, right);
  SF_ASSERT_NULL(sf_pair_left(pair));
  SF_ASSERT_NULL(sf_pair_right(pair));
  SF_ASSERT_INT_EQ(sf_count(pair), 2);
}


SF_TEST_CASE(sf_pair_with_NULL_on_left)
{
  sf_string_t left = NULL;
  sf_int_t right = sf_int(42);
  sf_pair_t pair = sf_pair(left, right);
  SF_ASSERT_NULL(sf_pair_left(pair));
  SF_ASSERT_IS_EQ(sf_pair_right(pair), right);
  SF_ASSERT_INT_EQ(sf_count(pair), 2);
}


SF_TEST_CASE(sf_pair_with_NULL_on_right)
{
  sf_string_t left = sf_string("left");
  sf_int_t right = NULL;
  sf_pair_t pair = sf_pair(left, right);
  SF_ASSERT_IS_EQ(sf_pair_left(pair), left);
  SF_ASSERT_NULL(sf_pair_right(pair));
  SF_ASSERT_INT_EQ(sf_count(pair), 2);
}


SF_TEST_CASE(sf_pair_with_two_objects)
{
  sf_string_t left = sf_string("left");
  sf_int_t right = sf_int(42);
  sf_pair_t pair = sf_pair(left, right);
  SF_ASSERT_IS_EQ(sf_pair_left(pair), left);
  SF_ASSERT_IS_EQ(sf_pair_right(pair), right);
  SF_ASSERT_INT_EQ(sf_count(pair), 2);
}


SF_TEST_CASE(sf_pair_reversed_with_NULL_returns_NULL)
{
  sf_pair_t reversed = sf_pair_reversed(NULL);
  SF_ASSERT_NULL(reversed);
}


SF_TEST_CASE(sf_pair_reversed_swaps_items)
{
  sf_string_t left = sf_string("left");
  sf_int_t right = sf_int(42);
  sf_pair_t pair = sf_pair(left, right);
  sf_pair_t reversed = sf_pair_reversed(pair);
  SF_ASSERT_IS_EQ(sf_pair_left(reversed), right);
  SF_ASSERT_IS_EQ(sf_pair_right(reversed), left);
  SF_ASSERT_INT_EQ(sf_count(reversed), 2);
}


SF_TEST_CASE(sf_string_from_pair)
{
  sf_string_t string = sf_string_from(sf_pair(sf_string("one"), sf_int(42)));
  SF_ASSERT_IS_EQ(string, sf_string("<one,42>"));
}


SF_TEST_SUITE(sf_pair_tests,
              NULL_sf_pair,
              sf_pair_with_both_sides_NULL,
              sf_pair_with_NULL_on_left,
              sf_pair_with_NULL_on_right,
              sf_pair_with_two_objects,
              sf_pair_reversed_with_NULL_returns_NULL,
              sf_pair_reversed_swaps_items,
              sf_string_from_pair
              );
