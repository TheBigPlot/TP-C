#include <stdio.h>
#include <stdlib.h>
#include ".garbage.h"
#include "../alloc.h"

//generate a single element for adding to "garbage collector"
plist* create_garbage(void* p)
{
  plist* garbage = g_malloc(sizeof(plist));
  garbage->p = p;
  garbage->next = NULL;
  return garbage;
}

//add the elm to the garbage collector l
void garbage_add(plist* l, plist *elm)
{
  //to avoid some ' segfaults '
  if (l == NULL) return;

  //it add at the beginning of the garbage collector
  
  elm->next = l->next;
  l->next = elm;
}

//remove the pointer p from the garbage collector l
plist* garbage_remove(plist* l, void* p)
{
  if (l == NULL)
    return NULL;
  //search an element of the garbage collector which could have the pointer
  //as value
  plist* tmp = l;

  while (tmp->next != NULL && tmp->next->p != p)
    tmp = tmp->next;
  
  if (tmp->next == NULL)
    return NULL;
  
  plist* elm = tmp->next;
  tmp->next = elm->next;
  return elm;
}

//it free all the element of the garbage collector
void garbage_free(plist* l)
{
  plist* tmp = NULL;;
  while (l != NULL)
    {
      tmp = l;
      l = l->next;
      g_free(tmp->p);
      g_free(tmp);
    }
}







  


