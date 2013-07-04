#include "sf_temp_pool.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sf_memory.h"
#include "sf_object.h"


struct temp_pool;


static int max_depth;
static int max_item_count;
static int max_total_item_count;
static struct temp_pool *temp_pools;


static void
add_node(struct temp_pool *temp_pool);

static void
report(void);


struct node
{
  struct node *next;
  int count;
  int max;
  sf_any_t items[];
};

struct temp_pool
{
  struct temp_pool *next;
  struct node *nodes;
  int depth;
  int item_count;
  int total_item_count;
};


void
_sf_temp_pool_init(void)
{
  sf_temp_pool();
}


void
_sf_temp_pool_fin(void)
{
  sf_temp_pool_release();
  report();
}


static void
add_node(struct temp_pool *temp_pool)
{
  size_t size = sysconf(_SC_PAGE_SIZE);
  struct node *node = sf_calloc(1, size);
  if (not node) {
    fprintf(stderr, "ERROR: unable to extend temp pool\n");
    exit(EXIT_FAILURE);
  }
  
  node->next = temp_pool->nodes;
  node->max = (int) ((size - sizeof(struct node)) / sizeof(sf_any_t));
  
  temp_pool->nodes = node;
}


static void
report(void)
{
#ifdef SF_TEMP_POOL_LOG
  fprintf(stdout, "\nsf_temp_pool:\n");
  fprintf(stdout, "  max temp pool count: %i\n", max_depth);
  fprintf(stdout, "  max object count per pool: %i\n", max_item_count);
  fprintf(stdout, "  max total object count: %i\n", max_total_item_count);
#endif
}


sf_any_t
sf_copy_to_temp_pool(sf_any_t any)
{
  return sf_move_to_temp_pool(sf_retain(any));
}


sf_any_t
sf_move_to_temp_pool(sf_any_t any)
{
  if (not any) return any;
  
  if (temp_pools->nodes->max == temp_pools->nodes->count) add_node(temp_pools);
  temp_pools->nodes->items[temp_pools->nodes->count] = any;
  ++temp_pools->nodes->count;
  
  ++temp_pools->item_count;
  ++temp_pools->total_item_count;
  
  if (temp_pools->item_count > max_item_count) max_item_count = temp_pools->item_count;
  if (temp_pools->total_item_count > max_total_item_count) max_total_item_count = temp_pools->total_item_count;
  
  return any;
}


void
sf_temp_pool(void)
{
  struct temp_pool *temp_pool = sf_calloc(1, sizeof(struct temp_pool));
  if (not temp_pool) {
    fprintf(stderr, "ERROR: unable to create new temp pool\n");
    exit(EXIT_FAILURE);
  }
  
  if (temp_pools) {
    temp_pool->depth = temp_pools->depth + 1;
    temp_pool->total_item_count = temp_pools->total_item_count;
    temp_pool->next = temp_pools;
  }
  
  add_node(temp_pool);
  if (temp_pool->depth > max_depth) max_depth = temp_pool->depth;
  
  temp_pools = temp_pool;
}


void
sf_temp_pool_release(void)
{
  assert(temp_pools);
  
  struct temp_pool *temp_pool = temp_pools;
  temp_pools = temp_pool->next;
  
  struct node *node = temp_pool->nodes;
  while (node) {
    struct node *next = node->next;
    
    for (int i = 0; i < node->count; ++i) {
      sf_any_t item = node->items[i];
      sf_release(item);
    }
    
    sf_free(node);
    node = next;
  }
  
  sf_free(temp_pool);
}
