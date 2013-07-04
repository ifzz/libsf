#include <sf/sf.h>
#include <sf_test/sf_test.h>


static sf_any_t
collect_type(sf_any_t item, void *context);


SF_TEST_CASE(sf_collect_from_empty_array)
{
  sf_array_t collection = NULL;
  
  sf_list_t types = sf_collect(collection, collect_type, NULL);
  
  SF_ASSERT_INT_EQ(sf_count(types), 0);
}


SF_TEST_CASE(sf_collect_from_array_with_one_item)
{
  sf_array_t collection = sf_array_from_items(sf_string("one"));
  
  sf_list_t types = sf_collect(collection, collect_type, NULL);
  
  SF_ASSERT_INT_EQ(sf_count(types), 1);
  SF_ASSERT_IS_EQ(sf_list_head(types), sf_string_type);
}


SF_TEST_CASE(sf_collect_from_array_with_two_items)
{
  sf_array_t collection = sf_array_from_items(sf_string("one"), sf_int(2));
  
  sf_list_t types = sf_collect(collection, collect_type, NULL);
  
  SF_ASSERT_INT_EQ(sf_count(types), 2);
  SF_ASSERT_IS_EQ(sf_list_head(types), sf_string_type);
}


SF_TEST_CASE(sf_collect_from_array_with_three_items)
{
  sf_array_t collection = sf_array_from_items(sf_string("one"), sf_int(2), sf_random_type);
  
  sf_list_t types = sf_collect(collection, collect_type, NULL);
  
  SF_ASSERT_INT_EQ(sf_count(types), 3);
  SF_ASSERT_IS_EQ(sf_list_head(types), sf_string_type);
}


SF_TEST_CASE(sf_collect_strings_from_array_with_two_items)
{
  sf_array_t collection = sf_array_from_items(sf_int(1), sf_string("two"));
  
  sf_list_t types = sf_collect_strings(collection);
  
  SF_ASSERT_INT_EQ(sf_count(types), 2);
  SF_ASSERT_IS_EQ(sf_list_head(types), sf_string("1"));
}


SF_TEST_SUITE(sf_collection_collect_tests,
              sf_collect_from_empty_array,
              sf_collect_from_array_with_one_item,
              sf_collect_from_array_with_two_items,
              sf_collect_from_array_with_three_items,
              sf_collect_strings_from_array_with_two_items
              );


static sf_any_t
collect_type(sf_any_t item, void *context)
{
  return sf_type_of(item);
}
