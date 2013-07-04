#include "sf_collection.h"

#include "sf_list.h"
#include "sf_object.h"
#include "sf_type.h"


struct collect_context
{
  sf_collect_from collect_from;
  void *context;
  sf_list_t collected_items;
};


struct filter_context
{
  sf_is_included is_included;
  void *context;
  sf_list_t included_items;
};


static bool
collect_from_each(sf_any_t item, void *context);

static bool
filter_each(sf_any_t item, void *context);

static sf_any_t
string_from(sf_any_t any, void *context);


static bool
collect_from_each(sf_any_t item, void *context)
{
  struct collect_context *collect_context = context;
  sf_any_t collected_item = collect_context->collect_from(item, collect_context->context);
  collect_context->collected_items = sf_list(collected_item, collect_context->collected_items);
  return true;
}


static bool
filter_each(sf_any_t item, void *context)
{
  struct filter_context *filter_context = context;
  if (filter_context->is_included(item, filter_context->context)) {
    filter_context->included_items = sf_list(item, filter_context->included_items);
  }
  return true;
}


sf_list_t
sf_collect(sf_any_t collection, sf_collect_from collect_from, void *context)
{
  struct collect_context collect_context = {
    .context = context,
    .collect_from = collect_from,
    .collected_items = NULL,
  };
  
  sf_each(collection, collect_from_each, &collect_context);
  return sf_list_reversed(collect_context.collected_items);
}


sf_list_t
sf_collect_strings(sf_any_t collection)
{
  return sf_collect(collection, string_from, NULL);
}


int
sf_count(sf_any_t collection)
{
  sf_type_t type = sf_type_of(collection);
  return sf_type_method_count(type)(collection);
}


int
sf_default_method_count(sf_any_t collection)
{
  return 0;
}


bool
sf_default_method_each(sf_any_t item, sf_act_on act_on, void *context)
{
  return true;
}


bool
sf_each(sf_any_t collection, sf_act_on act_on, void *context)
{
  sf_type_t type = sf_type_of(collection);
  return sf_type_method_each(type)(collection, act_on, context);
}


sf_list_t
sf_filter(sf_any_t collection, sf_is_included is_included, void *context)
{
  struct filter_context filter_context = {
    .context = context,
    .is_included = is_included,
    .included_items = NULL,
  };
  
  sf_each(collection, filter_each, &filter_context);
  return sf_list_reversed(filter_context.included_items);
}


bool
sf_is_collection_type(sf_any_t any)
{
  sf_type_t type = sf_type_of(any);
  return sf_type_is_collection_type(type);
}


static sf_any_t
string_from(sf_any_t any, void *context)
{
  return sf_string_from(any);
}
