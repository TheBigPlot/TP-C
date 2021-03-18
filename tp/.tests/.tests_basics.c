#include <stdio.h>
#include <stdlib.h>

#include "../basics/basics.h"
#include ".res/.res_basics.h"
#include ".unitTest/.unitTest.h"
#include ".tests_basics.h"
#include ".tools.h"
#include "../structs.h"
#include "../alloc.h"


extern size_t all_alloc;
extern size_t all_free;



void test_power_of_two(char* name, int nb_tests)
{
  //tests values
  nb_tests = 7;
  int vals[] = {0,1,3,8,16,25,50};
  for (int i = 0; i< nb_tests; i++)
    {
      //calls & tests
      size_t expected = r_power_of_two(vals[i]);
      size_t got = power_of_two(vals[i]);
      comp_size_t(name,expected,got,"");
    }
}

void test_bin_to_int(char* name, int nb_tests)
{
  //tests values
  nb_tests = 8;
  int vals[] = {0,1,1000,0001,1011011011,100111,1111,0000};
  for(int i = 0; i< nb_tests; i++)
    {
      //calls & tests
      unsigned long expected = r_binary_to_int(vals[i]);
      unsigned long got = binary_to_int(vals[i]);
      comp_size_t(name,expected,got,"");
    }
}


void test_decompose(char* name, int nb_tests)
{
  //values part
  int* vals = generate_int_array(nb_tests);
  for (int i = 0; i < nb_tests; i++)
    {
      //creation and initialisation of 2 array of 14 elements
      int* expected = r_malloc(14*sizeof(int));
      int* got = r_malloc(14*sizeof(int));
      for (int i = 0; i < 14; i++)
	{
	  expected[i] = 0;
	  got[i] = 0;
	}

      //calls and tests
      r_decompose(vals[i],expected);
      decompose(vals[i],got);
      insert_sort(expected,14);
      insert_sort(got,14);
      comp_array(name, expected, 14, got, "");

      //free the temporary arrays
      r_free(expected);
      r_free(got);
    }
  
  r_free(vals);
}


void test_reverse_array(char* name, int nb_tests)
{
  //tests values
  nb_tests = 5;
  int vals[] = {0,1,5,8,17};

  for(int i = 0; i < nb_tests; i++)
    {
      int* arr = generate_int_array(vals[i]);
      int* copy = copy_array(arr,vals[i]);

      reverse_arr(arr,vals[i]);
      r_reverse_arr(copy,vals[i]);
      comp_array(name,copy,vals[i],arr,"");

      r_free(arr);
      r_free(copy);
    }
}



void test_shift_array(char* name, int nb_tests)
{
  nb_tests = 5;
  int vals[] = {0,1,5,8,17};
  int shifts[] = {-1,2,-2,8,-5};
  for(int i = 0; i<nb_tests ; i++)
    {
      int* arr = generate_int_array(vals[i]);
      int* copy = copy_array(arr,vals[i]);
      
      n_shift_arr(arr,vals[i],shifts[i]);
      r_n_shift_arr(copy,vals[i],shifts[i]);
      comp_array(name,copy,vals[i],arr,"");

      r_free(arr);
      r_free(copy);
    }
}

void test_replace(char* name, int nb_tests)
{
  nb_tests = 7;
  char strings[7][20] = {"","","h","hello","hello world","122okdacccc"};
  char strings_copy[7][20] = {"","","h","hello","hello world","122okdacccc"};
  char to_replace[7][30] = {"","salut","ka","aie","Hello Hello como estas","233"};
  
  for(int i = 0; i < nb_tests; i++)
    {
      replace(strings[i],to_replace[i]);
      r_replace(strings_copy[i],to_replace[i]);
      comp_string(name,strings_copy[i],strings[i],"");
    }
}


void test_cesar(char* name, int nb_tests)
{
  nb_tests = 6;
  char strings[6][25] =
    {
     "",
     "abcdefg",
     "bcdefgh",
     "Hello World !",
     "hola ! comment vas-tu ?",
     "!! __a__b"
    };
  char strings_copy[6][25] =
    {
     "",
     "abcdefg",
     "bcdefgh",
     "Hello World !",
     "hola ! comment vas-tu ?",
     "!! __a__b"
    };
  
  int vals[] = {2,1,-3,4,96,-76};

  for (int i = 0; i < nb_tests; i++)
    {
      cesar(strings[i],vals[i]);
      r_cesar(strings_copy[i],vals[i]);
      comp_string(name,strings_copy[i],strings[i],"");
    }
}


void test_calculator(char* name, int nb_tests)
{
  nb_tests = 4;
  char* calculs[] = {"1+1","2+2*2","6*9+5*2","12/3/3*1+1"};
  for(int i = 0; i< nb_tests ; i++)
    {
      unsigned long test = basic_calculator(calculs[i]);
      unsigned long res = r_basic_calculator(calculs[i]);
      comp_size_t(name,res,test,"");
    }
}



void all_basics_tests(int nb_tests)
{
  //an array of pointer to function
  Func funcs[] =
    {
     test_power_of_two,
     test_bin_to_int,
     test_decompose,
     test_reverse_array,
     test_shift_array,
     test_replace,
     test_cesar,
     test_calculator
    };
  //the names of the functions
  char* names[] =
    {
     "test_power_of_two",
     "test_binary_to_int",
     "test_decompose",
     "test_reverse_array",
     "test_shift_array",
     "test_replace",
     "test_cesar",
     "test_calculator"
    };
  
  //function that call all the others
  CallFile("BASICS TESTS:",funcs,names,8,nb_tests);
}
