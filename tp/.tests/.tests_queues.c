#include <stdio.h>
#include <stdlib.h>

#include ".unitTest/.unitTest.h"
#include ".tools.h"
#include ".tests_queues.h"
#include "../queues/queue.h"
#include ".res/.res_queue.h"
#include "../structs.h"
#include "../alloc.h"

extern size_t all_alloc;
extern size_t all_free;

void test_init_queue(char* name, int nb_tests)
{
  nb_tests++;
  queue* qtest = init_queue();
  queue* qgood = r_init_queue();
  if (qtest == NULL)
    comp_bool(name,1,0,"");

  else
    {   
      comp_full_list(name,qgood->Queue,qtest->Queue,"");
      r_FreeQueue(qtest);
    }
  
  r_FreeQueue(qgood);
}


void test_enqueue(char* name, int nb_tests)
{
  for (int i = 0; i < nb_tests; i++)
    {
      //creation of 2 tmp lists
      queue* q = init_queue();
      queue* r_q = r_init_queue();

      if (q != NULL)
	{
	  //tests values
	  int* vals = generate_int_array(nb_tests*2);

	  //enqueue valuue in the queues
	  for (int j = 0; j < nb_tests*2; j++)
	    {
	      enqueue(q,vals[j]);
	      r_enqueue(r_q,vals[j]);
	    }
	  
	  free(vals);
	  comp_full_list(name,r_q->Queue,q->Queue,"");
	  
	  r_FreeQueue(q);
	  r_FreeQueue(r_q);
	}
      //there is a problem, only free r_q
      //q is not allocated
      else
	{
	  comp_bool(name,1,0,"");
	  r_free(r_q);
	}
    }
}

void test_dequeue(char* name, int nb_tests)
{
  queue* q_start = init_queue();
  queue* r_q_start = r_init_queue();
  
  if (q_start != NULL)
    {
      list* elm_q_start = dequeue(q_start);
      list* elm_r_q_start = r_dequeue(r_q_start);
      comp_bool(name,1,elm_q_start == elm_r_q_start && list_equals(q_start->Queue,r_q_start->Queue),"");
      r_FreeQueue(q_start);
    }
  
  else
    comp_bool(name,1,0,"");
    
  r_FreeQueue(r_q_start);
  int* vals = generate_int_array(nb_tests*2);
  queue* q = init_queue();
  queue* r_q = init_queue();

  if (q != NULL)
    {
      // add elements to the queues (could be replace by a subfonction)
      for (int i = 0; i< nb_tests*2; i++)
	{
	  r_enqueue(q,vals[i]);
	  r_enqueue(r_q,vals[i]);
	}
      
      printf("\tqueue de test:\n\t");
      printList(q->Queue);
      printf("\n");

      //dequeue some elements of the queues and compare
      for (int i = 0; i < 3*nb_tests/4; i++)
	{
	  list* elm = dequeue(q);
	  list* r_elm = r_dequeue(r_q);
	  comp_list(name,r_elm,elm,"");
	  r_free(elm);
	  r_free(r_elm);
	}
      
      printf("\n");
      comp_full_list(name,r_q->Queue,q->Queue,"");
      r_free(q);
    }
  
  else
    comp_bool(name,1,0,"");

  r_free(r_q);
  r_free(vals);
  
}


void test_isempty(char* name, int nb_tests)
{
  nb_tests++;
  queue* q = init_queue();
  if (q != NULL)
    {
      comp_bool(name,r_isempty(q),isempty(q),"");
      r_enqueue(q,10);
      comp_bool(name,r_isempty(q),isempty(q),"");
      r_FreeQueue(q);
    }
  
  else
    {
      comp_bool(name,1,0,"");
      comp_bool(name,1,0,"");
    }
}

void test_FreeQueue(char* name, int nb_tests)
{
  queue* q = r_init_queue();
  q->Queue = make_list(nb_tests);
  FreeQueue(q);
  comp_size_t(name,nb_tests+2,all_free,"");
}


void all_queues_tests(int nb_tests)
{
  Func funcs[] =
    {
     test_init_queue,
     test_enqueue,
     test_dequeue,
     test_isempty,
     test_FreeQueue
    };
  char* names[] =
    {
     "test_init_queue",
     "test_enqueue",
     "test_dequeue",
     "test_isempty",
     "test_FreeQueue"
    };
  CallFile("QUEUES TESTS:",funcs,names,5, nb_tests);
}
