#include "sf_stdio_test_monitor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sf/sf_collection.h>
#include <sf/sf_list.h>
#include <sf/sf_object.h>
#include <sf/sf_pair.h>
#include <sf/sf_string.h>
#include "sf_test_case.h"
#include "sf_test_failure.h"
#include "sf_test_monitor.h"
#include "sf_test_time.h"


#define ESC "\033"
#define NORMAL "0"
#define BOLD "1"
#define BLACK "30"
#define WHITE "37"
#define ON_RED "41"
#define ON_GREEN "42"

#define MICRO_SIGN "\xc2\xb5"


struct statistics
{
  int test_case_count;
  int failed_test_case_count;
  sf_test_time_t test_sequence_start_time;
};

struct test_monitor_context
{
  struct sf_stdio_test_monitor_options options;
  struct statistics statistics;
};


static bool
is_a_terminal(FILE *file);

static void
test_case_did_stop(sf_test_time_t test_time, sf_test_case_t test_case, sf_list_t test_suites, sf_list_t test_failures, void *context);

static bool
print_each_test_failure(sf_any_t item, void *context);

static void
test_sequence_did_stop(sf_test_time_t test_time, sf_test_sequence_t test_sequence, void *context);

static void
test_sequence_will_start(sf_test_time_t test_time, sf_test_sequence_t test_sequence, void *context);

static void
test_case_will_start(sf_test_time_t test_time, sf_test_case_t test_case, sf_list_t test_suites, void *context);


static struct test_monitor_context test_monitor_context;

static struct sf_test_monitor stdio_test_monitor = {
  .context = &test_monitor_context,
  .test_sequence_will_start = test_sequence_will_start,
  .test_case_will_start = test_case_will_start,
  .test_case_did_stop = test_case_did_stop,
  .test_sequence_did_stop = test_sequence_did_stop,
};


struct sf_test_monitor *
sf_stdio_test_monitor(void)
{
  struct sf_stdio_test_monitor_options options = {
    .test_case_output = sf_stdio_test_monitor_test_case_output_default,
  };
  return sf_stdio_test_monitor_from_options(&options);
}


int
sf_stdio_test_monitor_failed_test_case_count(struct sf_test_monitor *test_monitor)
{
  struct test_monitor_context *test_monitor_context = test_monitor->context;
  struct statistics *statistics = &test_monitor_context->statistics;
  return statistics->failed_test_case_count;
}


struct sf_test_monitor *
sf_stdio_test_monitor_from_options(struct sf_stdio_test_monitor_options const *options)
{
  memcpy(&test_monitor_context.options, options, sizeof(struct sf_stdio_test_monitor_options));
  memset(&test_monitor_context.statistics, 0, sizeof(struct statistics));
  return &stdio_test_monitor;
}


static void
test_case_did_stop(sf_test_time_t test_time, sf_test_case_t test_case, sf_list_t test_suites, sf_list_t test_failures, void *context)
{
  struct test_monitor_context *test_monitor_context = context;
  struct sf_stdio_test_monitor_options *options = &test_monitor_context->options;
  struct statistics *statistics = &test_monitor_context->statistics;
  
  ++statistics->test_case_count;
  if (sf_count(test_failures)) {
    ++statistics->failed_test_case_count;
    if (sf_stdio_test_monitor_test_case_output_brief == options->test_case_output) {
      fprintf(stdout, "\n");
      fflush(stdout);
    }
    sf_pair_t pair = sf_pair(test_case, test_suites);
    sf_each(test_failures, print_each_test_failure, (void *) pair);
    if (sf_stdio_test_monitor_test_case_output_full == options->test_case_output) {
      fprintf(stdout, "\n");
      fflush(stdout);
    }
  }
}


static bool
print_each_test_failure(sf_any_t item, void *context)
{
  sf_test_failure_t test_failure = item;
  sf_string_t file = sf_test_failure_file(test_failure);
  int line = sf_test_failure_line(test_failure);
  
  sf_pair_t pair = context;
  sf_test_case_t test_case = sf_pair_left(pair);
  sf_list_t test_suites = sf_pair_right(pair);
  sf_list_t test_suites_reversed = sf_list_reversed(test_suites);
  sf_string_t test_suites_string = sf_string_from_suffix_and_collection(sf_string("."), test_suites_reversed);
  
  char const *identifier_prefix = "";
  char const *identifier_suffix = "";
  if (is_a_terminal(stderr)) {
    identifier_prefix = ESC "[" BOLD ";" WHITE ";" ON_RED "m";
    identifier_suffix = ESC "[" NORMAL "m";
  }
  
  sf_string_t failure_description = sf_test_failure_description(test_failure);
  fprintf(stderr, "%s:%d: \\\n  %s%s%s%s: \\\n    %s\n",
          sf_c_string_from(file), line,
          sf_c_string_from(test_suites_string),
          identifier_prefix, sf_c_string_from(sf_test_case_identifier(test_case)), identifier_suffix,
          sf_c_string_from(failure_description));
  fflush(stderr);
  return true;
}


