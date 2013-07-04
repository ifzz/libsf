#include "sf_assert.h"

#include <stdarg.h>
#include <string.h>
#include <sf/sf_key.h>
#include <sf/sf_list.h>
#include <sf/sf_object.h>
#include <sf/sf_string.h>
#include "sf_test_failure.h"


static void
add_failure(sf_list_t *_sf_test_failures, char const *file, int line, char const *format, ...) SF_FORMAT_FUNCTION(4, 5);

static char const *
expression_value_description(char const *expression, char const *format, ...) SF_FORMAT_FUNCTION(2, 3);


static void
add_failure(sf_list_t *_sf_test_failures, char const *file, int line, char const *format, ...)
{
  va_list arguments;
  va_start(arguments, format);
  sf_string_t message = sf_string_from_format_and_arguments(format, arguments);
  va_end(arguments);
  
  sf_test_failure_t test_failure = sf_test_failure(file, line, message);
  *_sf_test_failures = sf_list(test_failure, *_sf_test_failures);
}


static char const *
expression_value_description(char const *expression, char const *format, ...)
{
  sf_string_t expression_string = sf_string(expression);
  
  va_list arguments;
  va_start(arguments, format);
  sf_string_t value_string = sf_string_from_format_and_arguments(format, arguments);
  va_end(arguments);
  
  if (0 == strcmp(format, "%p") and sf_is_equal(value_string, sf_string("0x0"))) {
    value_string = sf_string("NULL");
  }
  
  sf_string_t description = NULL;
  if (sf_is_equal(expression_string, value_string)) {
    description = sf_string_from_format("(%s)", expression);
  } else {
    description = sf_string_from_format("(%s) { %s }", expression, sf_c_string_from(value_string));
  }
  return sf_c_string_from(description);
}


bool
sf_assert_bool(char const *file, int line, char const *expression, bool actual, bool expected, sf_list_t *_sf_test_failures)
{
  if (actual == expected) return true;
  char const *format = expected ? "(%s) expected to be true" : "(%s) expected to be false";
  add_failure(_sf_test_failures, file, line, format, expression);
  return false;
}


bool
sf_assert_c_string_equals(char const *file, int line, char const *actual_expression, char const *actual_value, char const *expected_expression, char const *expected_value, sf_list_t *_sf_test_failures)
{
  if (actual_value == expected_value) return true;
  
  if (not actual_value) {
    add_failure(_sf_test_failures, file, line, "%s expected to equal %s",
                expression_value_description(actual_expression, "NULL"),
                expression_value_description(expected_expression, "\"%s\"", expected_value));
    return false;
  }
  
  if (not expected_value) {
    add_failure(_sf_test_failures, file, line, "%s expected to equal %s",
                expression_value_description(actual_expression, "\"%s\"", actual_value),
                expression_value_description(expected_expression, "NULL"));
    return false;
  }
  
  if (0 == strcmp(actual_value, expected_value)) return true;

  add_failure(_sf_test_failures, file, line, "%s expected to equal %s",
              expression_value_description(actual_expression, "\"%s\"", actual_value),
              expression_value_description(expected_expression, "\"%s\"", expected_value));
  return false;
}


bool
sf_assert_c_string_not_equals(char const *file, int line, char const *actual_expression, char const *actual_value, char const *unexpected_expression, char const *unexpected_value, sf_list_t *_sf_test_failures)
{
  if (not actual_value or not unexpected_value) {
    if (not actual_value and not unexpected_value) {
      add_failure(_sf_test_failures, file, line, "expected NULL to NOT equal NULL");
      return false;
    }

    return true;
  }

  if (0 == strcmp(actual_value, unexpected_value)) {
    add_failure(_sf_test_failures, file, line, "expected %s to NOT equal %s",
        expression_value_description(actual_expression, "\"%s\"", actual_value),
        expression_value_description(unexpected_expression, "\"%s\"", unexpected_value));
    return false;
  }

  return true;
}


bool
sf_assert_int_equals(char const *file, int line, char const *actual_expression, int actual_value, char const *expected_expression, int expected_value, sf_list_t *_sf_test_failures)
{
  if (actual_value == expected_value) return true;
  add_failure(_sf_test_failures, file, line, "expected %s to equal %s",
              expression_value_description(actual_expression, "%i", actual_value),
              expression_value_description(expected_expression, "%i", expected_value));
  return false;
}


bool
sf_assert_int_not_equals(char const *file, int line, char const *actual_expression, int actual_value, char const *unexpected_expression, int unexpected_value, sf_list_t *_sf_test_failures)
{
  if (actual_value != unexpected_value) return true;
  add_failure(_sf_test_failures, file, line, "expected %s to NOT equal %s",
              expression_value_description(actual_expression, "%i", actual_value),
              expression_value_description(unexpected_expression, "%i", unexpected_value));
  return false;
}


