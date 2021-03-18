#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "../../alloc.h"


#include "../../structs.h"
#include ".res_list.h"

void r_list_init(list* l)
{
  
  l->val = -42;
  l->next = NULL;
  
}


list* r_create_list(int nb)
{

  list* l = r_malloc(sizeof(list));
  
  if(l == NULL)
    errx(1,"can't allocate the list");
  
  l->val = nb;
  l->next = NULL;
  return l;

}


int r_list_is_empty(list *l)
{
  //in case of a null list the list is still empty
  if (l == NULL)
    return 1;

  return (l->next == NULL);
}


size_t r_list_len(list *l)
{

  size_t len = 0;
  list* tmp = l;
  while(tmp != NULL)
    {
      len++;
      tmp = tmp->next;
    }
  return len-1;
  
}


list* r_list_get(list* l,size_t n)
{

  size_t i = -1;
  //in case of an empty liste
  if(l == NULL) return NULL;
  list* tmp = l;

  while(tmp != NULL && i < n)
    {
      tmp = tmp->next;
      i++;
    }

  return tmp;

}


void r_list_push_front(list *l, list *elm)
{
  //to avoid some ' segfaults '
  if (l == NULL) return;
  
  elm->next = l->next;
  l->next = elm;
  
}

void r_list_push_end(list *l, list *elm)
{
  if (l == NULL)
    return;
  
  list* tmp = l;

  while (tmp->next != NULL)
    tmp = tmp->next;

  tmp->next = elm;
}


void r_list_insert(list *l, list *elm, size_t n)
{
  if (l == NULL)
    return;
  
  list* tmp = l;
  size_t i = 0;

  while (tmp->next != NULL && i < n)
    {
      i++;
      tmp = tmp->next;
    }

  if (tmp->next != NULL)
    elm->next = tmp->next->next;

  tmp->next = elm;

}
void r_insert_in_sorted_list(list* l, list* elm)
{
  if (l == NULL)
    return;
  
  list* tmp = l;

  while (tmp->next != NULL && tmp->next->val < elm->val)
    tmp = tmp->next;
  
  if (tmp->next != NULL && tmp->next->val == elm->val)
    return;
  
  elm->next = tmp->next;
  tmp->next = elm;
}



list * r_list_pop_front(list *l)
{
  if(l != NULL && l->next != NULL)
    {
      list* el = l->next;
      l->next = l->next->next;
      return el;
    }
  
  return NULL;

}
list* r_list_remove(list* l, size_t n)
{
  if (l == NULL)
    return NULL;
  
  list* tmp = l;
  size_t i = 0;
  
  while (tmp->next != NULL && i < n)
    tmp = tmp->next;
  
  if (tmp->next == NULL)
    return NULL;
  
  list* elm = tmp->next;
  tmp->next = elm->next;
  return elm;
}


list* r_list_search(list* l, int val)
{

  list* tmp = l->next;
  while (tmp != NULL && tmp->val != val)
    tmp = tmp->next;
  
  return tmp;
}


list* r_list_binary_search(list* l, int val)
{
  size_t len = r_list_len(l);
  size_t j = len-1;
  size_t i = 0;
  while (i<j)
    {
      size_t mid = i+ ((i+j)/2);
      list* val_mid = r_list_get(l,mid);
      if (val_mid == NULL)
	return NULL;

      if (val == val_mid->val)
	return val_mid;
      
      if(val < val_mid->val)
	j = mid-1;
      
      else
	i = mid+1;
    }
  return NULL;
}


void r_FreeList(list* l)
{
  list* tmp = NULL;
  while(l != NULL)
    {
      tmp = l;
      l = l->next;
      r_free(tmp);
    }
}

