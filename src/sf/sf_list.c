#include "sf_list.h"

#include "sf_collection.h"
#include "sf_object.h"
#include "sf_string.h"
#include "sf_temp_pool.h"
#include "sf_type.h"


static bool
build_reversed_list(sf_any_t item, void *context);

static int
count(sf_any_t self);

static void
dealloc(sf_any_t self);

static bool
each(sf_any_t self, sf_act_on act_on, void *context);

static sf_string_t
string_from(sf_any_t self);


struct _sf_list
{
  SF_OBJECT_FIELDS;
  int count;
  sf_any_t head;
  sf_list_t tail;
};


sf_type_t sf_list_type;


void
_sf_list_init(void)
{
  sf_list_type = sf_type("sf_list_t", dealloc, string_from, NULL, NULL, count, each);
}


static bool
build_reversed_list(sf_any_t item, void *context)
{
  sf_list_t *list = context;
  *list = sf_list(item, *list);
  return true;
}


static int
count(sf_any_t self)
{
  sf_list_t list = self;
  return list->count;
}


static void
dealloc(sf_any_t self)
{
  sf_list_t list = self;
  
  sf_release(list->head);
  sf_release(list->tail);
}


static bool
each(sf_any_t self, sf_act_on act_on, void *context)
{
  sf_list_t list = self;
  while (list) {
    bool keep_going = act_on(list->head, context);
    if (not keep_going) return false;
    list = list->tail;
  }
  return true;
}


sf_list_t 
sf_list(sf_any_t head, sf_list_t tail)
{
  struct _sf_list *list = sf_object_calloc(sizeof(struct _sf_list), sf_list_type);
  if ( ! list) return NULL;

  list->count = sf_count(tail) + 1;
  list->head = sf_retain(head);
  list->tail = sf_retain(tail);

  return sf_move_to_temp_pool(list);
}


sf_list_t
sf_list_from_collection(sf_any_t collection)
{
  if (sf_list_type == sf_type_of(collection)) return sf_copy_to_temp_pool(collection);
  
  sf_array_t array = sf_array_from_collection(collection);
  sf_list_t list = NULL;
  for (int i = sf_count(array) - 1; i >= 0; --i) {
    list = sf_list(sf_array_item_at_index(array, i), list);
  }
  return list;
}


sf_any_t
sf_list_head(sf_list_t list)
{
  return sf_copy_to_temp_pool(list ? list->head : NULL);
}


sf_list_t 
sf_list_reversed(sf_any_t collection)
{
  if (sf_count(collection) <= 1) return sf_copy_to_temp_pool(collection);
  
  sf_list_t reversed = NULL;
  sf_each(collection, build_reversed_list, &reversed);
  return reversed;
}


sf_list_t
sf_list_tail(sf_list_t list)
{
  return sf_copy_to_temp_pool(list ? list->tail : NULL);
}


static sf_string_t
string_from(sf_any_t self)
{
  sf_string_t comma_separated = sf_string_from_separator_and_collection(sf_string(","), self);
  return sf_string_from_format("(%s)", sf_string_chars(comma_separated));
}
