#ifndef SF_SF_STRING_H_INCLUDED
#define SF_SF_STRING_H_INCLUDED


#include <stdarg.h>
#include <sf/sf_defs.h>


extern sf_type_t sf_string_type;


sf_string_t 
sf_string(char const *chars);

char const *
sf_string_chars(sf_string_t string);

sf_string_t
sf_string_from_format(char const *format, ...) SF_FORMAT_FUNCTION(1, 2);

sf_string_t
sf_string_from_format_and_arguments(char const *format, va_list arguments);

#define sf_string_from_items(...) \
        sf_string_from_separator_and_collection(NULL, sf_array_from_items(__VA_ARGS__))

sf_string_t
sf_string_from_prefix_and_collection(sf_string_t prefix, sf_any_t collection);

#define sf_string_from_prefix_and_items(PREFIX, ...) \
        sf_string_from_prefix_and_collection((PREFIX), sf_array_from_items(__VA_ARGS__))

sf_string_t
sf_string_from_separator_and_collection(sf_string_t separator, sf_any_t collection);

#define sf_string_from_separator_and_items(SEPARATOR, ...) \
        sf_string_from_separator_and_collection((SEPARATOR), sf_array_from_items(__VA_ARGS__))

sf_string_t
sf_string_from_suffix_and_collection(sf_string_t suffix, sf_any_t collection);

#define sf_string_from_suffix_and_items(SUFFIX, ...) \
        sf_string_from_suffix_and_collection((SUFFIX), sf_array_from_items(__VA_ARGS__))

int
sf_string_length(sf_string_t string);


#endif
