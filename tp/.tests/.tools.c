#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <time.h>

#include ".tools.h"
#include "../structs.h"
#include "../alloc.h"
#include ".res/.res_list.h"
#include ".res/.res_queue.h"
#include ".res/.res_graph.h"

#define MAX 10000

//array tools

void printArr(int* arr, size_t len)
{
  printf("[");
  //traverse all the elements to display them 
  for (size_t i = 0; i<len ; i++)
    {
      printf("%d",arr[i]);
      if (i < len-1)
	printf(", ");
    }
  printf("]\n");
}

//create and return a copy of the array src
int* copy_array(int* src, size_t len)
{
  int* copy = r_malloc(len*sizeof(int));

  for (size_t i = 0; i < len; i++)
    copy[i] = src[i];
  
  return copy;
}


//compare to arrays with the same len
int array_equals(int* a, int* b, int len)
{
  for(int i = 0; i < len; i++)
    if(a[i] != b[i])
      return 0;
  
  return 1;
}

//generate a array of length n with random values
int* generate_int_array(int n)
{
  int* arr = r_malloc(n*sizeof(int));
  if (arr == NULL)
    errx(1,"allocation error generateArray");

  for (int i = 0; i < n; i++)
    {
      int nb = rand()%MAX;
      arr[i] = nb;
    }
  
  return arr;
}


void insert_sort(int arr[], int n)
{
  int i, key, j;
  for (i = 1; i < n; i++)
    {
      key = arr[i];
      j = i - 1;
      
      /* Move elements of arr[0..i-1], that are
	 greater than key, to one position ahead
	 of their current position */
      while (j >= 0 && arr[j] > key)
	{
	  arr[j + 1] = arr[j];
	  j = j - 1;
	}
      
      arr[j + 1] = key;
    }
}


//list tools
//generate a list of length n with random values 
list* make_list(int n)
{
  list* l = r_create_list(-42);
  list* tmp = l;
  for (int i = 0; i<n; i++)
    {
      tmp->next = r_create_list(rand()%MAX);
      tmp = tmp->next;
    }
  return l;
}


list* copy_list(list* l)
{
  list* copy = make_list(0);
  list* tmp = l->next;
  while (tmp != NULL)
    {
      list* elm = r_create_list(tmp->val);
      r_list_push_end(copy,elm);
      tmp = tmp->next;
    }
  return copy;
}

list* list_from_array(int* arr, int len)
{
  list* l = make_list(0);
  for (int i = 0; i < len; i++)
    {
      list* elm = r_create_list(arr[i]);
      r_list_push_end(l,elm);
    }
  return l;
}

void printList(list* l)
{
  printf("{ ");
  if (l != NULL)
    {
      list* tmp = l->next;
      while (tmp != NULL)
	{
	  printf("%d",tmp->val);
	  if (tmp->next != NULL)
	    printf(", ");
	  
	  tmp = tmp->next;
	}
    }
  printf("}\n");
}




int list_equals(list* l1, list* l2)
{
  list* tmp1 = l1;
  list* tmp2 = l2;
  while (tmp1 != NULL && tmp2 != NULL && tmp1->val == tmp2->val)
    {
      tmp1 = tmp1->next;
      tmp2 = tmp2->next;
    }
  return tmp1 == tmp2;
}

//graph tools


graph* generate_full_graph(int order, int is_directed)
{
  //initialise a graph with order and is_directed
  graph* g = r_init_graph(order,is_directed);
  for (int i = 0; i< order; i++)
    {
      //for each vertices add nb edges
      int nb = rand() % (order < 2 ? 1: (2*order/3));
      for (int j = 0; j < nb ; j++)
	{
	  int dst = rand() % order;
	  r_add_edge(g, i, dst);
	}
    }
  return g;
}


void todot(graph* G){
  char* link;
  if (G->is_directed)
    {
      link = " -> ";
      printf("digraph {\n");
    }
  
  else
    {
      link = " -- ";
      printf("graph {\n");
    }
  
  for (int i = 1; i<G->order; i++)
    {
      printf(" %d\n",i);
      list* tmp = G->adjlists[i]->next;
      while (tmp != NULL)
	{
	  if (G->is_directed  || tmp->val <= i)
	    printf("%d%s%d\n",i,link,tmp->val);
	  tmp = tmp->next;
	}
    }
  printf("}\n");
}
 
