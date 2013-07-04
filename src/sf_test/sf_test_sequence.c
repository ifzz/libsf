#include "sf_test_sequence.h"

#include <assert.h>
#include <sf/sf_collection.h>
#include <sf/sf_list.h>
#include <sf/sf_pair.h>
#include <sf/sf_object.h>
#include <sf/sf_temp_pool.h>
#include <sf/sf_type.h>
#include "sf_test_case.h"
#include "sf_test_monitor.h"
#include "sf_test_suite.h"
#include "sf_test_time.h"


static sf_list_t
add_test_pair(sf_list_t pairs, sf_any_t any, sf_list_t test_suites);

static bool
add_each_test_pair(sf_any_t item, void *context);

static int
count(sf_any_t self);

static void
dealloc(sf_any_t self);

static bool
each(sf_any_t self, sf_act_on act_on, void *context);

static bool
run_each_test_case(sf_any_t item, void *context);

static sf_string_t
string_from(sf_any_t self);

static sf_test_sequence_t
test_sequence_from_pairs(sf_any_t pairs);


struct add_test_pair_context
{
  sf_list_t pairs;
  sf_list_t test_suites;
};

struct _sf_test_sequence
{
  SF_OBJECT_FIELDS;
  sf_list_t pairs;
};


sf_type_t sf_test_sequence_type;


void
_sf_test_sequence_init(void)
{
  sf_test_sequence_type = sf_type("sf_test_sequence_t", dealloc, string_from, NULL, NULL, count, each);
}


static sf_list_t
add_test_pair(sf_list_t pairs, sf_any_t any, sf_list_t test_suites)
{
  if (sf_test_case_type == sf_type_of(any)) {
    sf_pair_t pair = sf_pair(any, test_suites);
    return sf_list(pair, pairs);
  } else if (sf_test_suite_type == sf_type_of(any)) {
    sf_test_suite_t test_suite = any;
    test_suites = sf_list(test_suite, test_suites);
    return add_test_pair(pairs, sf_test_suite_items(test_suite), test_suites);
  } else if (sf_is_collection_type(any)) {
    struct add_test_pair_context add_test_pairs_context = {
      .pairs = pairs,
      .test_suites = test_suites,
    };
    sf_each(any, add_each_test_pair, &add_test_pairs_context);
    return add_test_pairs_context.pairs;
  } else {
    return pairs;
  }
}


static bool
add_each_test_pair(sf_any_t item, void *context)
{
  struct add_test_pair_context *add_test_pairs_context = context;
  sf_list_t pairs = add_test_pairs_context->pairs;
  sf_list_t test_suites = add_test_pairs_context->test_suites;
  add_test_pairs_context->pairs = add_test_pair(pairs, item, test_suites);
  return true;
}


static int
count(sf_any_t self)
{
  sf_test_sequence_t test_sequence = self;
  return sf_count(test_sequence->pairs);
}


static void
dealloc(sf_any_t self)
{
  sf_test_sequence_t test_sequence = self;
  sf_release(test_sequence->pairs);
}


static bool
each(sf_any_t self, sf_act_on act_on, void *context)
{
  sf_test_sequence_t test_sequence = self;
  return sf_each(test_sequence->pairs, act_on, context);
}


static bool
run_each_test_case(sf_any_t item, void *context)
{
  sf_temp_pool();
  
  sf_pair_t pair = item;
  sf_test_case_t test_case = sf_pair_left(pair);
  sf_list_t test_suites = sf_pair_right(pair);
  
  struct sf_test_monitor *test_monitor = context;
  if (test_monitor->test_case_will_start) {
    test_monitor->test_case_will_start(sf_test_time_now(), test_case, test_suites, test_monitor->context);
  }
  
  sf_temp_pool();
  sf_list_t test_failures = sf_test_case_run(test_case);
  test_failures = sf_retain(test_failures);
  sf_temp_pool_release();
  
  sf_move_to_temp_pool(test_failures);
  if (test_monitor->test_case_did_stop) {
    test_monitor->test_case_did_stop(sf_test_time_now(), test_case, test_suites, test_failures, test_monitor->context);
  }
  
  sf_temp_pool_release();
  return true;
}


sf_test_sequence_t
sf_test_sequence_from_array(sf_array_t array)
{
  sf_list_t pairs = NULL;
  for (int i = 0; i < sf_count(array); ++i) {
    sf_any_t item = sf_array_item_at_index(array, i);
    pairs = add_test_pair(pairs, item, NULL);
  }
  return test_sequence_from_pairs(pairs);
}


void
sf_test_sequence_run_test_cases(sf_test_sequence_t test_sequence, struct sf_test_monitor *test_monitor)
{
  assert(test_sequence);
  assert(test_monitor);
  
  if (test_monitor->test_sequence_will_start) {
    test_monitor->test_sequence_will_start(sf_test_time_now(), test_sequence, test_monitor->context);
  }
  sf_each(test_sequence, run_each_test_case, test_monitor);
  if (test_monitor->test_sequence_did_stop) {
    test_monitor->test_sequence_did_stop(sf_test_time_now(), test_sequence, test_monitor->context);
  }
}


sf_test_sequence_t
sf_test_sequence_shuffled(sf_test_sequence_t test_sequence, sf_random_t random_in, sf_random_t *random_out)
{
  sf_array_t pairs = sf_array_from_collection(test_sequence->pairs);
  sf_array_t shuffled = sf_array_shuffled(pairs, random_in, random_out);
  return test_sequence_from_pairs(shuffled);
}


static sf_string_t
string_from(sf_any_t self)
{
  sf_test_sequence_t test_sequence = self;
  return sf_string_from(test_sequence->pairs);
}


static sf_test_sequence_t
test_sequence_from_pairs(sf_any_t pairs)
{
  struct _sf_test_sequence *test_sequence = sf_object_calloc(sizeof(struct _sf_test_sequence), sf_test_sequence_type);
  if ( ! test_sequence) return NULL;
  
  test_sequence->pairs = sf_retain(sf_list_from_collection(pairs));
  
  return sf_move_to_temp_pool(test_sequence);
}