bool
sf_assert_is_equal(char const *file, int line, char const *actual_expression, sf_any_t actual_value, char const *expected_expression, sf_any_t expected_value, sf_list_t *_sf_test_failures)
{
  if (sf_is_equal(actual_value, expected_value)) return true;
  add_failure(_sf_test_failures, file, line, "expected %s to equal %s",
              expression_value_description(actual_expression, "%s", sf_c_string_from(actual_value)),
              expression_value_description(expected_expression, "%s", sf_c_string_from(expected_value)));
  return false;
}


bool
sf_assert_is_not_equal(char const *file, int line, char const *actual_expression, sf_any_t actual_value, char const *unexpected_expression, sf_any_t unexpected_value, sf_list_t *_sf_test_failures)
{
  if (not sf_is_equal(actual_value, unexpected_value)) return true;
  add_failure(_sf_test_failures, file, line, "%s expected to NOT equal %s",
              expression_value_description(actual_expression, "%s", sf_c_string_from(actual_value)),
              expression_value_description(unexpected_expression, "%s", sf_c_string_from(unexpected_value)));
  return false;
}


bool
sf_assert_long_equals(char const *file, int line, char const *actual_expression, long actual_value, char const *expected_expression, long expected_value, sf_list_t *_sf_test_failures)
{
  if (actual_value == expected_value) return true;
  add_failure(_sf_test_failures, file, line, "expected %s to equal %s",
              expression_value_description(actual_expression, "%li", actual_value),
              expression_value_description(expected_expression, "%li", expected_value));
  return false;
}


bool
sf_assert_long_not_equals(char const *file, int line, char const *actual_expression, long actual_value, char const *unexpected_expression, long unexpected_value, sf_list_t *_sf_test_failures)
{
  if (actual_value != unexpected_value) return true;
  add_failure(_sf_test_failures, file, line, "expected %s to NOT equal %s",
      expression_value_description(actual_expression, "%li", actual_value),
      expression_value_description(unexpected_expression, "%li", unexpected_value));
  return false;
}


bool
sf_assert_not_null(char const *file, int line, char const *expression, void const *actual, sf_list_t *_sf_test_failures)
{
  if (actual != NULL) return true;  
  add_failure(_sf_test_failures, file, line, "expected (%s) to be non-NULL", expression);
  return false;
}


bool
sf_assert_null(char const *file, int line, char const *expression, void const *actual, sf_list_t *_sf_test_failures)
{
  if (actual == NULL) return true;
  add_failure(_sf_test_failures, file, line, "expected (%s) to be NULL but was (%p)", expression, actual);
  return false;
}


bool
sf_assert_ptr_equals(char const *file, int line, char const *actual_expression, void const *actual_value, char const *expected_expression, void const *expected_value, sf_list_t *_sf_test_failures)
{
  if (actual_value == expected_value) return true;
  add_failure(_sf_test_failures, file, line, "expected %s to equal %s",
              expression_value_description(actual_expression, "%p", actual_value),
              expression_value_description(expected_expression, "%p", expected_value));
  return false;
}


bool
sf_assert_ptr_not_equals(char const *file, int line, char const *actual_expression, void const *actual_value, char const *expected_expression, void const *expected_value, sf_list_t *_sf_test_failures)
{
  if (actual_value != expected_value) return true;
  add_failure(_sf_test_failures, file, line, "expected %s to not equal %s",
              expression_value_description(actual_expression, "%p", actual_value),
              expression_value_description(expected_expression, "%p", expected_value));
  return false;
}


bool
sf_assert_size_t_equals(char const *file, int line, char const *actual_expression, size_t actual_value, char const *expected_expression, size_t expected_value, sf_list_t *_sf_test_failures)
{
  if (actual_value == expected_value) return true;
  add_failure(_sf_test_failures, file, line, "expected %s to equal %s",
      expression_value_description(actual_expression, "%zi", actual_value),
      expression_value_description(expected_expression, "%zi", expected_value));
  return false;
}


bool
sf_assert_size_t_not_equals(char const *file, int line, char const *actual_expression, size_t actual_value, char const *unexpected_expression, size_t unexpected_value, sf_list_t *_sf_test_failures)
{
  if (actual_value != unexpected_value) return true;
  add_failure(_sf_test_failures, file, line, "expected %s to NOT equal %s",
      expression_value_description(actual_expression, "%zi", actual_value),
      expression_value_description(unexpected_expression, "%zi", unexpected_value));
  return false;
}
