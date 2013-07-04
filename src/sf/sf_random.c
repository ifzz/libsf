#include "sf_random.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sf_object.h"
#include "sf_string.h"
#include "sf_temp_pool.h"
#include "sf_type.h"


static char const *dev_random_path = "/dev/random";


static int
next_uniform_random_value(unsigned short const state_in[3], long range, unsigned short state_out[3]);

static void
random_state(char const *dev_random_path, unsigned short state_out[3]);


struct _sf_random
{
  SF_OBJECT_FIELDS;
  long range;
  unsigned short state[3];
  int value;
};


sf_type_t sf_random_type;


void
_sf_random_init(void)
{
  sf_random_type = sf_type("sf_random_t", NULL, NULL, NULL, NULL, NULL, NULL);
}


static int
next_uniform_random_value(unsigned short const state_in[3], long range, unsigned short state_out[3])
{
  long modulo_bias_range = SF_RANDOM_RANGE % range;
  long largest_multiple = SF_RANDOM_MAX - modulo_bias_range;
  long next_value;
  memcpy(state_out, state_in, sizeof(unsigned short[3]));
  do {
    next_value = nrand48(state_out);
  } while (next_value > largest_multiple);
  
  int value = (int) (next_value % range);
  assert(value >= 0);
  assert(value < range);
  
  return value;
}


static void
random_state(char const *dev_random_path, unsigned short state_out[3])
{
  FILE *file = fopen(dev_random_path, "rb");
  if ( ! file) {
    if (errno) fprintf(stderr, "ERROR: (%i) %s\n", errno, strerror(errno));
    fprintf(stderr, "ERROR: unable to open \"%s\"\n", dev_random_path);
    exit(EXIT_FAILURE);
  }

  size_t item_count = 1;
  size_t items_read = fread(state_out, sizeof(unsigned short[3]), item_count, file);
  fclose(file);

  if (items_read < item_count) {
    if (errno) fprintf(stderr, "ERROR: (%i) %s\n", errno, strerror(errno));
    fprintf(stderr, "ERROR: unable to read \"%s\"\n", dev_random_path);
    exit(EXIT_FAILURE);
  }
}


sf_random_t 
sf_random_next(sf_random_t random)
{
  return sf_random_next_from_range(random, random->range);
}


sf_random_t 
sf_random_next_from_range(sf_random_t random, long range)
{
  unsigned short state_out[3];
  int value = next_uniform_random_value(random->state, range, state_out);
  return sf_random_from_state_range_and_value(state_out, range, value);
}


long
sf_random_range(sf_random_t random)
{
  return random ? random->range : 0;
}


unsigned short const *
sf_random_state(sf_random_t random)
{
  return random ? random->state : NULL;
}


int
sf_random_value(sf_random_t random)
{
  return random ? random->value : 0;
}


sf_random_t 
sf_random_from_random_state(void)
{
  return sf_random_from_random_state_and_range(SF_RANDOM_RANGE);
}


sf_random_t 
sf_random_from_random_state_and_range(long range)
{
  unsigned short state[3];
  random_state(dev_random_path, state);
  return sf_random_from_state_and_range(state, range);
}


sf_random_t
sf_random_from_state(unsigned short const state[3])
{
  return sf_random_from_state_range_and_value(state, SF_RANDOM_RANGE, 0);
}


sf_random_t 
sf_random_from_state_and_range(unsigned short const state[3], long range)
{
  return sf_random_from_state_range_and_value(state, range, 0);
}


sf_random_t 
sf_random_from_state_range_and_value(unsigned short const state[3], long range, int value)
{
  assert(range > 0);
  assert(range <= SF_RANDOM_RANGE);
  
  struct _sf_random *random = sf_object_calloc(sizeof(struct _sf_random), sf_random_type);
  if ( ! random) return NULL;
  
  random->range = range;
  memcpy(random->state, state, sizeof(unsigned short[3]));
  random->value = value;
  
  return sf_move_to_temp_pool(random);
}
