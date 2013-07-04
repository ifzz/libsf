#include "sf_string.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "sf_list.h"
#include "sf_object.h"
#include "sf_temp_pool.h"
#include "sf_type.h"
#include "sf_collection.h"


enum join_method {
  between_each,
  before_each,
  after_each,
};


static bool
accumulate_string_length(sf_any_t item, void *context);

static int
hash_code(sf_any_t self);

static bool
is_equal(sf_any_t self, sf_any_t other);

static sf_string_t 
join(sf_string_t separator, enum join_method method, sf_any_t collection);

static struct _sf_string *
string_for_length(size_t length);

static sf_string_t 
string_from(sf_any_t self);


struct _sf_string
{
  SF_OBJECT_FIELDS;
  int length;
  char chars[];
};


sf_type_t sf_string_type;


void
_sf_string_init(void)
{
  sf_string_type = sf_type("sf_string_t", NULL, string_from, is_equal, hash_code, NULL, NULL);
}


static bool
accumulate_string_length(sf_any_t item, void *context)
{
  sf_string_t string = item;
  size_t *length = context;
  *length += sf_string_length(string);
  return true;
}


static int
hash_code(sf_any_t self)
{
  sf_string_t string = self;
  
  int hash_code = 71;
  char const *ch = string->chars;
  while (*ch) {
    hash_code = (37 * hash_code) + (int) *ch;
    ++ch;
  }
  
  return hash_code;
}


static bool
is_equal(sf_any_t self, sf_any_t other)
{
  sf_string_t string = self;
  sf_string_t other_string = other;
  
  if (string->chars == other_string->chars) return true;
  if (not string->chars) return false;
  if (not other_string->chars) return false;
  
  return 0 == strcmp(string->chars, other_string->chars);
}


static sf_string_t
join(sf_string_t separator, enum join_method method, sf_any_t collection)
{
  sf_list_t items = sf_collect_strings(collection);
  if (not sf_count(items)) return NULL;
  
  size_t length = 0;
  sf_each(items, accumulate_string_length, &length);
  int separator_count = sf_count(items);
  if (between_each == method) --separator_count;
  length += separator_count * sf_string_length(separator);
  
  struct _sf_string *string = string_for_length(length);
  if ( ! string) return NULL;
  
  if (separator and before_each == method) strcat(string->chars, separator->chars);
  while (items) {
    sf_string_t item = sf_list_head(items);
    items = sf_list_tail(items);
    
    if (item) strcat(string->chars, item->chars);
    if (items and separator) strcat(string->chars, separator->chars);
  }
  if (separator and after_each == method) strcat(string->chars, separator->chars);
  
  return string;
}


sf_string_t 
sf_string(char const *chars)
{
  if (not chars) return NULL;

  struct _sf_string *string = string_for_length(strlen(chars));
  if (string) strcpy(string->chars, chars);
  return string;
}


char const *
sf_string_chars(sf_string_t string)
{
  return string and string->chars ? string->chars : "";
}


sf_string_t
sf_string_from_format(char const *format, ...)
{
  assert(format);
  
  va_list arguments;
  va_start(arguments, format);
  sf_string_t formatted = sf_string_from_format_and_arguments(format, arguments);
  va_end(arguments);
  
  return formatted;
}


sf_string_t
sf_string_from_format_and_arguments(char const *format, va_list arguments)
{
  assert(format);
  
  va_list arguments_copy;
  va_copy(arguments_copy, arguments);
  
  int length = vsnprintf(NULL, 0, format, arguments);
  struct _sf_string *string = string_for_length(length);
  if (string) {
    vsnprintf(string->chars, length + 1, format, arguments_copy);
  }
  return string;
}


sf_string_t
sf_string_from_prefix_and_collection(sf_string_t prefix, sf_any_t collection)
{
  return join(prefix, before_each, collection);
}


sf_string_t
sf_string_from_separator_and_collection(sf_string_t separator, sf_any_t collection)
{
  return join(separator, between_each, collection);
}


sf_string_t
sf_string_from_suffix_and_collection(sf_string_t suffix, sf_any_t collection)
{
  return join(suffix, after_each, collection);
}


int
sf_string_length(sf_string_t string)
{
  return string ? string->length : 0;
}


static struct _sf_string *
string_for_length(size_t length)
{
  assert(length < INT_MAX);
  
  size_t size = sizeof(struct _sf_string) + length + 1;
  struct _sf_string *string = sf_object_malloc(size, sf_string_type);
  if (not string) return NULL;
  
  string->length = (int) length;
  string->chars[0] = '\0';
  return (struct _sf_string *) sf_move_to_temp_pool(string);
}


static sf_string_t
string_from(sf_any_t self)
{
  return sf_copy_to_temp_pool(self);
}
