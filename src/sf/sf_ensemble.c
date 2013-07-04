#include "sf_ensemble.h"

#include "sf_collection.h"
#include "sf_object.h"
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


struct _sf_ensemble
{
  SF_OBJECT_FIELDS;
  int count;
  sf_array_t collections;
};


sf_type_t sf_ensemble_type;


void
_sf_ensemble_init(void)
{
  sf_ensemble_type = sf_type("sf_ensemble_t", dealloc, string_from, NULL, NULL, count, each);
}


static int
count(sf_any_t self)
{
  sf_ensemble_t ensemble = self;
  return ensemble->count;
}


static void
dealloc(sf_any_t self)
{
  sf_ensemble_t ensemble = self;
  sf_release(ensemble->collections);
}


static bool
each(sf_any_t self, sf_act_on act_on, void *context)
{
  sf_ensemble_t ensemble = self;
  for (int i = 0; i < sf_count(ensemble->collections); ++i) {
    bool keep_going = sf_each(sf_array_item_at_index(ensemble->collections, i), act_on, context);
    if (not keep_going) return false;
  }
  return true;
}


sf_array_t
sf_ensemble_collections(sf_ensemble_t ensemble)
{
  return ensemble ? sf_copy_to_temp_pool(ensemble->collections) : NULL;
}


int
sf_ensemble_count(sf_ensemble_t ensemble)
{
  return ensemble ? sf_count(ensemble->collections) : 0;
}


sf_ensemble_t
sf_ensemble_from_collections(sf_array_t collections)
{
  struct _sf_ensemble *ensemble = sf_object_calloc(sizeof(struct _sf_ensemble), sf_ensemble_type);
  if (not ensemble) return NULL;
  
  ensemble->collections = sf_retain(collections);
  for (int i = 0; i < sf_count(collections); ++i) {
    ensemble->count += sf_count(sf_array_item_at_index(collections, i));
  }
  
  return sf_move_to_temp_pool(ensemble);
}


static sf_string_t
string_from(sf_any_t self)
{
  sf_string_t comma_separated = sf_string_from_separator_and_collection(sf_string(","), self);
  return sf_string_from_format("((%s))", sf_string_chars(comma_separated));
}
