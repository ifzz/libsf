#ifndef SF_TEST_SF_TEST_DEFS_H_INCLUDED
#define SF_TEST_SF_TEST_DEFS_H_INCLUDED


#include <sf/sf_defs.h>


struct _sf_test_case;
struct _sf_test_failure;
struct _sf_test_sequence;
struct _sf_test_suite;
struct _sf_test_time;

struct sf_test_item;
struct sf_test_monitor;


typedef struct _sf_test_case const *sf_test_case_t;
typedef struct _sf_test_failure const *sf_test_failure_t;
typedef struct _sf_test_sequence const *sf_test_sequence_t;
typedef struct _sf_test_suite const *sf_test_suite_t;
typedef struct _sf_test_time const *sf_test_time_t;


#endif
