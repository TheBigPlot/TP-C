#include <stdio.h>
#include <stdlib.h>
#include ".tools.h"
#include ".res/.res_list.h"
#include ".res/.res_graph.h"
#include "../graphs/graph.h"
#include ".tests_graphs.h"
#include ".unitTest/.unitTest.h"
#include "../structs.h"
#include "../alloc.h"


extern size_t all_alloc;
extern size_t all_free;
extern size_t all_realloc;

void test_init_graph(char* name, int nb_tests)
{
  graph* g = init_graph(nb_tests,0);
  
  if (g != NULL)
    {
      comp_bool(name,1,g->order == nb_tests && g->is_directed == 0 && g->adjlists != NULL,"");
      r_FreeGraph(g);
    }
  
  else
    comp_bool(name,1,0,"");
}

void test_add_edge(char* name, int nb_tests)
{
  graph* g1 = r_init_graph(nb_tests,0);
  graph* g2 = r_init_graph(nb_tests,1);

  add_edge(g1, 0, nb_tests-1);
  add_edge(g1, 0, nb_tests-1);

  //some search to verify is the elements have been well add
  list* dst1 = r_list_search(g1->adjlists[0], nb_tests-1);
  list* src1 = r_list_search(g1->adjlists[nb_tests-1], 0);
  
  list* dst2 = r_list_search(g2->adjlists[0], nb_tests-1);
  list* src2 = r_list_search(g2->adjlists[nb_tests-1], 0);

  //in case the code is still not implemented
  if (dst2 == NULL)
    comp_bool(name,1,0,"");
  
  else
    comp_bool(name,1,dst2->val == nb_tests-1 && src2 == NULL,"");

  if (dst1 == NULL || src1 == NULL)
    comp_bool(name,1,0,"");

  else
    comp_bool(name,1,dst1->val == nb_tests-1 && src1->val == 0,"");

  r_FreeGraph(g1);
  r_FreeGraph(g2);
}

void test_add_vertice(char* name, int nb_tests)
{
  graph* g = r_init_graph(nb_tests,0);
  add_vertice(g);
  comp_bool(name,1,g->order == nb_tests+1 && all_realloc == 1,"");
  r_FreeGraph(g);
}

void test_backedges_dfs(char* name, int nb_tests)
{
  printf("%s:\n",name);
  for (int i = 0; i < nb_tests; i++)
    {
      graph* g = generate_full_graph((nb_tests/3)+i, 0);
      
      printf("expected:\n");
      r_backedges_dfs(g);
      printf("\ngot:\n");
      backedges_dfs(g);
      
      r_FreeGraph(g);

      if (i != nb_tests-1)
	printf("--------------------\n");

      printf("\n");
    }
}
  
void test_components_dfs(char* name, int nb_tests)
{
  for(int i = 0; i < nb_tests; i++){
    graph* g = generate_full_graph(nb_tests*(i+1), 0);
    int expected = r_components_dfs(g);
    int got = components_dfs(g);
    comp_size_t(name,expected,got,"");
    r_FreeGraph(g);
  }
}
  
void test_components_bfs(char* name, int nb_tests)
{
  for(int i = 0; i < nb_tests; i++)
    {
      graph* g = generate_full_graph(nb_tests*(i+1), 0);

      int expected = r_components_bfs(g);
      int got = components_bfs(g);

      comp_size_t(name,expected,got,"");
      r_FreeGraph(g);
    }
}
void test_path(char* name, int nb_tests)
{
  for (int i = 0; i < nb_tests; i++)
    {
      graph* g = generate_full_graph(nb_tests*(i+3), 0);

      int src = rand()%(nb_tests*(i+3));
      int dst = rand()%(nb_tests*(i+3));			

      list* expected = r_path(g,src,dst);
      list* got = path(g,src,dst);

      comp_full_list(name,expected,got,"");
      r_FreeList(expected);

      if (got != NULL)
	r_FreeList(got);
      
      r_FreeGraph(g);
  }
}

void test_eccentricity(char* name, int nb_tests)
{
  for (int i = 0; i < nb_tests; i++)
    {
      graph* g = generate_full_graph(nb_tests*(i+3), 0);
      int src = rand()%(nb_tests*(i+3));
      int expected = r_eccentricity(g,src);
      int got = eccentricity(g,src);
      comp_size_t(name,expected,got,"");
      r_FreeGraph(g);
    }
}

void test_center(char* name, int nb_tests)
{
  for (int i = 0; i < nb_tests; i++)
    {
      graph* g = generate_full_graph(nb_tests*(i+3), 0);
      
      list* expected = r_center(g);
      list* got = center(g);
      
      comp_full_list(name,expected,got,"");
      r_FreeList(expected);
      
      if(got != NULL)
	r_FreeList(got);
      
      r_FreeGraph(g);
    }
}

void test_FreeGraph(char* name, int nb_tests)
{
  graph* g = r_init_graph(nb_tests,0);
  for (int i = 0; i < nb_tests; i++)
    {
      g->adjlists[i] = make_list(nb_tests);
    }
  FreeGraph(g);
  comp_size_t(name,nb_tests*(nb_tests+1)+1,all_free,"");

}


void all_graphs_tests(int nb_tests)
{
  Func funcs[] =
    {
     test_init_graph,
     test_add_edge,
     test_add_vertice,
     test_backedges_dfs,
     test_components_dfs,
     test_components_bfs,
     test_path,
     test_eccentricity,
     test_center,
     test_FreeGraph
    };
  char* names[] =
    {
     "test_init_graph",
     "test_add_edge",
     "test_add_vertice",
     "test_backedges_dfs",
     "test_components_dfs",
     "test_components_bfs",
     "test_path",
     "test_eccentricity",
     "test_center",
     "test_FreeGraph"
    };
  CallFile("GRAPHS TESTS:",funcs,names,8,nb_tests);
}
