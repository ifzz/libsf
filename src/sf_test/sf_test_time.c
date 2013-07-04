#include "sf_test_time.h"

#include <sf/sf_object.h>
#include <sf/sf_string.h>
#include <sf/sf_temp_pool.h>
#include <sf/sf_type.h>


static sf_string_t
string_from(sf_any_t self);


struct _sf_test_time
{
  SF_OBJECT_FIELDS;
  clock_t clocks;
  time_t value;
};


sf_type_t sf_test_time_type;


void
_sf_test_time_init(void)
{
  sf_test_time_type = sf_type("sf_test_time_t", NULL, string_from, NULL, NULL, NULL, NULL);
}


clock_t
sf_test_time_clocks(sf_test_time_t test_time)
{
  return test_time ? test_time->clocks : 0;
}


double
sf_test_time_elapsed_seconds(sf_test_time_t test_time1, sf_test_time_t test_time2)
{
  clock_t clocks1 = sf_test_time_clocks(test_time1);
  clock_t clocks2 = sf_test_time_clocks(test_time2);
  clock_t elapsed_clocks = (clocks1 > clocks2)
                         ? clocks1 - clocks2
                         : clocks2 - clocks1;
  return (double) elapsed_clocks / (double) CLOCKS_PER_SEC;
}


sf_test_time_t
sf_test_time_now(void)
{
  struct _sf_test_time *test_time = sf_object_calloc(sizeof(struct _sf_test_time), sf_test_time_type);
  if ( ! test_time) return NULL;
  
  test_time->value = time(NULL);
  test_time->clocks = clock();
  
  return sf_move_to_temp_pool(test_time);
}


time_t
sf_test_time_value(sf_test_time_t test_time)
{
  return test_time ? test_time->value : 0;
}


static sf_string_t
string_from(sf_any_t self)
{
  sf_test_time_t test_time = self;  
  return sf_string_from_format("test time: %li (%lu clocks)", (long) test_time->value, (unsigned long) test_time->clocks);
}
