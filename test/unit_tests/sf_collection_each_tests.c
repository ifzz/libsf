#include <sf/sf.h>
#include <sf_test/sf_test.h>


static bool
act_on(sf_any_t item, void *context);


struct each_context
{
  int count;
};


SF_TEST_CASE(sf_each_for_NULL)
{
  struct each_context each_context = { .count = 0, };
  
  bool result = sf_each(NULL, act_on, &each_context);
  
  SF_ASSERT_TRUE(result);
  SF_ASSERT_INT_EQ(each_context.count, 0);
}


SF_TEST_CASE(sf_each_for_collection)
{
  struct each_context each_context = { .count = 0, };
  sf_array_t collection1 = sf_array_from_items(sf_string("one"));
  bool result = sf_each(collection1, act_on, &each_context);
  
  SF_ASSERT_TRUE(result);
  SF_ASSERT_INT_EQ(each_context.count, 1);
}


SF_TEST_SUITE(sf_collection_each_tests,
              sf_each_for_NULL,
              sf_each_for_collection
              );


static bool
act_on(sf_any_t item, void *context)
{
  struct each_context *each_context = context;
  ++each_context->count;
  return true;
}
