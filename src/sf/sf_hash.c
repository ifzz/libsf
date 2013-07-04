#include "sf_hash.h"

#include <stdlib.h>
#include "sf_array.h"
#include "sf_collection.h"
#include "sf_key.h"
#include "sf_list.h"
#include "sf_memory.h"
#include "sf_object.h"
#include "sf_pair.h"
#include "sf_string.h"
#include "sf_temp_pool.h"
#include "sf_type.h"


static int
count(sf_any_t self);

static void
dealloc(sf_any_t self);

static bool
each(sf_any_t self, sf_act_on act_on, void *context);

static bool
each_from_collections(sf_any_t item, void *context);

static sf_string_t
string_from(sf_any_t self);


struct _sf_hash
{
  SF_OBJECT_FIELDS;
  int count;
  sf_array_t buckets;
};


sf_type_t sf_hash_type;


void
_sf_hash_init(void)
{
  sf_hash_type = sf_type("sf_hash_t", dealloc, string_from, NULL, NULL, count, each);
}


static int
count(sf_any_t self)
{
  sf_hash_t hash = self;
  return hash->count;
}


static void
dealloc(sf_any_t self)
{
  sf_hash_t hash = self;
  sf_release(hash->buckets);
}


static bool
each(sf_any_t self, sf_act_on act_on, void *context)
{
  return false;
}


bool
sf_hash_contains_key(sf_hash_t hash, sf_any_t key)
{
  if (not hash) return false;
  
  int i = sf_hash_code(key) % sf_count(hash->buckets);
  sf_list_t bucket = sf_array_item_at_index(hash->buckets, i);
  while (bucket) {
    sf_pair_t pair = sf_list_head(bucket);
    if (sf_is_equal(key, sf_pair_left(pair))) return true;
    bucket = sf_list_tail(bucket);
  }
  return false;
}


sf_hash_t
sf_hash_from_keys_and_values(sf_any_t keys, sf_any_t values)
{
  int keys_count = sf_count(keys);
  if (not keys_count) return NULL;
  
  int values_count = sf_count(values);
  if (not values_count) return NULL;
  
  struct _sf_hash *hash = sf_object_calloc(sizeof(struct _sf_hash), sf_hash_type);
  if (not hash) return NULL;
  
  hash->count = keys_count < values_count ? keys_count : values_count;
  int bucket_count = (int) (hash->count * 1.3) + 1;
  
  sf_any_t *buckets = sf_calloc(bucket_count, sizeof(sf_any_t));
  if ( ! buckets) {
    sf_free(hash);
    return NULL;
  }
  
  sf_array_t keys_array = sf_array_from_collection(keys);
  sf_array_t values_array = sf_array_from_collection(values);
  for (int j = 0; j < hash->count; ++j) {
    sf_any_t key = sf_array_item_at_index(keys_array, j);
    sf_any_t value = sf_array_item_at_index(values_array, j);
    int i = sf_hash_code(key) % bucket_count;
    sf_pair_t pair = sf_pair(key, value);
    buckets[i] = sf_list(pair, buckets[i]);
  }
  
  hash->buckets = sf_retain(sf_array(buckets, bucket_count));
  sf_free(buckets);
  
  return sf_move_to_temp_pool(hash);
}


sf_any_t
sf_hash_value_for_key(sf_hash_t hash, sf_any_t key)
{
  if (not hash) return NULL;
  
  int i = sf_hash_code(key) % sf_count(hash->buckets);
  sf_list_t bucket = sf_array_item_at_index(hash->buckets, i);
  while (bucket) {
    sf_pair_t pair = sf_list_head(bucket);
    if (sf_is_equal(key, sf_pair_left(pair))) return sf_pair_right(pair);
    bucket = sf_list_tail(bucket);
  }
  return NULL;
}


static sf_string_t
string_from(sf_any_t self)
{
  return sf_string_from_format("{?}");
}
