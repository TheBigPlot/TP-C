#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <err.h>

#include ".tests_lists.h"
#include "../lists/list.h"
#include ".res/.res_list.h"
#include "../structs.h"
#include "../alloc.h"
#include ".tools.h"
#include ".unitTest/.unitTest.h"

#define MAX 10000

extern size_t all_alloc;
extern size_t all_free;


void test_list_init(char* name,int nb_tests)
{
  //just to use the variable
  nb_tests++;

  //creation of an empty list with a working function
  list* l = r_malloc(sizeof(list));
  //for the tests
  l->val = -84;
  
  list_init(l);

  //list_init() has done nothing
  if (l->val == -84)
    comp_bool(name,1,0,"");
  else
    comp_bool(name,1,(l->val == -42 && l->next == NULL),"");
  r_free(l);
}

void test_create_list(char* name, int nb_tests)
{
  //tests values
  int* arr = generate_int_array(nb_tests);
  for (int i = 0; i<nb_tests; i++)
    {
      //tests lists
      list* l = r_create_list(-42);
      l = create_list(arr[i]);
      
      //in case of nothing done by create_list
      if (l == NULL)
	comp_int(name,arr[i],-42,"");
      else
	comp_int(name,arr[i],l->val,"");

      r_FreeList(l);
    }
  
  r_free(arr);
}

void test_list_is_empty(char* name,int nb_tests)
{
  list* empty_list =  make_list(0);
  list* not_empty_list = make_list(nb_tests);

  //few tests
  comp_bool(name,1,list_is_empty(NULL),"");
  comp_bool(name,1,list_is_empty(empty_list),"");
  comp_bool(name,0,list_is_empty(not_empty_list),"");

  r_FreeList(empty_list);
  r_FreeList(not_empty_list);
}

void test_list_len(char* name, int nb_tests)
{
  //coner cases
  list* empty = make_list(0);
  comp_size_t(name,-1,list_len(NULL),"");
  comp_size_t(name,0,list_len(empty),"");
  r_FreeList(empty);
  
  for (int i = 0; i < nb_tests; i++)
    {
      //calls & tests
      list* l = make_list(rand()%MAX);
      size_t expected = r_list_len(l);
      size_t got = list_len(l);
      comp_size_t(name,expected,got,"");
      
      r_FreeList(l);
    }
}

void test_list_get(char* name, int nb_tests)
{
  list* l  = make_list(nb_tests);

  list* expected_1 = r_list_get(l,-1);
  list* expected_2 = r_list_get(l,nb_tests+5);

  list* got_1 = list_get(l,-1);
  list* got_2 = list_get(l,nb_tests+5);

  comp_list(name,expected_1,got_1,"");
  comp_list(name,expected_2,got_2,"");
  
  for (int i = 0; i < nb_tests; i++)
    {
      list* expected = r_list_get(l,i);
      list* got = list_get(l,i);
      comp_list(name,expected,got,"");
    }
  
  r_FreeList(l);
}

void test_list_push_front(char* name, int nb_tests)
{
  int* vals = generate_int_array(nb_tests);
  list* expected = make_list(0);
  list* got = make_list(0);
  
  //initialise 2 empty lists
  for (int i = 0; i < nb_tests; i++)
    {
      list* elm_exp = r_create_list(vals[i]);
      list* elm_got = r_create_list(vals[i]);
      
      r_list_push_front(expected,elm_exp);
      list_push_front(got,elm_got);
    }
  
  comp_full_list(name,expected,got,"");

  r_FreeList(expected);
  r_FreeList(got);
  r_free(vals);
}

void test_list_push_end(char* name, int nb_tests)
{
  int* vals = generate_int_array(nb_tests);

  // 2 empty list
  list* expected = make_list(0);
  list* got = make_list(0);
  
  for (int i = 0; i < nb_tests; i++)
    {
      list* elm_exp = r_create_list(vals[i]);
      list* elm_got = r_create_list(vals[i]);
      r_list_push_end(expected,elm_exp);
      list_push_end(got,elm_got);
    }
  
  comp_full_list(name,expected,got,"");
  r_FreeList(expected);
  r_FreeList(got);
  r_free(vals);
}



