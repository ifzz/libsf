#ifndef SF_SF_DEFS_H_INCLUDED
#define SF_SF_DEFS_H_INCLUDED


#include <iso646.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>


#define SF_FORMAT_FUNCTION(FORMAT_POS, PARAMS_POS) \
    __attribute__((format(printf,FORMAT_POS,PARAMS_POS)))

// See http://groups.google.com/group/comp.std.c/browse_thread/thread/77ee8c8f92e4a3fb/346fc464319b1ee5
// for origin of SF_VA_ARGS_COUNT() and related macros.
#define SF_VA_ARGS_COUNT(...) \
    SF_VA_ARGS_SHIFT_COUNT_VALUES(__VA_ARGS__, SF_VA_ARGS_COUNT_VALUES)

#define SF_VA_ARGS_COUNT_VALUES \
                            63, 62, 61, 60, \
    59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
    49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
    39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
    29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
    19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
     9,  8,  7,  6,  5,  4,  3,  2,  1,  0

#define SF_VA_ARGS_SELECT_COUNT_VALUE( \
       _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, _10, \
      _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
      _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
      _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
      _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
      _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, \
      _61, _62, _63, \
        N, ... \
    ) \
      N

#define SF_VA_ARGS_SHIFT_COUNT_VALUES(...) \
    SF_VA_ARGS_SELECT_COUNT_VALUE(__VA_ARGS__)


struct _sf_array;
struct _sf_ensemble;
struct _sf_hash;
struct _sf_int;
struct _sf_list;
struct _sf_long;
struct _sf_object;
struct _sf_pair;
struct _sf_random;
struct _sf_string;
struct _sf_type;


typedef void const *sf_any_t;
typedef struct _sf_array const *sf_array_t;
typedef struct _sf_ensemble const *sf_ensemble_t;
typedef struct _sf_hash const *sf_hash_t;
typedef struct _sf_int const *sf_int_t;
typedef struct _sf_list const *sf_list_t;
typedef struct _sf_long const *sf_long_t;
typedef struct _sf_object const *sf_object_t;
typedef struct _sf_pair const *sf_pair_t;
typedef struct _sf_random const *sf_random_t;
typedef struct _sf_string const *sf_string_t;
typedef struct _sf_type const *sf_type_t;

typedef bool (*sf_act_on)(sf_any_t item, void *context);
typedef sf_any_t (*sf_collect_from)(sf_any_t item, void *context);
typedef bool (*sf_is_included)(sf_any_t item, void *context);

typedef void (*sf_method_dealloc)(sf_any_t self);
typedef sf_string_t (*sf_method_string_from)(sf_any_t self);
typedef bool (*sf_method_is_equal)(sf_any_t self, sf_any_t other);
typedef int (*sf_method_hash_code)(sf_any_t self);
typedef int (*sf_method_count)(sf_any_t self);
typedef bool (*sf_method_each)(sf_any_t self, sf_act_on act_on, void *context);


#endif
