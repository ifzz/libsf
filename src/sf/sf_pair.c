#include "sf_pair.h"

#include "sf_object.h"
#include "sf_string.h"
#include "sf_temp_pool.h"
#include "sf_type.h"


static int
count(sf_any_t self);

static void
dealloc(sf_any_t self);

static bool
each(sf_any_t self, sf_act_on act_on, void *context);

static sf_string_t
string_from(sf_any_t self);


struct _sf_pair
{
  SF_OBJECT_FIELDS;
  sf_any_t left;
  sf_any_t right;
};


sf_type_t sf_pair_type;


void
_sf_pair_init(void)
{
  sf_pair_type = sf_type("sf_pair_t", dealloc, string_from, NULL, NULL, count, each);
}


static int
count(sf_any_t self)
{
  return 2;
}


static void
dealloc(sf_any_t self)
{
  sf_pair_t pair = self;
  sf_release(pair->left);
  sf_release(pair->right);
}


static bool
each(sf_any_t self, sf_act_on act_on, void *context)
{
  sf_pair_t pair = self;
  if ( ! act_on(pair->left, context)) return false;
  return act_on(pair->right, context);
}


sf_pair_t
sf_pair(sf_any_t left, sf_any_t right)
{
  struct _sf_pair *pair = sf_object_calloc(sizeof(struct _sf_pair), sf_pair_type);
  if ( ! pair) return NULL;
  
  pair->left = sf_retain(left);
  pair->right = sf_retain(right);
  
  return sf_move_to_temp_pool(pair);
}


sf_any_t
sf_pair_left(sf_pair_t pair)
{
  return pair ? sf_copy_to_temp_pool(pair->left) : NULL;
}


sf_pair_t
sf_pair_reversed(sf_pair_t pair)
{
  return pair ? sf_pair(pair->right, pair->left) : NULL;
}


sf_any_t
sf_pair_right(sf_pair_t pair)
{
  return pair ? sf_copy_to_temp_pool(pair->right) : NULL;
}


static sf_string_t
string_from(sf_any_t self)
{
  sf_pair_t pair = self;
  return sf_string_from_format("<%s,%s>", sf_c_string_from(pair->left), sf_c_string_from(pair->right));
}
