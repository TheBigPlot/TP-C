#include <stdlib.h>

#include "../../structs.h"
#include "../../alloc.h"
#include ".res_list.h"
#include ".res_queue.h"


queue* r_init_queue()
{
  queue* q = (queue*)r_malloc(sizeof(queue));
  q->Queue = r_create_list(-42);
  return q;
}


void r_enqueue(queue* q, int elt)
{
  list* elm = r_create_list(elt);
  r_list_push_end(q->Queue, elm);
}

list* r_dequeue(queue* q)
{
  list* poped = r_list_pop_front(q->Queue);
  return poped;
}

int r_isempty(queue* q)
{
  return r_list_is_empty(q->Queue);
}

void r_FreeQueue(queue* q)
{
  if (q == NULL)
    return;

  r_FreeList(q->Queue);
  r_free(q);
}
