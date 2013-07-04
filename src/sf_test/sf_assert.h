#ifndef SF_TEST_SF_ASSERT_H_INCLUDED
#define SF_TEST_SF_ASSERT_H_INCLUDED


#include <sf_test/sf_test_defs.h>


#define SF_ASSERT(EXPRESSION) \
    if (not sf_assert_bool(__FILE__, __LINE__, #EXPRESSION, !!(EXPRESSION), true, _sf_test_failures)) return

#define SF_ASSERT_C_STR_EQ(ACTUAL, EXPECTED) \
    if (not sf_assert_c_string_equals(__FILE__, __LINE__, #ACTUAL, (ACTUAL), #EXPECTED, (EXPECTED), _sf_test_failures)) return

#define SF_ASSERT_C_STR_NOT_EQ(ACTUAL, EXPECTED) \
    if (not sf_assert_c_string_not_equals(__FILE__, __LINE__, #ACTUAL, (ACTUAL), #EXPECTED, (EXPECTED), _sf_test_failures)) return

#define SF_ASSERT_FALSE(EXPRESSION) \
    if (not sf_assert_bool(__FILE__, __LINE__, #EXPRESSION, !!(EXPRESSION), false, _sf_test_failures)) return

#define SF_ASSERT_INT_EQ(ACTUAL, EXPECTED) \
    if (not sf_assert_int_equals(__FILE__, __LINE__, #ACTUAL, (ACTUAL), #EXPECTED, (EXPECTED), _sf_test_failures)) return

#define SF_ASSERT_INT_NOT_EQ(ACTUAL, EXPECTED) \
    if (not sf_assert_int_not_equals(__FILE__, __LINE__, #ACTUAL, (ACTUAL), #EXPECTED, (EXPECTED), _sf_test_failures)) return

#define SF_ASSERT_IS_EQ(ACTUAL, EXPECTED) \
    if (not sf_assert_is_equal(__FILE__, __LINE__, #ACTUAL, (ACTUAL), #EXPECTED, (EXPECTED), _sf_test_failures)) return

#define SF_ASSERT_IS_NOT_EQ(ACTUAL, EXPECTED) \
    if (not sf_assert_is_not_equal(__FILE__, __LINE__, #ACTUAL, (ACTUAL), #EXPECTED, (EXPECTED), _sf_test_failures)) return

#define SF_ASSERT_LONG_EQ(ACTUAL, EXPECTED) \
    if (not sf_assert_long_equals(__FILE__, __LINE__, #ACTUAL, (ACTUAL), #EXPECTED, (EXPECTED), _sf_test_failures)) return

#define SF_ASSERT_LONG_NOT_EQ(ACTUAL, EXPECTED) \
    if (not sf_assert_long_not_equals(__FILE__, __LINE__, #ACTUAL, (ACTUAL), #EXPECTED, (EXPECTED), _sf_test_failures)) return

#define SF_ASSERT_NOT_NULL(EXPRESSION) \
    if (not sf_assert_not_null(__FILE__, __LINE__, #EXPRESSION, (EXPRESSION), _sf_test_failures)) return

#define SF_ASSERT_NULL(EXPRESSION) \
    if (not sf_assert_null(__FILE__, __LINE__, #EXPRESSION, (EXPRESSION), _sf_test_failures)) return

#define SF_ASSERT_PTR_EQ(ACTUAL, EXPECTED) \
    if (not sf_assert_ptr_equals(__FILE__, __LINE__, #ACTUAL, (ACTUAL), #EXPECTED, (EXPECTED), _sf_test_failures)) return

#define SF_ASSERT_PTR_NOT_EQ(ACTUAL, EXPECTED) \
    if (not sf_assert_ptr_not_equals(__FILE__, __LINE__, #ACTUAL, (ACTUAL), #EXPECTED, (EXPECTED), _sf_test_failures)) return

#define SF_ASSERT_SIZE_T_EQ(ACTUAL, EXPECTED) \
    if (not sf_assert_size_t_equals(__FILE__, __LINE__, #ACTUAL, (ACTUAL), #EXPECTED, (EXPECTED), _sf_test_failures)) return

#define SF_ASSERT_SIZE_T_NOT_EQ(ACTUAL, EXPECTED) \
    if (not sf_assert_size_t_not_equals(__FILE__, __LINE__, #ACTUAL, (ACTUAL), #EXPECTED, (EXPECTED), _sf_test_failures)) return

#define SF_ASSERT_TRUE(EXPRESSION) \
    if (not sf_assert_bool(__FILE__, __LINE__, #EXPRESSION, !!(EXPRESSION), true, _sf_test_failures)) return


bool
sf_assert_bool(char const *file, int line, char const *expression, bool actual, bool expected, sf_list_t *_sf_test_failures);

bool
sf_assert_c_string_equals(char const *file, int line, char const *actual_expression, char const *actual_value, char const *expected_expression, char const *expected_value, sf_list_t *_sf_test_failures);

bool
sf_assert_c_string_not_equals(char const *file, int line, char const *actual_expression, char const *actual_value, char const *unexpected_expression, char const *unexpected_value, sf_list_t *_sf_test_failures);

bool
sf_assert_int_equals(char const *file, int line, char const *actual_expression, int actual_value, char const *expected_expression, int expected_value, sf_list_t *_sf_test_failures);

bool
sf_assert_int_not_equals(char const *file, int line, char const *actual_expression, int actual_value, char const *unexpected_expression, int unexpected_value, sf_list_t *_sf_test_failures);

bool
sf_assert_is_equal(char const *file, int line, char const *actual_expression, sf_any_t actual_value, char const *expected_expression, sf_any_t expected_value, sf_list_t *_sf_test_failures);

bool
sf_assert_is_not_equal(char const *file, int line, char const *actual_expression, sf_any_t actual_value, char const *unexpected_expression, sf_any_t unexpected_value, sf_list_t *_sf_test_failures);

bool
sf_assert_long_equals(char const *file, int line, char const *actual_expression, long actual_value, char const *expected_expression, long expected_value, sf_list_t *_sf_test_failures);

bool
sf_assert_long_not_equals(char const *file, int line, char const *actual_expression, long actual_value, char const *unexpected_expression, long unexpected_value, sf_list_t *_sf_test_failures);

bool
sf_assert_not_null(char const *file, int line, char const *expression, void const *actual, sf_list_t *_sf_test_failures);

bool
sf_assert_null(char const *file, int line, char const *expression, void const *actual, sf_list_t *_sf_test_failures);

bool
sf_assert_ptr_equals(char const *file, int line, char const *actual_expression, void const *actual_value, char const *expected_expression, void const *expected_value, sf_list_t *_sf_test_failures);

bool
sf_assert_ptr_not_equals(char const *file, int line, char const *actual_expression, void const *actual_value, char const *expected_expression, void const *expected_value, sf_list_t *_sf_test_failures);

bool
sf_assert_size_t_equals(char const *file, int line, char const *actual_expression, size_t actual_value, char const *expected_expression, size_t expected_value, sf_list_t *_sf_test_failures);

bool
sf_assert_size_t_not_equals(char const *file, int line, char const *actual_expression, size_t actual_value, char const *unexpected_expression, size_t unexpected_value, sf_list_t *_sf_test_failures);


#endif
