#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <time.h>
#include <string.h>

#include ".unitTest.h"
#include "../../structs.h"
#include "../.tools.h"
#include "../.garbage.h"

#define MAX 10000


extern size_t all_alloc;
extern size_t all_free;
extern plist* garbage;

void red () {
  printf("\033[1;31m");
}

void green() {
  printf("\033[1;32m");
}

void blue() {
  printf("\033[1;33m");
}

void reset () {
  printf("\033[0m");
}

void trans(void){
  printf("============================\n\n");
}

void BigTrans(void){
  printf("==================================================\n\
==================================================\n\n");
}

void CallFile(char* name,Func funcs[],char* names[],int len, int nb_tests)
{
  blue();
  BigTrans();
  printf("%s\n\n",name);
  reset();
  all_alloc = 0;
  all_free = 0;
  call_all_functions(funcs,names,len, nb_tests);
  blue();
  BigTrans();
  reset();
}

void callFunction(Func f,char* name, int nb_tests)
{
  trans();
  (*f)(name,nb_tests);
  trans();
}

void call_all_functions(Func funcs[],char** names,int len, int nb_tests)
{
  for(int i = 0; i < len; i++)
    {
      garbage = create_garbage(NULL);
      trans();
      (*funcs[i])(names[i],nb_tests);
      check_allocs();
      trans();
      garbage_free(garbage);
    }
}



void comp_bool(char* testname,int expected, int got, char* data)
{
  printf("[");
  if (expected == got)
    {
      green();
      printf("OKAY");
      reset();
    }
  
  else
    {
      red();
      printf("NOT OKAY");
      reset();
    }

  printf("] %s\n",testname);
  printf("\texpected: %s | got: %s\n",expected==0?"false":"true",got==0?"false":"true");

  if (strcmp(data,"") != 0)
    printf("input: %s\n",data);

  printf("\n");
}


void comp_size_t(char* testname, size_t expected, size_t got, char* data)
{
  printf("[");
  
  if (expected == got)
    {
      green();
      printf("OKAY");
      reset();
    }

  else
    {
      red();
      printf("NOT OKAY");
      reset();
    }
  
  printf("] %s\n",testname);
  printf("\texpected: %ld | got: %ld\n",expected,got);

  if (strcmp(data,"") != 0)
    printf("input: %s\n",data);
  printf("\n");
}

void comp_int(char* testname, int expected, int got, char* data)
{
  printf("[");
  if (expected == got)
    {
      green();
      printf("OKAY");
      reset();
    }
  else
    {
      red();
      printf("NOT OKAY");
      reset();
    }
  printf("] %s\n",testname);
  printf("\texpected: %d | got: %d\n",expected,got);

  if (strcmp(data,"") != 0)
    printf("input: %s\n",data);
  printf("\n");
}


void comp_array(char* testname, int* expected, int len, int* got, char* data)
{
  printf("[");
  
  if (array_equals(expected, got,len))
    {
      green();
      printf("OKAY");
      reset();
    }
  
  else
    {
      red();
      printf("NOT OKAY");
      reset();
    }
  
  printf("] %s\n",testname);
  printf("\texpected: ");
  printArr(expected,len);
  printf("\n\tgot: ");
  printArr(got,len);
  
  if (strcmp(data,"") != 0)
    printf("input: %s\n",data);
  printf("\n");
}

void comp_string(char* testname, char* expected, char* got, char* data)
{
  printf("[");
  if (strcmp(expected,got) == 0)
    {
      green();
      printf("OKAY");
      reset();
    }
  
  else
    {
      red();
      printf("NOT OKAY");
      reset();
    }
  
  printf("] %s\n",testname);
  printf("\texpected: %s | got: %s\n",expected,got);

  if (strcmp(data,"") != 0)
    printf("input: %s\n",data);

  printf("\n");
}

void comp_list(char* testname, list* expected, list* got, char* data)
{
  printf("[");
  if (expected == got)
    {
      green();
      printf("OKAY");
      reset();
    }
  
  else
    {
      red();
      printf("NOT OKAY");
      reset();
    }
  
  printf("] %s\n",testname);
  if (expected == NULL && got == NULL)
    printf("\texpected: %s | got: %s\n","Null","NULL");

  else if (expected == NULL)
    printf("\texpected: %s | got: %d\n","Null",got->val);

  else if (got == NULL)
    printf("\texpected: %d | got: %s\n",expected->val,"NULL");

  else
    printf("\texpected: %d | got: %d\n",expected->val,got->val);

  if (strcmp(data,"") != 0)
    printf("input: %s\n",data);

  printf("\n");
}

void comp_full_list(char* testname, list* expected, list* got, char* data)
{
  printf("[");
  if(list_equals(expected,got))
    {
      green();
      printf("OKAY");
      reset();
    }
  
  else
    {
      red();
      printf("NOT OKAY");
      reset();
    }
  
  printf("] %s\n",testname);
  printf("\texpected:\n\t");
  printList(expected);
  
  printf("\n\tgot:\n\t");
  printList(got);
  printf("\n");

  if (strcmp(data,"") != 0)
    printf("input: %s\n",data);

  printf("\n");
}



void check_allocs()
{
  if (all_alloc == all_free)
    green();
  
  else
    red();
  
  printf("%zu alloc(s) -- %zu free(s) \n",all_alloc, all_free);
  reset();
  all_alloc = 0;
  all_free = 0;
}