void test_list_insert(char*name, int nb_tests)
{
  int* vals = generate_int_array(nb_tests);
  list* expected = make_list(0);
  list* got = make_list(0);
  
  for (int i = 0; i < nb_tests; i++)
    {
      list* elm_exp = r_create_list(vals[i]);
      list* elm_got = r_create_list(vals[i]);
      
      //a random position to insert the elements
      size_t n = rand()%nb_tests;

      r_list_insert(expected,elm_exp,n);
      list_insert(got,elm_got,n);
    }
  
  //compare the 2 lists created
  comp_full_list(name,expected,got,"");

  r_FreeList(expected);
  r_FreeList(got);
  r_free(vals);
}


void test_insert_in_sorted_list(char* name, int nb_tests)
{
  int* vals = generate_int_array(nb_tests);
  list* expected = make_list(0);
  list* got = make_list(0);
  for(int i = 0; i < nb_tests; i++){
    list* elm_exp = r_create_list(vals[i]);
    list* elm_got = r_create_list(vals[i]);
    r_insert_in_sorted_list(expected,elm_exp);
    insert_in_sorted_list(got,elm_got);
  }
  comp_full_list(name,expected,got,"");
  r_FreeList(expected);
  r_FreeList(got);
  r_free(vals);
}
  

void test_list_pop_front(char* name, int nb_tests)
{
  list* l = make_list(nb_tests);
  list* copy = copy_list(l);
  
  for (int i = 0; i < nb_tests; i++)
    {
      list* expected = r_list_pop_front(copy);
      list* got = list_pop_front(l);
      int exp = expected == NULL ? -84: expected->val;
      int g = got == NULL ? -42 : got->val;
      comp_int(name,exp,g,"");
      r_free(expected);
      r_free(got);
    }
  
  comp_full_list(name,copy,l,"");
  r_FreeList(l);
  r_FreeList(copy);
}

void test_list_remove(char* name, int nb_tests)
{
  list* l = make_list(nb_tests);
  list* copy = copy_list(l);
  while (nb_tests > 0)
    {
      int ind = rand()%nb_tests;
      list* expected = r_list_remove(copy,ind);
      list* got = list_remove(l,ind);
      
      int exp = expected == NULL ? -84: expected->val;
      int g = got == NULL ? -42 : got->val;
      
      comp_int(name,exp,g,"");
      r_free(expected);
      r_free(got);
      nb_tests--;
    }
  
  comp_full_list(name,copy,l,"");
  r_FreeList(l);
  r_FreeList(copy);
}




void test_list_search(char*name, int nb_tests)
{
  int* vals = generate_int_array(nb_tests);
  list* l = list_from_array(vals,nb_tests);

  for (int i = 0; i < nb_tests/2; i++)
    {
      int ind = rand()%nb_tests;
      list* expected = r_list_search(l,vals[ind]);
      list* got = list_search(l,vals[ind]);
      comp_list(name,expected,got,"");
      
    }
  
  for (int i = 0; i <nb_tests/2; i++)
    {
      int val = rand()%MAX;
      list* expected = r_list_search(l,val);
      list* got = list_search(l,val);
      comp_list(name,expected,got,"");
      
    }
  r_FreeList(l);
  r_free(vals);
}


void test_FreeList(char* name, int nb_tests)
{
  list* l = make_list(nb_tests);
  FreeList(l);
  comp_size_t(name,nb_tests+1,all_free,"");
}



void all_lists_tests(int nb_tests)
{
  Func funcs[] =
    {
     test_list_init,
     test_create_list,
     test_list_is_empty,
     test_list_len,
     test_list_get,
     test_list_push_front,
     test_list_push_end,
     test_list_insert,
     test_insert_in_sorted_list,
     test_list_pop_front,
     test_list_remove,
     test_list_search,
     test_FreeList
    };
  char* names[] =
    {
     "test_list_init",
     "test_create_list",
     "test_list_is_empty",
     "test_list_len",
     "test_list_get",
     "test_list_push_front",
     "test_list_push_end",
     "test_list_insert",
     "test_insert_in_sorted_list",
     "test_list_pop_front",
     "test_list_remove",
     "test_list_search",
     "test_FreeList"
    };
  CallFile("LISTS TESTS:",funcs,names,13, nb_tests);
}
