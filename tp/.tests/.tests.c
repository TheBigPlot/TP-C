#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <time.h>

#include ".tests_basics.h"
#include ".tests_lists.h"
#include ".tests_queues.h"
#include ".tests_graphs.h"

#include "../structs.h"
#include ".res/.res_list.h"
#include ".garbage.h"



#include <dlfcn.h>


void help()
{
  printf("The program work like:\n ./tests file nb_tests\n");
  printf("the possible files arguments are: \n");
  printf("basics - lists - queues - graphs \n");
}


//WARNING GLOBALS DO NOT TOUCH

size_t all_alloc;
size_t all_free;
size_t all_realloc;
plist* garbage;



int main (int argc, char** argv)
{
  if (argc != 3)
    {
      help();
      errx(1,"arguments problem");
    }
  
  
  time_t t;
  srand((unsigned) time(&t));
  
  int nb_tests = atoi(argv[2]);


  all_alloc = 0;
  all_free = 0;
  all_realloc = 0;
  garbage = NULL;

  //all the case that launch the program
  
  if (strcmp(argv[1],"basics") == 0)
    all_basics_tests(nb_tests);

  else if (strcmp(argv[1],"lists") == 0)
    all_lists_tests(nb_tests);

  else if (strcmp(argv[1],"queues") == 0)
    all_queues_tests(nb_tests);

  else if (strcmp(argv[1],"graphs") == 0)
    all_graphs_tests(nb_tests);

  else if (strcmp(argv[1],"all") == 0)
    {
      all_basics_tests(nb_tests);
      all_lists_tests(nb_tests);
      all_queues_tests(nb_tests);
      all_graphs_tests(nb_tests);
    }

  else
    {
      help();
      errx(1,"arguments problem");
    }

  return 0;
}
