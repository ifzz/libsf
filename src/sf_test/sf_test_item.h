#ifndef SF_TEST_SF_TEST_ITEMS_H_INCLUDED
#define SF_TEST_SF_TEST_ITEMS_H_INCLUDED


#include <sf/sf_defs.h>


enum sf_test_item_type
{
  sf_test_item_type_unknown = 0,
  sf_test_item_type_test_case,
  sf_test_item_type_test_suite,
};


struct sf_test_item
{
  enum sf_test_item_type type;
  char const *identifier;
  union {
    void (*test_function)(sf_list_t *_sf_test_failures);
    sf_array_t (*generate_items)(void);
  };
};


sf_any_t
sf_test_item(struct sf_test_item const *test_item);

#define sf_test_items(...) \
        sf_test_items_array((struct sf_test_item const *[]) { __VA_ARGS__ }, SF_VA_ARGS_COUNT(__VA_ARGS__))

sf_array_t
sf_test_items_array(struct sf_test_item const **test_items, int count);


#endif
