#include <sf/sf.h>
#include <sf_test/sf_test.h>


static bool
is_int_type(sf_any_t, void *context);

static bool
is_string_type(sf_any_t, void *context);


SF_TEST_CASE(sf_filter_empty_array)
{
  sf_array_t collection = NULL;
  
  sf_list_t ints = sf_filter(collection, is_int_type, NULL);
  
  SF_ASSERT_INT_EQ(sf_count(ints), 0);
}


SF_TEST_CASE(sf_filter_array_with_one_item)
{
  sf_array_t collection = sf_array_from_items(sf_string("one"));
  
  sf_list_t ints = sf_filter(collection, is_int_type, NULL);
  SF_ASSERT_INT_EQ(sf_count(ints), 0);
  
  sf_list_t strings = sf_filter(collection, is_string_type, NULL);
  SF_ASSERT_INT_EQ(sf_count(strings), 1);
  SF_ASSERT_IS_EQ(sf_list_head(strings), sf_string("one"));
}


SF_TEST_CASE(sf_filter_array_with_two_items)
{
  sf_array_t collection = sf_array_from_items(sf_string("one"), sf_int(2));
  
  sf_list_t ints = sf_filter(collection, is_int_type, NULL);
  SF_ASSERT_INT_EQ(sf_count(ints), 1);
  SF_ASSERT_IS_EQ(sf_list_head(ints), sf_int(2));
  
  sf_list_t strings = sf_filter(collection, is_string_type, NULL);
  SF_ASSERT_INT_EQ(sf_count(strings), 1);
  SF_ASSERT_IS_EQ(sf_list_head(strings), sf_string("one"));
}


SF_TEST_SUITE(sf_collection_filter_tests,
              sf_filter_empty_array,
              sf_filter_array_with_one_item,
              sf_filter_array_with_two_items
              );


static bool
is_int_type(sf_any_t item, void *context)
{
  return sf_int_type == sf_type_of(item);
}


static bool
is_string_type(sf_any_t item, void *context)
{
  return sf_string_type == sf_type_of(item);
}
