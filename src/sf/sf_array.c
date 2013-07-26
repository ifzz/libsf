#include "sf_array.h"

#include <stdlib.h>
#include <string.h>
#include "sf_collection.h"
#include "sf_key.h"
#include "sf_memory.h"
#include "sf_object.h"
#include "sf_random.h"
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
each_from_collection(sf_any_t item, void *context);

static bool
is_equal(sf_any_t self, sf_any_t other);

static sf_string_t
string_from(sf_any_t self);


struct from_collection_context
{
  sf_any_t *items;
  int index;
  bool reversed;
};


struct _sf_array
{
  SF_OBJECT_FIELDS;
  int count;
  sf_any_t items[];
};


sf_type_t sf_array_type;


void
_sf_array_init(void)
{
  sf_array_type = sf_type("sf_array_t", dealloc, string_from, is_equal, NULL, count, each);
}


struct _sf_array *
array_for_count(int count)
{
  if (not count) return NULL;
  
  size_t size = sizeof(struct _sf_array) + (count * sizeof(sf_any_t));
  struct _sf_array *array = sf_object_malloc(size, sf_array_type);
  if (not array) return NULL;
  
  array->count = count;
  return (struct _sf_array *) sf_move_to_temp_pool(array);
}


static int
count(sf_any_t self)
{
  sf_array_t array = self;
  return array->count;
}


static void
dealloc(sf_any_t self)
{
  sf_array_t array = self;
  for (int i = 0; i < array->count; ++i) sf_release(array->items[i]);
}


static bool
each(sf_any_t self, sf_act_on act_on, void *context)
{
  sf_array_t array = self;
  for (int i = 0; i < array->count; ++i) {
    bool keep_going = act_on(array->items[i], context);
    if (not keep_going) return false;
  }
  return true;
}


static bool
each_from_collection(sf_any_t item, void *context)
{
  struct from_collection_context *from_collection_contest = context;
  sf_any_t *items = from_collection_contest->items;
  int index = from_collection_contest->index;
  items[index] = sf_retain(item);
  from_collection_contest->index += from_collection_contest->reversed ? -1 : 1;
  return true;
}


static bool
is_equal(sf_any_t self, sf_any_t other)
{
  if (sf_count(self) != sf_count(other)) return false;
  
  sf_array_t array = self;
  sf_array_t other_array = other;
  for (int i = 0; i < array->count; ++i) {
    if (not sf_is_equal(array->items[i], other_array->items[i])) return false;
  }
  return true;
}


sf_array_t
sf_array(sf_any_t *items, int count)
{
  if (not items) return NULL;
  
  struct _sf_array *array = array_for_count(count);
  if (array) {
    for (int i = 0; i < count; ++i) {
      array->items[i] = sf_retain(items[i]);
    }
  }
  return array;
}


sf_array_t
sf_array_from_collection(sf_any_t collection)
{
  if (sf_array_type == sf_type_of(collection)) return sf_copy_to_temp_pool(collection);
  
  struct _sf_array *array = array_for_count(sf_count(collection));
  if (array) {
    struct from_collection_context from_collection_context = {
      .items = array->items,
      .index = 0,
      .reversed = false,
    };
    sf_each(collection, each_from_collection, &from_collection_context);
  }
  return array;
}


sf_any_t
sf_array_item_at_index(sf_array_t array, int index)
{
  if (index < 0) return NULL;
  if (array and index < array->count) return sf_copy_to_temp_pool(array->items[index]);
  return NULL;
}


sf_any_t const*
sf_array_items(sf_array_t array)
{
  return array ? array->items : NULL;
}


sf_array_t
sf_array_reversed(sf_any_t collection)
{
  int count = sf_count(collection);
  if (count < 2 and sf_array_type == sf_type_of(collection)) {
    return sf_copy_to_temp_pool(collection);
  }
  
  struct _sf_array *reversed = array_for_count(count);
  if (reversed) {
    struct from_collection_context from_collection_context = {
      .items = reversed->items,
      .index = count - 1,
      .reversed = true,
    };
    sf_each(collection, each_from_collection, &from_collection_context);
  }
  return reversed;
}


sf_array_t
sf_array_shuffled(sf_array_t array, sf_random_t random_in, sf_random_t *random_out)
{
  if (random_out) *random_out = random_in;
  
  int count = sf_count(array);
  if (count < 2) return sf_copy_to_temp_pool(array);
  
  struct _sf_array *shuffled = array_for_count(count);
  if (not array) return NULL;
  
  for (int i = 0; i < count; ++i) {
    shuffled->items[i] = sf_retain(array->items[i]);
  }
  
  sf_random_t random = random_in;
  for (int unshuffled = count; unshuffled > 1; --unshuffled) {
    int i = unshuffled - 1;
    random = sf_random_next_from_range(random, unshuffled);
    int j = sf_random_value(random);
    
    sf_any_t temp = shuffled->items[i];
    shuffled->items[i] = shuffled->items[j];
    shuffled->items[j] = temp;
  }
  
  if (random_out) *random_out = random;
  return shuffled;
}


static sf_string_t
string_from(sf_any_t self)
{
  sf_string_t comma_separated = sf_string_from_separator_and_collection(sf_string(","), self);
  return sf_string_from_format("[%s]", sf_string_chars(comma_separated));
}
