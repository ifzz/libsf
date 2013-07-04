#include <sf/sf.h>
#include <sf_test/sf_test.h>


static bool
count_items(sf_any_t item, void *context);


SF_TEST_CASE(NULL_sf_ensemble)
{
  sf_ensemble_t ensemble = NULL;
  
  SF_ASSERT_INT_EQ(sf_ensemble_count(ensemble), 0);
  SF_ASSERT_NULL(sf_ensemble_collections(ensemble));
  
  SF_ASSERT_INT_EQ(sf_count(ensemble), 0);
  int count = 0;
  SF_ASSERT_TRUE(sf_each(ensemble, count_items, &count));
  SF_ASSERT_INT_EQ(count, 0);
}


SF_TEST_CASE(sf_ensemble_from_one_collection)
{
  sf_array_t collection1 = sf_array_from_items(sf_string("foo"), sf_int(42));
  sf_ensemble_t ensemble = sf_ensemble(collection1);
  
  SF_ASSERT_INT_EQ(sf_ensemble_count(ensemble), 1);
  SF_ASSERT_NOT_NULL(sf_ensemble_collections(ensemble));
  
  SF_ASSERT_INT_EQ(sf_count(ensemble), 2);
  int count = 0;
  SF_ASSERT_TRUE(sf_each(ensemble, count_items, &count));
  SF_ASSERT_INT_EQ(count, 2);
  
  SF_ASSERT_IS_EQ(sf_string_from(ensemble), sf_string("((foo,42))"));
}


SF_TEST_CASE(sf_ensemble_from_two_collections)
{
  sf_array_t collection1 = sf_array_from_items(sf_string("foo"), sf_int(42));
  sf_list_t collection2 = sf_list_from_items(sf_string("bar"), sf_int(-3), sf_list_type);
  sf_ensemble_t ensemble = sf_ensemble(collection1, collection2);
  
  SF_ASSERT_INT_EQ(sf_ensemble_count(ensemble), 2);
  SF_ASSERT_NOT_NULL(sf_ensemble_collections(ensemble));
  
  SF_ASSERT_INT_EQ(sf_count(ensemble), 5);
  int count = 0;
  SF_ASSERT_TRUE(sf_each(ensemble, count_items, &count));
  SF_ASSERT_INT_EQ(count, 5);
  
  SF_ASSERT_IS_EQ(sf_string_from(ensemble), sf_string("((foo,42,bar,-3,sf_list_t))"));
}


SF_TEST_CASE(sf_ensemble_from_three_collections)
{
  sf_array_t collection1 = sf_array_from_items(sf_string("foo"), sf_int(42));
  sf_list_t collection2 = sf_list_from_items(sf_string("bar"), sf_int(-3), sf_list_type);
  sf_pair_t collection3 = sf_pair(sf_string("fnord"), sf_long(17));
  sf_ensemble_t ensemble = sf_ensemble(collection1, collection2, collection3);
  
  SF_ASSERT_INT_EQ(sf_ensemble_count(ensemble), 3);
  SF_ASSERT_NOT_NULL(sf_ensemble_collections(ensemble));
  
  SF_ASSERT_INT_EQ(sf_count(ensemble), 7);
  int count = 0;
  SF_ASSERT_TRUE(sf_each(ensemble, count_items, &count));
  SF_ASSERT_INT_EQ(count, 7);
  
  SF_ASSERT_IS_EQ(sf_string_from(ensemble), sf_string("((foo,42,bar,-3,sf_list_t,fnord,17L))"));
}


SF_TEST_SUITE(sf_ensemble_tests,
              NULL_sf_ensemble,
              sf_ensemble_from_one_collection,
              sf_ensemble_from_two_collections,
              sf_ensemble_from_three_collections
              );


static bool
count_items(sf_any_t item, void *context)
{
  int *count = context;
  ++*count;
  return true;
}
