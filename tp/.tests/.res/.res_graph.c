#include <stdlib.h>
#include <stdio.h>
#include <err.h>

#include ".res_graph.h"
#include "../../structs.h"
#include "../../alloc.h"
#include ".res_list.h"
#include ".res_queue.h"

graph* r_init_graph(int order, int is_directed)
{
  graph* g = r_malloc(sizeof(graph));
  g->order = order;
  g->is_directed = is_directed;
  g->adjlists = (list**)r_malloc(order*sizeof(list*));

  for (int i = 0; i<order; i++)
    g->adjlists[i] = r_create_list(-42);

  return g;
}


void r_add_edge(graph* G, int src, int dst)
{
  //it creates an element with dst
  if (0 <= src && src < G->order && 0<= dst && dst < G->order)
    {
      list* elm_dst = r_create_list(dst);
      r_insert_in_sorted_list(G->adjlists[src],elm_dst);
      
      //if not directed has to insert src the dst list
      if (G->is_directed == 0)
	{
	  list* elm_src = r_create_list(src);
	  r_insert_in_sorted_list(G->adjlists[dst],elm_src);
	}
    }
}

void r_add_vertice(graph* G)
{
  G->order += 1;
  G->adjlists = realloc(G->adjlists,G->order*sizeof(list*));
  G->adjlists[(G->order)-1] = r_create_list(-42);
}
void backedges_dfs_rec(graph* G, int* M, int src, int dad)
{
  M[src] = 1;
  list* tmp = G->adjlists[src]->next;
  while (tmp != NULL)
    {
      int y = tmp->val;

      if(M[y] == 0)
	backedges_dfs_rec(G,M,y,src);

      else if(y != dad)
	printf("%d --> %d\n",src,y);
      tmp = tmp->next;
    }
}


void r_backedges_dfs(graph* G)
{
  if (G == NULL)
    errx(1,"graph null");
  
  if (G->is_directed)
    {
      printf("only work for undirected graph\n");
      return;
    }
  
  int* M = r_malloc(G->order*sizeof(int));

  for (int i = 0; i < G->order; i++)
    M[i] = 0;

  for (int i = 0; i < G->order; i++)
    if (M[i] == 0)
      backedges_dfs_rec(G,M,i,-1);

  r_free(M);
}


void __components_dfs(graph* G, int* M, int src)
{
  M[src] = 1;
  list* tmp = G->adjlists[src]->next;
  while (tmp != NULL)
    {
      if (M[tmp->val] == 0)
	__components_dfs(G,M,tmp->val);
      tmp = tmp->next;
    }
}


int r_components_dfs(graph* G)
{
  if (G == NULL)
    errx(1,"graph null");
  
  int* M = r_malloc(G->order*sizeof(int));

  for (int i = 0; i < G->order; i++)
    M[i] = 0;

  int res = 0;
  for (int i = 0; i < G->order; i++)
    if(M[i] == 0)
      {
	res++;
	__components_dfs(G,M,i);
      }
  
  r_free(M);
  return res;
}

void __components_bfs(graph* G, int* M, int src)
{
  M[src] = 1;
  queue* q = r_init_queue();
  r_enqueue(q,src);
  
  while (r_isempty(q) == 0)
    {
      list* poped = r_dequeue(q);
      list* tmp = G->adjlists[poped->val]->next;
      while (tmp != NULL)
	{
	  if (M[tmp->val] == 0)
	    {
	      M[tmp->val] = 1;
	      r_enqueue(q,tmp->val);
	    }
	  tmp = tmp->next;
	}
      r_free(poped);
    }
  r_FreeQueue(q);
}

int r_components_bfs(graph* G)
{
  if (G == NULL)
    errx(1,"graph null");
  int* M = r_malloc(G->order*sizeof(int));

  for (int i = 0; i < G->order; i++)
    M[i] = 0;

  int res = 0;

  for(int i = 0; i < G->order; i++)
    if(M[i] == 0)
      {
	res++;
	__components_bfs(G,M,i);
      }
  
  r_free(M);
  return res;
}



int __path(graph* G, int src, int dst, int* M)
{
  queue* q = r_init_queue();
  r_enqueue(q,src);
  
  while (r_isempty(q) == 0)
    {
      list* poped = r_dequeue(q);

      if(poped->val == dst)
	return 1;
      list* tmp = G->adjlists[poped->val]->next;

      while (tmp != NULL)
	{
	  if(M[tmp->val] == -1)
	    {
	      M[tmp->val] = src;
	      r_enqueue(q,tmp->val);
	    }
	  tmp = tmp->next;
	}
      r_free(poped);
    }
  r_FreeQueue(q);
  return 0;
}

list* r_path(graph* G, int src, int dst)
{
  if (G == NULL)
    errx(1,"graph null");
  int* M = r_malloc(G->order*sizeof(int));

  for (int i = 0; i < G->order; i++)
    M[i] = -1;

  list* path = r_create_list(-42);
  int b = __path(G,src,dst,M);

  if(b)
    {
      while (dst != src)
	{
	  list* elm = r_create_list(dst);
	  r_list_push_front(path,elm);
	  dst = M[dst];
	}

      list* elm_start = r_create_list(src);
      r_list_push_front(path,elm_start);
    }
  
  r_free(M);
  return path;
}

int r_eccentricity(graph* G, int x)
{
  if (G == NULL)
    errx(1,"graph null");

  int* M = r_malloc(G->order*sizeof(int));
  int res;

  for (int i = 0; i < G->order; i++)
    M[i] = -1;

  M[x] = 0;
  queue* q = r_init_queue();
  r_enqueue(q,x);
  while (r_isempty(q) == 0)
    {
      list* poped = r_dequeue(q);
      x = poped->val;
      list* tmp = G->adjlists[poped->val]->next;
      while (tmp != NULL)
	{
	  if (M[tmp->val] == -1)
	    {
	      M[tmp->val] = M[x]+1;
	      r_enqueue(q,tmp->val);
	    }
	  tmp = tmp->next;
	}
      r_free(poped);
    }
  res = M[x];
  r_free(M);
  r_FreeQueue(q);
  return res;
}
  
list* r_center(graph* G)
{
  if(G == NULL)
    errx(1,"graph null");

  list* res = r_create_list(-42);
  list* elm = r_create_list(0);
  
  r_list_push_end(res,elm);
  int min = r_eccentricity(G,0);
  
  for (int i = 1; i< G->order; i++)
    {
      int tmp = r_eccentricity(G,i);
      list* tmp_elm = r_create_list(i);
      
      if(tmp < min)
	{
	  min = tmp;
	  r_FreeList(res);
	  res = r_create_list(-42);
	  r_list_push_end(res,tmp_elm);
	}
      
      else if (tmp == min)
	r_list_push_end(res,tmp_elm);
    }
  return res;
      
}

void r_FreeGraph(graph* g)
{
  for(int i = 0; i < g->order; i++)
    {
      r_FreeList(g->adjlists[i]);
    }
  r_free(g->adjlists);
  r_free(g);
}