static bool
is_a_terminal(FILE *file)
{
  int file_descriptor = fileno(file);
  return isatty(file_descriptor) && getenv("TERM");
}


static void
test_sequence_did_stop(sf_test_time_t test_time, sf_test_sequence_t test_sequence, void *context)
{
  struct test_monitor_context *test_monitor_context = context;
  struct sf_stdio_test_monitor_options *options = &test_monitor_context->options;
  struct statistics *statistics = &test_monitor_context->statistics;
  
  if (sf_stdio_test_monitor_test_case_output_none != options->test_case_output) {    
    fprintf(stdout, "\n");
    fflush(stdout);
  }
  
  char const *format = "%Y-%m-%d %H:%M:%S";
  char timestamp[2 * sizeof format];
  time_t time = sf_test_time_value(test_time);
  size_t charsStored = strftime(timestamp, sizeof timestamp, format, localtime(&time));
  if ( ! charsStored) timestamp[0] = '\0';
  
  FILE *out = NULL;
  char const *prefix = "";
  char const *suffix = "";
  sf_string_t message = NULL;
  if (statistics->failed_test_case_count) {
    out = stderr;
    if (is_a_terminal(out)) {
      prefix = ESC "[" BOLD ";" WHITE ";" ON_RED "m" "[ ";
      suffix = " ]" ESC "[" NORMAL "m";
    } else {
      prefix = "[*** ";
      suffix = " ***]";
    }
    message = sf_string_from_format("%i FAILED", statistics->failed_test_case_count);
  } else {
    out = stdout;
    if (is_a_terminal(out)) {
      prefix = ESC "[" BOLD ";" BLACK ";" ON_GREEN "m ";
      suffix = " " ESC "[" NORMAL "m";
    }
    message = sf_string("PASSED");
  }
  
  double elapsed_time = sf_test_time_elapsed_seconds(statistics->test_sequence_start_time, test_time);
  char const *elapsed_time_unit = "sec";
  if (elapsed_time < 0.001 /*sec*/) {
    elapsed_time *= 1000000.0;
    elapsed_time_unit = MICRO_SIGN "sec";
  } else if (elapsed_time < 1.0 /*sec*/) {
    elapsed_time *= 1000.0;
    elapsed_time_unit = "msec";
  } else if (elapsed_time > 60.0 /*sec*/) {
    elapsed_time /= 60.0;
    elapsed_time_unit = "min";
  }
  
  char const *plural = (1 == statistics->test_case_count) ? "" : "s";
  fprintf(out, "%s %s%s%s %i test%s in %0.1f %s\n",
          timestamp, prefix, sf_c_string_from(message), suffix, statistics->test_case_count,
          plural, elapsed_time, elapsed_time_unit);
  fflush(out);
  
  sf_release(statistics->test_sequence_start_time);
}


static void
test_sequence_will_start(sf_test_time_t test_time, sf_test_sequence_t test_sequence, void *context)
{
  struct test_monitor_context *test_monitor_context = context;
  struct statistics *statistics = &test_monitor_context->statistics;
  
  statistics->test_case_count = 0;
  statistics->failed_test_case_count = 0;
  statistics->test_sequence_start_time = sf_retain(test_time);
}


static void
test_case_will_start(sf_test_time_t test_time, sf_test_case_t test_case, sf_list_t test_suites, void *context)
{
  struct test_monitor_context *test_monitor_context = context;
  struct sf_stdio_test_monitor_options *options = &test_monitor_context->options;
  struct statistics *statistics = &test_monitor_context->statistics;
  
  switch (options->test_case_output) {
    case sf_stdio_test_monitor_test_case_output_brief:
      fprintf(stdout, ".");
      fflush(stdout);
      break;
    case sf_stdio_test_monitor_test_case_output_full:
      {
        sf_list_t test_suites_reversed = sf_list_reversed(test_suites);
        sf_string_t test_suites_string = sf_string_from_suffix_and_collection(sf_string("."), test_suites_reversed);
        fprintf(stdout, "%5i) %s%s\n", (statistics->test_case_count + 1),
                sf_c_string_from(test_suites_string), sf_c_string_from(sf_test_case_identifier(test_case)));
        fflush(stdout);
      }
      break;
    default:
      break;
  }
}
